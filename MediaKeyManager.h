#pragma once
#include "LocalProvisioning.h"
#include <pEp/pEpEngine.h>

namespace pEp
{
	#define MediaKeyRegKey	_T("Software\\planck\\Provisioning\\Mediakeys")
	#define MediaKeyDir		_T("Mediakeys")

	/// <summary>
	/// Manages importing and configuring media keys 
	/// See OUT-947,OUT-968,OUT-942,OUT-960 
	/// </summary>
	class MediaKeyManager
	{

		inline static const std::wstring pubkey_filename = L"public_key.asc";
		inline static const std::wstring privkey_filename = L"private_key.asc";
		inline static const std::wstring allkeys_filename = L"keys.asc";
		inline static const std::wstring pattern_filename = L"pattern.txt";
		inline static const std::wstring stamp_filename = L"stamp.txt";

		PEP_SESSION session;
		pEp::utility::RegistryKey rk;

		// Loads keys in a particular directory
		void load_keys_in_dir(const std::filesystem::path& p);
		// imports a PGP key
		std::string import_media_key(const std::filesystem::path& p) const;

		// trims space-characters from string
		std::string trim_chars(const std::string& in, const std::string& chars = " \n\r\t\f\v") const;
		// loads a text file into a string
		std::string load_text_file_contents(const std::filesystem::path& p) const;
		// saves stamp.txt for a particular key
		void save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr) const;

	public:

		MediaKeyManager(PEP_SESSION session) noexcept : session(session), rk(MediaKeyRegKey)
		{
		}

		/// <summary>
		/// Imports keys found in %LOCALAPPDATA%\pEp\Provisioning\Mediakeys and adds necessary registry
		/// keys in HKEY_CURRENT_USER\Software\pEp\Provisioning\Mediakeys
		/// </summary>
		void ImportKeys();

		/// <summary>
		/// Configures keys found in HKEY_CURRENT_USER\Software\pEp\Provisioning\Mediakeys
		/// </summary>
		void ConfigureMediaKeyMap() const;

	};

}