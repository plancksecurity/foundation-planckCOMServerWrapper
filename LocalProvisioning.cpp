#include "stdafx.h"
#include "LocalProvisioning.h"
#include "ProvisioningLog.h"

namespace pEp
{

	void LocalProvisioning::Run()
	{
		pEp::utility::RegistryKey provisionRegKey(ProvisioningRegKey);

		std::wstring isProvisioned = provisionRegKey.GetValue(ProvisioningIsProvisionedRegKey,L"False");
		std::wstring localFolder = provisionRegKey.GetValue(ProvisioningLocalFolderRegKey,LocalProvisioning::defaultProvisioningPath());
		std::wstring provisioningFileName = provisionRegKey.GetValue(ProvisioningFileNameRegKey,DefaultProvisionPackage);	

		if (!convertBool(isProvisioned))
		{
			provisioning_log_info << "Preparing provisioning routine.";

			std::filesystem::path pep_user_path(SignedPackage::pEp_locations.at("PER_USER_DIRECTORY"));
			std::filesystem::path provisioning_path(localFolder);
			std::filesystem::path pkg_path(provisioning_path / provisioningFileName);
			std::filesystem::path deployment_key_path = provisioning_path / DeploymentKeyFile;
			std::filesystem::path provisioning_key_path = provisioning_path / ProvisioningKeyFile;
			std::filesystem::path target_path = provisioning_path / L"package";

			if (!std::filesystem::exists(provisioning_path))
				LocalProvisioning::createDirIfNotExists(provisioning_path);

			if (!std::filesystem::exists(pkg_path)) {
				// there is no package to provision
				provisioning_log_info << "No provisioning package found.";
				return;
			}
			else {
				if (!std::filesystem::exists(deployment_key_path)) // there is no deployment key
				{
					provisioning_log_info << "Provisioning package found but no deployment key is present.";
					return;
				}
				if (!std::filesystem::exists(provisioning_key_path)) // there is no provisioning key
				{
					provisioning_log_info << "Provisioning package found but no provisioning key is present.";
					return;
				}
			}
		

			provisioning_log_info << "Starting provisioning of user data.";

			CryptoPP::ed25519PublicKey deployment_key;
			CryptoPP::RSA::PrivateKey provisioning_key;

			try
			{
				SignedPackage::LoadPublicKey(deployment_key_path, deployment_key);
				SignedPackage::LoadPrivateKey(provisioning_key_path, provisioning_key);

				// verify package signature and extract it in a temporary folder and copy them
				// to package extraction directory (pep_user_dir\Provisioning\package)
				SignedPackage::install_if_location_empty(deployment_key, provisioning_key,
					pkg_path, "package", target_path);

				// move dbs from package directory into (pEp) user directory
				for (auto const& direntry : std::filesystem::directory_iterator{ target_path }) {
					std::filesystem::path source = direntry.path();
					std::filesystem::rename(direntry.path(), pep_user_path / source.filename());
				}
				// remove provisioning package and extraction directory
				std::filesystem::remove(pkg_path);
				std::filesystem::remove(target_path);

				provisionRegKey.SetValue(ProvisioningIsProvisionedRegKey, L"True");
				provisioning_log_info << "Provisioning has finished succesfully.";
			}
			catch (std::runtime_error& e)
			{
				provisioning_log_error << "Provisioning failed: " << e.what();
			}
			catch (std::exception& e)
			{
				provisioning_log_error << "Provisioning failed: " << e.what();
			}
		}
	}


	bool LocalProvisioning::createDirIfNotExists(const std::filesystem::path& path)
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


	bool LocalProvisioning::convertBool(const std::wstring& in)
	{
		bool ret = false;
		if (in.size() < 1)
			return false;
		std::wstring s = in;
		boost::to_lower(s);
		std::wistringstream(s) >> std::boolalpha >> ret;
		return ret;
	}

	std::wstring LocalProvisioning::defaultProvisioningPath()
	{
		std::wstring pep_user_path = SignedPackage::pEp_locations.at("PER_USER_DIRECTORY");
		std::filesystem::path provisioning_path(pep_user_path);
		provisioning_path /= "Provisioning";
		return provisioning_path.c_str();
	}


	

} // namespaece pEp


