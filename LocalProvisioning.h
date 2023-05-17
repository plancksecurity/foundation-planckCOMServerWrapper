#pragma once
#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include "unpack.hh"
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/manipulators.hpp>

namespace pEp
{

	#define ProvisioningRegKey				_T("Software\\planck\\Provisioning")
	#define ProvisioningLocalFolderRegKey	_T("LocalFolder")
	#define ProvisioningIsProvisionedRegKey _T("IsProvisioned")
	#define ProvisioningFileNameRegKey		_T("FileName")

	#define DeploymentKeyFile L"deployment_key-pub.der"
	#define ProvisioningKeyFile L"provisioning_key.der"
	#define DefaultProvisionPackage L"pEp.ppk"


	class LocalProvisioning
	{
		/// <summary>
		/// Convert string into boolean
		/// </summary>
		/// <param name="in"></param>
		/// <returns></returns>
		bool convert_bool(const std::wstring& in);

	public:

		/// <summary>
		/// Run provisioning procedure
		/// </summary>
		void Run();

		/// <summary>
		/// Get default provisioning directory
		/// </summary>
		/// <returns></returns>
		static std::wstring defaultProvisioningPath();

		/// <summary>
		/// Creates a directory
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		static bool create_dir_if_not_exists(const std::filesystem::path& path);
	};


/// Provisioning Log

#define LOG_LOCATION(LEVEL) \
BOOST_LOG_SEV(::boost::log::trivial::logger::get(), LEVEL) \
<< boost::log::add_value("Line", __LINE__)                 \
<< boost::log::add_value("File", __FILE__)                 \
<< boost::log::add_value("Function", __FUNCTION__) \

#define provisioning_log_debug LOG_LOCATION(::boost::log::trivial::debug)
#define provisioning_log_info BOOST_LOG_TRIVIAL(info)
#define provisioning_log_warning BOOST_LOG_TRIVIAL(warning)
#define provisioning_log_error BOOST_LOG_TRIVIAL(error)



}


