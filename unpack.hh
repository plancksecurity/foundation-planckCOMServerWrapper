#ifndef SP_UNPACK
#define SP_UNPACK

#include <string>
#include <map>
#include <filesystem>



#include <cryptopp/files.h>
#include <cryptopp/oaep.h>
#include <cryptopp/osrng.h>
#include <cryptopp/xed25519.h>
#include <cryptopp/rsa.h>
#include <cryptopp/gcm.h>
#include <codecvt>


#include <pEp/pEpEngine.h>
//#include <pEp/downloadclient.hh>
#include "utf8_helper.h"

namespace SignedPackage {
    // locations maps installation location name to actual POSIX path
    typedef std::map< std::string, std::wstring > locations;

    const locations pEp_locations = {
            { "PER_USER_DIRECTORY",  pEp::utility::utf16_string(::per_user_directory()) },
            { "PER_MACHINE_DIRECTORY",  pEp::utility::utf16_string(::per_machine_directory()) }
        };

    void LoadPrivateKey(const std::wstring& filename, CryptoPP::PrivateKey& key);
    void LoadPublicKey(const std::wstring& filename, CryptoPP::PublicKey& key);

    void extract_archive(
            std::wstring pkg_path,
            std::wstring target_path
        );

    void decrypt_archive(
            std::filesystem::path archive,
            std::filesystem::path key,
            CryptoPP::PrivateKey& provisioning_key
        );

    std::string decrypt_distribution_key(
            std::filesystem::path key_path,
            CryptoPP::PrivateKey& provisioning_key
        );

    void verify_distribution_signature(
            std::filesystem::path archive,
            std::filesystem::path sigfile,
            CryptoPP::PublicKey& deployment_key
        );

    std::filesystem::path decrypt_distribution_archive(
            std::filesystem::path archive,
            std::filesystem::path key_path,
            CryptoPP::PrivateKey& provisioning_key
        );

    std::filesystem::path extract_deployment_archive(
            CryptoPP::PublicKey& deployment_key,
            CryptoPP::PrivateKey& provisioning_key,
            std::filesystem::path pkg_path
        );

    void install_if_location_empty(
            CryptoPP::PublicKey& deployment_key,
            CryptoPP::PrivateKey& provisioning_key,
            std::filesystem::path pkg_path,
            std::string location,
            std::filesystem::path target_path
        );

/*  how to provision for a user and use this API

    #include <pEp/unpack.hh>

    void provision(std::string url)
    {
        pEp::UpdateClient::product p { "provisioning data", url };

        UpdateClient::PublicKey update_key;
        UpdateClient::load_key("update_key.der");

        CryptoPP::ed25519PublicKey deployment_key;
        SignedPackage::LoadPublicKey("deployment_key-pub.der", deployment_key);

        CryptoPP::RSA::PrivateKey provisioning_key;
        SignedPackage::LoadPrivateKey("provisioning_key.der", provisioning_key);

        SignedPackage::provision_user(p, update_key, deployment_key,
                provisioning_key);
    }

*/

    //void provision_user(
    //        pEp::UpdateClient::product p,
    //        pEp::UpdateClient::PublicKey update_key,
    //        CryptoPP::PublicKey& deployment_key,
    //        CryptoPP::PrivateKey& provisioning_key,
    //        pEp::notifyRead_t notifyRead = nullptr,
    //        locations loc = pEp_locations
    //    );
}

#endif // SP_UNPACK
