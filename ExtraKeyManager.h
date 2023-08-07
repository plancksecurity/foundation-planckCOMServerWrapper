// Copyright planck security 2023
// 07.08.2023/IP - added handling of extrakeys

#pragma once
#include <pEp/pEpEngine.h>
#include "unpack.hh"

namespace pEp
{
#define OutlookRegKey					_T("Software\\planck\\Outlook")
#define OutlookExtrakeyRegKey			_T("Extrakeys")
#define ExtrakeyKeyDefaultValue			_T("")
#define ExtraKeyRegKey					_T("Software\\planck\\Provisioning\\Extrakeys")
#define ExtraKeyLocalFolderRegKey		_T("LocalFolder")
#define ExtraKeyDir						_T("Extrakeys")

#define ALWAYS_IMPORT false

	class ExtraKeyManager
	{
		PEP_SESSION session;
		pEp::utility::RegistryKey rkExtrakeyImporter;	// references the config for managing the extrakey importer
		pEp::utility::RegistryKey rkSettingOutlook;		// references the registry node for Outlook configs
		std::wstring localFolder;						// holds the reference to the folder to look for extrakey import files

		/// <summary>
		// Loads a key from a file in a particular directory
		void loadKeyFromFile(const std::filesystem::path& p);
		/// </summary>
		/// <returns></returns>
		
		/// <summary>
		// imports a PGP key
		std::wstring importExtraKey(const std::filesystem::path& p) const;
		/// </summary>
		/// <returns></returns>

		/// <summary>
		// loads a text file into a string
		std::string loadTextFileContent(const std::filesystem::path& p) const;
		/// </summary>
		/// <returns></returns>
		
		/// <summary>
		// saves .stamp file for a particular key
		void saveFprToStamp(const std::filesystem::path& p, const std::string& fpr) const;
		/// </summary>
		/// <returns></returns>

		/// <summary>
		/// Get default provisioning directory
		/// </summary>
		/// <returns></returns>
		static std::wstring defaultExtrakeyPath();

		/// <summary>
		/// Checks if a file contains a PGP public Key
		/// </summary>
		/// <returns></returns>
		bool containsPGPPublicKey(const std::wstring& filename);

		/// <summary>
		/// Builds the string with extrakey values to be put for Outlook
		/// </summary>
		/// <returns></returns>
		std::wstring ExtraKeyManager::buildExtraKeysRegistryValueForOutlook(std::wstring fpr);

		bool comparei(wstring stringA, wstring stringB);
		std::string wstringToString(std::wstring ws);

	public:
		ExtraKeyManager(PEP_SESSION session): session(session), rkExtrakeyImporter(ExtraKeyRegKey), rkSettingOutlook(OutlookRegKey) {};

		/// <summary>
		/// Imports keys found in %LOCALAPPDATA%\pEp\Provisioning\Extrakeys and adds necessary registry
		/// keys in HKEY_CURRENT_USER\Software\pEp\Provisioning\Extrakeys
		/// </summary>
		void ImportKeys();
	};
};
