#pragma once
#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include "unpack.hh"

namespace pEp
{

	#define ProvisioningRegKey				_T("Software\\pEp\\Provisioning")
	#define ProvisioningLocalFolderRegKey	_T("LocalFolder")
	#define ProvisioningIsProvisionedRegKey _T("IsProvisioned")
	#define ProvisioningFileNameRegKey		_T("FileName")

	#define DeploymentKeyFile L"deployment_key-pub.der"
	#define ProvisioningKeyFile L"provisioning_key.der"
	#define DefaultProvisionPackage L"pEp.pkk"


	class LocalProvisioning
	{

		bool convert_bool(const std::wstring& in)
		{
			bool ret;
			if (in.size() < 1)
				return false;
			std::wstring s = in;
			boost::to_lower(s);
			std::wistringstream(s) >> std::boolalpha >> ret;
			return ret;
		}

		std::wstring defaultProvisioningPath()
		{
			std::wstring pep_user_path = SignedPackage::pEp_locations.at("PER_USER_DIRECTORY");
			std::filesystem::path provisioning_path(pep_user_path);
			provisioning_path /= "Provisioning";
			return provisioning_path.c_str();
		}

		bool create_dir_if_not_exists(const std::filesystem::path& path)
		{
			if (!std::filesystem::exists(path))
			{
				std::filesystem::create_directories(path);
			}
			else
			{
				if (!std::filesystem::is_directory(path))
				{
					std::filesystem::remove(path);
					std::filesystem::create_directories(path);
				}
			}
			return std::filesystem::exists(path) && std::filesystem::is_directory(path);
		}

	public:
		void Run()
		{
			pEp::utility::RegistryKey provisionRegKey(ProvisioningRegKey);
			std::wstring isProvisioned = provisionRegKey.GetValue(ProvisioningIsProvisionedRegKey, 
																L"False");
			std::wstring localFolder = provisionRegKey.GetValue(ProvisioningLocalFolderRegKey, 
																defaultProvisioningPath());
			std::wstring provisioning_file_name = provisionRegKey.GetValue(ProvisioningFileNameRegKey,
																			DefaultProvisionPackage);

			if (!convert_bool(isProvisioned))
			{
				std::filesystem::path pep_user_path(SignedPackage::pEp_locations.at("PER_USER_DIRECTORY"));
				std::filesystem::path provisioning_path(localFolder);
				std::filesystem::path pkg_path(provisioning_path / provisioning_file_name);
				std::filesystem::path deployment_key_path = provisioning_path / DeploymentKeyFile;
				std::filesystem::path provisioning_key_path = provisioning_path / ProvisioningKeyFile;
				std::filesystem::path target_path = provisioning_path / L"package";

				if (!std::filesystem::exists(provisioning_path))
					create_dir_if_not_exists(provisioning_path);

				if (!std::filesystem::exists(pkg_path))
					return; // AQUI log?

				if (!std::filesystem::exists(deployment_key_path))
					return; // AQUI log

				if (!std::filesystem::exists(provisioning_key_path))
					return; // AQUI log

				CryptoPP::ed25519PublicKey deployment_key;
				CryptoPP::RSA::PrivateKey provisioning_key;

				try
				{
					SignedPackage::LoadPublicKey(deployment_key_path, deployment_key);
					SignedPackage::LoadPrivateKey(provisioning_key_path, provisioning_key);

					SignedPackage::install_if_location_empty(deployment_key, provisioning_key,
						pkg_path, "PER_USER_DIRECTORY", target_path);

					for (auto const& direntry : std::filesystem::directory_iterator{ target_path }) {
						std::filesystem::path source = direntry.path();
						std::filesystem::rename(direntry.path(), pep_user_path / source.filename());
					}

					provisionRegKey.SetValue(ProvisioningIsProvisionedRegKey,L"True");
				}
				catch (std::runtime_error& e)
				{
					std::cout << e.what() << "\n";
				}
				catch (std::exception& e)
				{
					std::cout << e.what() << "\n";
				}
			}
		}


	};






}


