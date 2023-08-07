// Copyright planck security 2023
// 07.08.2023/IP - added handling of extrakeys

#include "stdafx.h"
#include "ExtraKeyManager.h"
#include <fstream>
#include "pEp_utility.h"
#include "ProvisioningLog.h"
#include "LocalProvisioning.h"
#include <planckCoreV3/src/pEpEngine_internal.h>

#include <vector>
#include <sstream>
#include <algorithm>
#include <cwctype>
#include <boost/locale.hpp>

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
        localFolder = rkExtrakeyImporter.GetValue(ExtraKeyLocalFolderRegKey, ExtraKeyManager::defaultExtrakeyPath());

        provisioning_log_debug << "Creating " << localFolder << " if it does not exist.";
        LocalProvisioning::createDirIfNotExists(localFolder);

        for (const std::filesystem::directory_entry& dir_entry : std::filesystem::directory_iterator(localFolder))
        {
           ExtraKeyManager::loadKeyFromFile(dir_entry);
        }
    }

    void ExtraKeyManager::loadKeyFromFile(const std::filesystem::path& p)
    {
        std::filesystem::path pubkey_path = p;
        std::filesystem::path stamp_path = p;
        stamp_path += ".stamp";
        std::wstring fpr = L"";

        if (!containsPGPPublicKey(p.c_str())) {
            provisioning_log_debug << p.c_str() << " does not contain a public key";
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
                        saveFprToStamp(p, ExtraKeyManager::wstringToString(fpr));

                        std::wstring targetListOfExtrakeys = buildExtraKeysRegistryValueForOutlook(fpr);

                        if (rkSettingOutlook.SetValue(OutlookExtrakeyRegKey, targetListOfExtrakeys)) {
                            provisioning_log_info << "Set registry value for extrakey: " << fpr;
                        }
                        else {
                            provisioning_log_error << "Cannot set registry value for extrakey: " << fpr;
                        }
                        
                    }
                }
                catch (...) {
                    provisioning_log_error << "Cannot import key.";
                }
            }
        }
    }

    std::wstring ExtraKeyManager::importExtraKey(const std::filesystem::path& p) const
    {
        std::wstring ret = L"";
        std::string k = loadTextFileContent(p);
        identity_list* l;
        stringlist_t* imported_keys = new_stringlist(NULL);
        PEP_STATUS const status = import_extrakey_with_fpr_return(session, k.c_str(), k.size(), &l, &imported_keys, NULL);
        if ((status == PEP_KEY_IMPORTED)||(status==PEP_STATUS_OK))
        {
            std::string s = "";
            ret = boost::locale::conv::utf_to_utf<wchar_t>(imported_keys->value);
            provisioning_log_info << "Importing extra key from file " << p.c_str() << " successful, fpr: " << ret;
        }
        else
        {
            provisioning_log_error << "Error configuring extra key from file " << p.c_str() << ", status: " << status;
            goto finish_import_extrakey;
        }
    finish_import_extrakey:
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

    bool ExtraKeyManager::comparei(wstring stringA, wstring stringB)
    {
        std::locale loc = boost::locale::generator().generate("");  // use default system locale
        std::locale::global(loc);

        return 0 == std::use_facet<boost::locale::collator<wchar_t>>(loc).compare(boost::locale::collator_base::primary, stringA, stringB);
    }
    
    std::string ExtraKeyManager::wstringToString(std::wstring ws) {
        return boost::locale::conv::utf_to_utf<char>(ws);
    }

    std::wstring ExtraKeyManager::buildExtraKeysRegistryValueForOutlook(std::wstring fpr) {
        std::wstring listOfExtrakeys = rkSettingOutlook.GetValue(OutlookExtrakeyRegKey, ExtrakeyKeyDefaultValue);
        std::string ek = wstringToString(listOfExtrakeys);

        if (ExtraKeyManager::comparei(listOfExtrakeys, ExtrakeyKeyDefaultValue)) {
            listOfExtrakeys = fpr;
        }
        else {
            std::wstringstream ss(listOfExtrakeys);
            std::wstring item;
            std::vector<std::wstring> extraKeys;

            while (std::getline(ss, item, L',')) {
                extraKeys.push_back(item);
            }

            // Trim whitespace and remove empty
            for (auto it = extraKeys.begin(); it != extraKeys.end(); ) {
                it->erase(it->begin(), std::find_if(it->begin(), it->end(), [](wchar_t ch) {
                    return !std::iswspace(ch);
                    }));
                it->erase(std::find_if(it->rbegin(), it->rend(), [](wchar_t ch) {
                    return !std::iswspace(ch);
                    }).base(), it->end());

                if (it->empty()) {
                    it = extraKeys.erase(it);
                }
                else {
                    ++it;
                }
            }

            bool found = false;
            for (auto it = extraKeys.begin(); it != extraKeys.end(); ) {
                if (it->compare(fpr) == 0) {
                    found = true;
                }

                ++it;
            }

            if (!found) {
                listOfExtrakeys.append(L",").append(fpr);
            }
        }

        return listOfExtrakeys;
    }
}