#include "stdafx.h"
#include "MediaKeyManager.h"
#include <fstream>
#include "pEp_utility.h"

namespace pEp
{

namespace fs = std::filesystem;


std::string MediaKeyManager::trim_chars(const std::string& in, const std::string& chars) const
{   
    std::string part;
    size_t start = in.find_first_not_of(chars);
    part = (start == std::string::npos) ? "" : in.substr(start);
    size_t end = part.find_last_not_of(chars);
    return (end == std::string::npos) ? "" : part.substr(0, end + 1);
}


std::string MediaKeyManager::load_text_file_contents(const std::filesystem::path& p) const
{
    std::ifstream t(p);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void MediaKeyManager::save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr) const
{
    std::ofstream outfile;
    outfile.open(p / stamp_filename, std::ios_base::trunc);
    outfile << fpr;
}


void MediaKeyManager::ConfigureMediaKeyMap() const
{
    HKEY key;
    LONG status;
    status = RegOpenKeyEx(HKEY_CURRENT_USER, MediaKeyRegKey, 0, KEY_QUERY_VALUE, &key);
    if (status == ERROR_FILE_NOT_FOUND)
    {
        status = RegCreateKeyEx(HKEY_CURRENT_USER, MediaKeyRegKey, 0, REG_NONE,
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);

    }
    if (status == ERROR_SUCCESS)
    {
        TCHAR lpValname[2048];
        DWORD dwValSize = 2048;
        BYTE lpData[2048];
        DWORD dwDataSize = 2048;
        DWORD type;
        stringpair_list_t* media_key_map = new_stringpair_list(nullptr);


        int i = 0;
        while ((status = RegEnumValue(key, i++, lpValname, &dwValSize, NULL, &type, lpData, &dwDataSize)) == 0)
        {
            if (type == REG_SZ)
            {
                std::string fpr = utility::utf8_string((LPWSTR)lpData);
                std::string pattern = utility::utf8_string((LPWSTR)lpValname);
                stringpair_list_add(media_key_map, new_stringpair(pattern.c_str(), fpr.c_str()));
            }
            dwValSize = 2048;
            dwDataSize = 2048;
        }
        if (media_key_map->value != nullptr)
        {
            PEP_STATUS pep_status = config_media_keys(session, media_key_map);
            if (pep_status != PEP_STATUS_OK)
            {
                provisioning_log_error << "Error configuring media keys: " << pep_status;
            }
        }
        free_stringpair_list(media_key_map);
    }
}



std::string MediaKeyManager::import_media_key(const std::filesystem::path& p) const
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
    fs::path stamp_path = p / stamp_filename;

    if (fs::exists(privkey_path) && fs::exists(pubkey_path) && fs::exists(pattern_path))
    {
        // check stamp datetime against privkey, pubkey and pattern
        // and return if it stamp_path greater or equal than all of them
        if (fs::exists(stamp_path))
        {
            const auto time_stamp = fs::last_write_time(stamp_path);
            const auto time_privkey = fs::last_write_time(privkey_path);
            const auto time_pubkey = fs::last_write_time(pubkey_path);
            const auto time_pattern = fs::last_write_time(stamp_path);
            if (time_stamp >= time_privkey && time_stamp >= time_pubkey && time_stamp >= time_pattern)
            {
                return;
            }
        }

        // import keys and configure media key registry keys 
        std::string fpr_pri = import_media_key(privkey_path);
        std::string fpr_pub = import_media_key(pubkey_path);
        if (fpr_pri.compare(fpr_pub) != 0)
        {
            provisioning_log_error << "Error importing keys from " << p.c_str() << 
                                      ": FPRs do not match. This could mean that there " << 
                                      "is some mismatch between private an public keys.";
            delete_keypair(session, fpr_pri.c_str());
            delete_keypair(session, fpr_pub.c_str());
        }
        else
        {
            std::string pattern = trim_chars(load_text_file_contents(pattern_path));
            if (pattern.size() > 0)
            {
                save_fpr_stamp(p, fpr_pri);
                rk.SetValue(utility::utf16_string(pattern), utility::utf16_string(fpr_pri));
                provisioning_log_info << "Imported media key for pattern: " << pattern;
            }
            else
            {
                provisioning_log_info << "Found a void pattern in " << p.c_str() << ". Ignoring.";
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
        if (dir_entry.is_directory())
        {
            load_keys_in_dir(dir_entry);
        }
    }

}

} // namespace pEp