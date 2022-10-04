#include "stdafx.h"
#include "MediaKeyManager.h"
#include <fstream>
#include <pEp/media_key.h>

namespace pEp
{

namespace fs = std::filesystem;

std::string MediaKeyManager::trim_chars(const std::string& in, const std::string& chars)
{   
    std::string part;
    size_t start = in.find_first_not_of(chars);
    part = (start == std::string::npos) ? "" : in.substr(start);
    size_t end = part.find_last_not_of(chars);
    return (end == std::string::npos) ? "" : part.substr(0, end + 1);
}


std::string MediaKeyManager::load_text_file_contents(const std::filesystem::path& p)
{
    std::ifstream t(p);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void MediaKeyManager::save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr)
{
    std::ofstream outfile;
    outfile.open(p / stamp_filename, std::ios_base::trunc);
    outfile << fpr;
}

void MediaKeyManager::add_registry_pattern(const std::string& pattern, const std::string& fpr)
{

}


PEP_STATUS MediaKeyManager::config_media_key(const std::string& pattern, const std::string& fpr)
{
    PEP_STATUS status = PEP_STATUS_OK;
    stringpair_list_t* media_key_map = new_stringpair_list(new_stringpair(pattern.c_str(), fpr.c_str()));
    status = config_media_keys(session, media_key_map);
    free_stringpair_list(media_key_map);
    return status;
}



std::string MediaKeyManager::import_media_key(const std::filesystem::path& p)
{
    std::string k = load_text_file_contents(p);
    identity_list *l;
    import_key(session, k.c_str(), k.size(), &l);
    return l->ident->fpr;
}




void MediaKeyManager::load_keys_in_dir(const std::filesystem::path& p)
{
    fs::path privkey_path = p / privkey_filename;
    fs::path pubkey_path = p / pubkey_filename;
    fs::path pattern_path = p / pattern_filename;

    if (fs::exists(privkey_path) && fs::exists(pubkey_path) && fs::exists(pattern_path))
    {
        std::string fpr_pri = import_media_key(privkey_path);
        std::string fpr_pub = import_media_key(pubkey_path);
        if (fpr_pri.compare(fpr_pub) != 0)
        {
            // TODO log
            std::cout << "FPRs do not match\n";
            delete_keypair(session, fpr_pri.c_str());
            delete_keypair(session, fpr_pub.c_str());
        }
        else
        {
            std::string pattern = trim_chars(load_text_file_contents(pattern_path));
            PEP_STATUS status = config_media_key(pattern, fpr_pri);
            if (status != PEP_STATUS_OK)
            {
                // TODO log
                std::cout << "Error in config_media_key: " << status << "\n";
            }
            else
            {
                save_fpr_stamp(p, fpr_pri);
            }
        }
    }

}

void MediaKeyManager::ImportKeys()
{
	fs::path provisioning_path(LocalProvisioning::defaultProvisioningPath());
	fs::path media_key_path = provisioning_path / MediaKeyDir;
    
    LocalProvisioning::create_dir_if_not_exists(media_key_path);
   
    for (const fs::directory_entry& dir_entry : fs::directory_iterator(media_key_path))
    {
        std::cerr << dir_entry << '\n';
        if (dir_entry.is_directory())
        {
            load_keys_in_dir(dir_entry);
        }
    }

}

void MediaKeyManager::ConfigureMediaKeyMap()
{
}


} // namespace pEp