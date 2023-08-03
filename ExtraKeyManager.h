#pragma once
#include <pEp/pEpEngine.h>
#include "unpack.hh"

namespace pEp
{
	#define ExtraKeyRegKey	_T("Software\\planck\\Provisioning\\Extrakeys")
	#define ExtraKeyDir		_T("Extrakeys")

	class ExtraKeyManager
	{
		inline static const std::wstring pubkey_filename = L"extra_key.asc";
		inline static const std::wstring stamp_filename = L"stamp.txt";

		PEP_SESSION session;
		pEp::utility::RegistryKey rk;

		// Loads keys in a particular directory
		void load_keys_in_dir(const std::filesystem::path& p);
		// imports a PGP key
		std::string import_extra_key(const std::filesystem::path& p) const;

		// trims space-characters from string
		std::string trim_chars(const std::string& in, const std::string& chars = " \n\r\t\f\v") const;
		// loads a text file into a string
		std::string load_text_file_contents(const std::filesystem::path& p) const;
		// saves stamp.txt for a particular key
		void save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr) const;

	public:
		ExtraKeyManager(PEP_SESSION session) noexcept : session(session), rk(ExtraKeyRegKey)
		{
		}

		/// <summary>
		/// Imports keys found in %LOCALAPPDATA%\pEp\Provisioning\Extrakeys and adds necessary registry
		/// keys in HKEY_CURRENT_USER\Software\pEp\Provisioning\Extrakeys
		/// </summary>
		void ImportKeys();
	};	
}
