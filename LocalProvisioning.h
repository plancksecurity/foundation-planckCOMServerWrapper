#pragma once
#include "stdafx.h"
#undef __attribute__
#undef attribute
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/manipulators.hpp>
#include "unpack.hh"
#include <boost/algorithm/string.hpp>

namespace pEp
{

	// define the registry keys
	#define ProvisioningRegKey				_T("Software\\planck\\Provisioning")
	#define ProvisioningLocalFolderRegKey	_T("LocalFolder")
	#define ProvisioningIsProvisionedRegKey _T("IsProvisioned")
	#define ProvisioningFileNameRegKey		_T("FileName")
	

	// define the file names to be used during provisonoing
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
		bool convertBool(const std::wstring& in);

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
		static bool createDirIfNotExists(const std::filesystem::path& path);
	};
}