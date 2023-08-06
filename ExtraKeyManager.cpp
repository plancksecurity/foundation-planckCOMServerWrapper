#include "stdafx.h"
#include "ExtraKeyManager.h"
#include <fstream>
#include "pEp_utility.h"
#include "ProvisioningLog.h"
#include "LocalProvisioning.h"
#include <planckCoreV3/src/pEpEngine_internal.h>

namespace pEp
{
    std::string ExtraKeyManager::loadTextFileContent(const std::filesystem::path& p) const
    {
        std::ifstream t(p);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

    void ExtraKeyManager::saveFprToStamp(const std::filesystem::path& p, const std::string& fpr) const
    {
        std::ofstream outfile;
        std::filesystem::path stamp_path = p;
        stamp_path += ".stamp";
        outfile.open(stamp_path, std::ios_base::trunc);
        outfile << fpr;
    }

    void ExtraKeyManager::ImportKeys()
    {     
        std::wstring fullPathToFile;
        provisioning_log_info << "Processing extrakeys for import.";  

        // either take the value specified in the registry, or fall back to the default value
        localFolder = rk.GetValue(ExtraKeyLocalFolderRegKey, ExtraKeyManager::defaultExtrakeyPath());
        //provisioningFileName = rk.GetValue(ExtraKeyFileNameRegKey, ExtraKeyDefaultFileName);

        provisioning_log_debug << "Creating " << localFolder << " if it does not exist.";
        LocalProvisioning::createDirIfNotExists(localFolder);

        for (const std::filesystem::directory_entry& dir_entry : std::filesystem::directory_iterator(localFolder))
        {
           ExtraKeyManager::loadKeyFile(dir_entry);
        }
    }

    void ExtraKeyManager::loadKeyFile(const std::filesystem::path& p)
    {
        std::filesystem::path pubkey_path = p;
        std::filesystem::path stamp_path = p;
        stamp_path += ".stamp";
        std::string fpr = "";

        if (!containsPGPPublicKey(p.c_str())) {
            //provisioning_log_debug << p.c_str() << " does not contain a public key";
            return;
        }

        provisioning_log_debug << "Loading key from " << pubkey_path.c_str() << " and writing it to " << stamp_path.c_str();

        if (std::filesystem::exists(pubkey_path))
        {
            // check stamp datetime against allkeys and pattern
            // and return if it stamp_path greater or equal than all of them
            if (std::filesystem::exists(stamp_path) && std::filesystem::exists(pubkey_path))
            {
                const auto time_stamp = std::filesystem::last_write_time(stamp_path);
                const auto time_allkeys = std::filesystem::last_write_time(pubkey_path);
                if (time_stamp >= time_allkeys)
                {
                    if (!ALWAYS_IMPORT) {
                        provisioning_log_error << "Will not load extrakey, as a .stamp file for this key has been detected.";
                        return;
                    }                    
                }
            }

            if (std::filesystem::exists(pubkey_path))
            {
                // import keys and configure extra key registry keys
                try {
                    fpr = importExtraKey(pubkey_path);
                    if (!fpr.empty())
                    {
                        saveFprToStamp(p, fpr);
                        //rk.SetValue(utility::utf16_string(pattern), utility::utf16_string(fpr));
                        provisioning_log_info << "Imported extra key.";
                    }
                }
                catch (...) {
                    provisioning_log_error << "Cannot import key.";
                }
            }
        }
    }

    std::string ExtraKeyManager::importExtraKey(const std::filesystem::path& p) const
    {
        std::string ret;
        std::string k = loadTextFileContent(p);
        identity_list* l;
        stringlist_t* imported_keys = new_stringlist(NULL);
        PEP_STATUS status = import_extrakey_with_fpr_return(session, k.c_str(), k.size(), &l, &imported_keys, NULL);
        if (status != PEP_KEY_IMPORTED)
        {
            provisioning_log_error << "Error configuring extra key " << p.c_str() << ": " << status;
            return "";
        }
        else
        {
            ret = imported_keys->value;
        }
        free_stringlist(imported_keys);
        return ret;
    }

    std::wstring ExtraKeyManager::defaultExtrakeyPath()
    {
        std::wstring pep_user_path = SignedPackage::pEp_locations.at("PER_USER_DIRECTORY");
        std::filesystem::path provisioning_path(pep_user_path);
        provisioning_path /= "Provisioning";
        provisioning_path /= "Extrakeys";

        return provisioning_path.c_str();
    }

    bool ExtraKeyManager::containsPGPPublicKey(const std::wstring& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            provisioning_log_error << "Error opening file" << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("-----BEGIN PGP PUBLIC KEY BLOCK-----") != std::string::npos) {
                while (std::getline(file, line)) {
                    if (line.find("-----END PGP PUBLIC KEY BLOCK-----") != std::string::npos) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}