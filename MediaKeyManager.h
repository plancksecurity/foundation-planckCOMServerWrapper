#pragma once
#include "LocalProvisioning.h"
#include <pEp/pEpEngine.h>

namespace pEp
{
	#define MediaKeyRegKey	_T("Software\\pEp\\Provisioning\\Mediakeys")
	#define MediaKeyDir		_T("Mediakeys")

	class MediaKeyManager
	{

		inline static const std::wstring pubkey_filename = L"public_key.asc";
		inline static const std::wstring privkey_filename = L"private_key.asc";
		inline static const std::wstring pattern_filename = L"pattern.txt";
		inline static const std::wstring stamp_filename = L"stamp.txt";

		PEP_SESSION session;

		void load_keys_in_dir(const std::filesystem::path& p);
		std::string import_media_key(const std::filesystem::path& p);

		std::string trim_chars(const std::string& in, const std::string& chars = " \n\r\t\f\v");
		std::string load_text_file_contents(const std::filesystem::path& p);
		void add_registry_pattern(const std::string& pattern, const std::string& fpr);
		PEP_STATUS config_media_key(const std::string& pattern, const std::string& fpr);
		void save_fpr_stamp(const std::filesystem::path& p, const std::string& fpr);

	public:

		MediaKeyManager(PEP_SESSION session) noexcept : session(session)
		{
		}

		void ImportKeys();

		void ConfigureMediaKeyMap();






	};

}