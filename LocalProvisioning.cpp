#include "stdafx.h"
#include "unpack.hh"
#include "LocalProvisioning.h"


namespace pEp
{

void init_provisioning_log();


void LocalProvisioning::Run()
{
	init_provisioning_log();
	pEp::utility::RegistryKey provisionRegKey(ProvisioningRegKey);
	std::wstring isProvisioned = provisionRegKey.GetValue(ProvisioningIsProvisionedRegKey,
		L"False");
	std::wstring localFolder = provisionRegKey.GetValue(ProvisioningLocalFolderRegKey,
		LocalProvisioning::defaultProvisioningPath());
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
			LocalProvisioning::create_dir_if_not_exists(provisioning_path);

		if (!std::filesystem::exists(pkg_path)) // there is no package to provision
			return;

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

		provisioning_log_info << "Starting Provisioning";

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


bool LocalProvisioning::create_dir_if_not_exists(const std::filesystem::path& path)
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


bool LocalProvisioning::convert_bool(const std::wstring& in)
{
	bool ret;
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


void init_provisioning_log()
{
	static bool initialized = false;
	if (initialized)
		return;

	static const std::string COMMON_FMT("[%TimeStamp%][%Function%]:  %Message%");
	boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

	// Output message to file, rotates when file reached 1mb or at midnight every day. Each log file
	// is capped at 1mb and total is 20mb
	boost::filesystem::path user_dir(SignedPackage::pEp_locations.at("PER_USER_DIRECTORY"));
	boost::filesystem::path log_path = user_dir / "Logs" / "provisioning_log%3N.txt";
	boost::log::add_file_log(
		boost::log::keywords::file_name = log_path.c_str(),
		boost::log::keywords::rotation_size = 1 * 1024 * 1024,
		boost::log::keywords::max_size = 20 * 1024 * 1024,
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		boost::log::keywords::format = COMMON_FMT,
		boost::log::keywords::auto_flush = true
	);

	boost::log::add_common_attributes();

	// Only output message with INFO or higher severity in Release
#ifndef _DEBUG
	boost::log::core::get()->set_filter(
		boost::log::trivial::severity >= boost::log::trivial::info
	);
#endif

	initialized = true;
}



} // namespaece pEp


