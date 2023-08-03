#include "stdafx.h"
#include "ExtraKeyManager.h"
#include <fstream>
#include "pEp_utility.h"
#include "ProvisioningLog.h"
#include "LocalProvisioning.h"

namespace pEp
{
	namespace fs = std::filesystem;

    std::string ExtraKeyManager::trim_chars(const std::string& in, const std::string& chars) const
    {
        std::string part;
        size_t start = in.find_first_not_of(chars);
        part = (start == std::string::npos) ? "" : in.substr(start);
        size_t end = part.find_last_not_of(chars);
        return (end == std::string::npos) ? "" : part.substr(0, end + 1);
    }

    std::string ExtraKeyManager::load_text_file_contents(const std::filesystem::path& p) const
    {
        std::ifstream t(p);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

    void ExtraKeyManager::save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr) const
    {
        std::ofstream outfile;
        outfile.open(p / stamp_filename, std::ios_base::trunc);
        outfile << fpr;
    }

    void ExtraKeyManager::ImportKeys()
    {     
        provisioning_log_info << "Processing extrakeys for import.";

        fs::path provisioning_path(LocalProvisioning::defaultProvisioningPath());
        fs::path extra_key_path = provisioning_path / ExtraKeyDir;

        provisioning_log_debug << "Creating " << extra_key_path << " if it does not exist.";

        LocalProvisioning::createDirIfNotExists(extra_key_path);

        for (const fs::directory_entry& dir_entry : fs::directory_iterator(extra_key_path))
        {
            if (dir_entry.is_directory())
            {
                ExtraKeyManager::load_keys_in_dir(dir_entry);
            }
        }
    }

    std::string ExtraKeyManager::import_extra_key(const std::filesystem::path& p) const
    {
        std::string ret;
        std::string k = load_text_file_contents(p);
        identity_list* l;
        stringlist_t* imported_keys = new_stringlist(NULL);
        PEP_STATUS status = import_key_with_fpr_return(session, k.c_str(), k.size(), &l, &imported_keys, NULL);
        if (status != PEP_KEY_IMPORTED)
        {
            provisioning_log_error << "Error configuring extra key " << p.c_str() << ": " << status;
        }
        else
        {
            ret = imported_keys->value;
        }
        free_stringlist(imported_keys);
        return ret;
    }

    void ExtraKeyManager::load_keys_in_dir(const std::filesystem::path& p)
    {
        provisioning_log_debug << "Loading keys from " << p.c_str();

        fs::path pubkey_path = p / pubkey_filename;
        fs::path stamp_path = p / stamp_filename;

        if ( fs::exists(pubkey_path))
        {
            // check stamp datetime against allkeys and pattern
            // and return if it stamp_path greater or equal than all of them
            if (fs::exists(stamp_path) && fs::exists(pubkey_path))
            {
                const auto time_pattern = fs::last_write_time(stamp_path);
                const auto time_stamp = fs::last_write_time(stamp_path);
                const auto time_allkeys = fs::last_write_time(pubkey_path);
                if (time_stamp >= time_allkeys && time_stamp >= time_pattern)
                {
                    return;
                }
            }

            // import keys
            bool keys_are_imported = false;
            std::string fpr = "";
            if (fs::exists(pubkey_path))
            {
                // import keys and configure media key registry keys 
                std::string fpr_pub = import_extra_key(pubkey_path);
                if (!fpr_pub.empty())
                {
                    keys_are_imported = true;
                    fpr = fpr_pub;
                }
            }

            // update registry
            if (keys_are_imported && !fpr.empty())
            {
                save_fpr_stamp(p, fpr);
                //rk.SetValue(utility::utf16_string(pattern), utility::utf16_string(fpr));
               // provisioning_log_info << "Imported extra key";
            }
        }
    }
}