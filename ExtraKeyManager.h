#pragma once
#include <pEp/pEpEngine.h>
#include "unpack.hh"

namespace pEp
{
#define ExtraKeyRegKey					_T("Software\\planck\\Provisioning\\Extrakeys")
#define ExtraKeyLocalFolderRegKey		_T("LocalFolder")
#define ExtraKeyDir						_T("Extrakeys")

#define ALWAYS_IMPORT true

	class ExtraKeyManager
	{
		PEP_SESSION session;
		pEp::utility::RegistryKey rk;
		std::wstring localFolder;
		std::wstring provisioningFileName;

		/// <summary>
		// Loads keys in a particular directory
		void loadKeyFile(const std::filesystem::path& p);
		/// </summary>
		/// <returns></returns>
		
		/// <summary>
		// imports a PGP key
		std::string importExtraKey(const std::filesystem::path& p) const;
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

	public:
		ExtraKeyManager(PEP_SESSION session) noexcept : session(session), rk(ExtraKeyRegKey) {};

		/// <summary>
		/// Imports keys found in %LOCALAPPDATA%\pEp\Provisioning\Extrakeys and adds necessary registry
		/// keys in HKEY_CURRENT_USER\Software\pEp\Provisioning\Extrakeys
		/// </summary>
		void ImportKeys();
	};
};
