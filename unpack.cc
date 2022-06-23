#include "stdafx.h"
#include "unpack.hh"

#include <system_error>
#include <archive.h>
#include <archive_entry.h>

#ifdef WIN32
#include <io.h>
#include <direct.h>
// FIXME: name collision possible
static wchar_t *mkdtemp(wchar_t *_template, size_t len)
{
    if (_wmktemp_s(_template, len+1))
        return nullptr;

    if (_wmkdir(_template))
        return nullptr;

    return _template;
}
#endif

namespace SignedPackage {
    static bool path_empty(std::wstring path)
    {
        if (!std::filesystem::exists(path))
            return true;
        if (!std::filesystem::is_directory(path))
            return false;
        return std::filesystem::is_empty(path);
    }

    static void ensure_target_path(std::wstring path)
    {
        if (std::filesystem::exists(path)) {
            if (!std::filesystem::is_directory(path))
                std::filesystem::remove(path);
        }
        std::filesystem::create_directories(path);
    }

    static std::filesystem::path mktempdir()
    {
        std::filesystem::path _path = std::filesystem::temp_directory_path() / "spXXXXXXXXXXXX";
        std::unique_ptr< wchar_t[] > buffer { ::_wcsdup(_path.c_str()) };
        if (!buffer.get())
            throw std::bad_alloc();

        wchar_t *p = mkdtemp(buffer.get(), wcslen(buffer.get()));
        if (!p) {
            char err[512];
            if (!::strerror_s(err, sizeof(err), errno))
                throw std::filesystem::filesystem_error(err,
                    std::error_code(errno, std::system_category()));
            else
                throw std::filesystem::filesystem_error("Filesystem error",
                    std::error_code(errno, std::system_category()));
        }

        return buffer.get();
    }

    static void throw_archive_read_error(struct archive *a)
    {
        if (::archive_error_string(a)) {
            std::string error_string = ::archive_error_string(a);
            int e = ::archive_errno(a);
            ::archive_read_free(a);
            throw std::filesystem::filesystem_error(error_string,
                    std::error_code(e, std::system_category()));
        }
        else if (errno) {
            ::archive_read_free(a);
            char err[512];
            if (!::strerror_s(err, sizeof(err), errno))
                throw std::filesystem::filesystem_error(err,
                    std::error_code(errno, std::system_category()));
            else
                throw std::filesystem::filesystem_error("Filesystem error",
                    std::error_code(errno, std::system_category()));
        }
    }

    static void Load(const std::wstring& filename, CryptoPP::BufferedTransformation& bt)
    {
        CryptoPP::FileSource file(filename.c_str(), true);

        file.TransferTo(bt);
        bt.MessageEnd();
    }

    void LoadPrivateKey(const std::wstring& filename, CryptoPP::PrivateKey& key)
    {
        CryptoPP::ByteQueue queue;
        Load(filename, queue);

        key.Load(queue);
    }

    void LoadPublicKey(const std::wstring& filename, CryptoPP::PublicKey& key)
    {
        CryptoPP::ByteQueue queue;
        Load(filename, queue);

        key.Load(queue);
    }

    void extract_archive(
            std::wstring pkg_path,
            std::wstring target_path
        )
    {
        std::wstring cwd = std::filesystem::current_path();

        struct archive *a = ::archive_read_new();

        ::archive_read_support_filter_all(a);
        ::archive_read_support_format_all(a);

        int r = ::archive_read_open_filename_w(a, pkg_path.c_str(), 32768);
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN) {
            std::filesystem::current_path(cwd);
            throw_archive_read_error(a);
        }

        std::filesystem::current_path(target_path);

        struct ::archive_entry *entry;
        while (::archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            std::string pathname{::archive_entry_pathname(entry)};

            do {
                r = archive_read_extract(a, entry,
                        ARCHIVE_EXTRACT_ACL |
                        ARCHIVE_EXTRACT_FFLAGS |
                        ARCHIVE_EXTRACT_MAC_METADATA |
                        ARCHIVE_EXTRACT_NO_OVERWRITE |
                        ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS |
                        ARCHIVE_EXTRACT_SECURE_NODOTDOT |
                        ARCHIVE_EXTRACT_SECURE_SYMLINKS |
                        ARCHIVE_EXTRACT_TIME |
                        ARCHIVE_EXTRACT_XATTR
                    );
            } while (r == ARCHIVE_RETRY);
            if (r != ARCHIVE_OK && r != ARCHIVE_WARN) {
                std::filesystem::current_path(cwd);
                throw_archive_read_error(a);
            }
        }

        ::archive_read_free(a);
        std::filesystem::current_path(cwd);
    }

    std::string decrypt_distribution_key(
            std::filesystem::path key_path,
            CryptoPP::PrivateKey& provisioning_key
        )
    {
        CryptoPP::RSAES< CryptoPP::OAEP< CryptoPP::SHA256 > >::Decryptor
            decryptor(provisioning_key);
        CryptoPP::AutoSeededRandomPool rng;
        std::string distribution_key;

        CryptoPP::FileSource keySource(key_path.c_str(), true,
                new CryptoPP::PK_DecryptorFilter(rng, decryptor,
                    new CryptoPP::StringSink(distribution_key)));

        return distribution_key;
    }

    void verify_distribution_signature(
            std::filesystem::path archive,
            std::filesystem::path sigfile,
            CryptoPP::PublicKey& deployment_key
        )
    {
        CryptoPP::ed25519::Verifier verifier(
                dynamic_cast< CryptoPP::X509PublicKey& >(deployment_key));

        const size_t size = 64; // ed25519 signature size
        char signature[size];

        {
            std::ifstream _sigfile(sigfile, std::ios_base::in |
                    std::ios_base::binary);
            _sigfile.read(signature, size);
        }

        std::ifstream _archive(archive, std::ios_base::in | std::ios_base::binary);
        assert(_archive.good());
        bool valid = verifier.VerifyStream(_archive,
                (unsigned char*) signature, size);
        if (!valid)
            throw std::runtime_error("signature does not match"); 
    }

    std::filesystem::path decrypt_distribution_archive(
            std::filesystem::path archive,
            std::filesystem::path key_path,
            CryptoPP::PrivateKey& provisioning_key
        )
    {
        std::string distribution_key = decrypt_distribution_key(key_path,
                provisioning_key);

        std::ifstream ifs(archive, std::ios_base::binary | std::ios_base::in);
        char iv[12]; // 96 bit is GCM standard size
        ifs.read(iv, sizeof(iv));

        CryptoPP::GCM< CryptoPP::AES >::Decryption dec;
        dec.SetKeyWithIV((const unsigned char*) distribution_key.c_str(),
                distribution_key.size(), (const unsigned char*) iv, sizeof(iv));

        std::filesystem::path decrypted_archive = archive.c_str() + std::wstring(L"D");

        CryptoPP::FileSource archiveSource(ifs, true,
                new CryptoPP::AuthenticatedDecryptionFilter(dec,
                    new CryptoPP::FileSink(decrypted_archive.c_str())));

        return decrypted_archive;
    }

    std::filesystem::path extract_deployment_archive(
            CryptoPP::PublicKey& deployment_key,
            CryptoPP::PrivateKey& provisioning_key,
            std::filesystem::path pkg_path
        )
    {
        std::filesystem::path target_path = mktempdir();

        extract_archive(pkg_path, target_path);

        verify_distribution_signature(target_path / "DIST.A",
                target_path / "DIST.SIG", deployment_key);

        decrypt_distribution_archive(target_path / "DIST.A",
                target_path / "DIST.KEY", provisioning_key);

        return target_path;
    }

    void install_if_location_empty(
            CryptoPP::PublicKey& deployment_key,
            CryptoPP::PrivateKey& provisioning_key,
            std::filesystem::path pkg_path,
            std::string location,
            std::filesystem::path target_path
        )
    {
        if (path_empty(target_path)) {
            std::filesystem::path tmp_path = extract_deployment_archive(deployment_key,
                    provisioning_key, pkg_path);

            std::filesystem::path decrypted_archive =
                decrypt_distribution_archive(tmp_path / "DIST.A",
                        tmp_path / "DIST.KEY", provisioning_key);

            ensure_target_path(tmp_path / location);
            extract_archive(decrypted_archive, tmp_path / location);

            ensure_target_path(target_path);
            for (auto const& direntry : std::filesystem::directory_iterator{tmp_path / location}) {
                std::filesystem::path source = direntry.path();
                std::filesystem::rename(direntry.path(), target_path / source.filename());
            }

            std::filesystem::remove_all(tmp_path);
        }
    }

    //void provision_user(
    //        pEp::UpdateClient::product p,
    //        pEp::UpdateClient::PublicKey update_key,
    //        CryptoPP::PublicKey& deployment_key,
    //        CryptoPP::PrivateKey& provisioning_key,
    //        pEp::notifyRead_t notifyRead,
    //        locations loc
    //    )
    //{
    //    std::string target_path = loc["PER_USER_DIRECTORY"];

    //    // do not provision systems, which formerly were used
    //    if (!path_empty(target_path))
    //        return;

    //    std::string pkg_path = pEp::UpdateClient::update(p, update_key, notifyRead);
    //    install_if_location_empty(deployment_key, provisioning_key, pkg_path, "PER_USER_DIRECTORY", target_path);
    //    std::filesystem::remove(pkg_path);
    //}
}
