// Copyright planck security 2023
// 07.08.2023/IP - extracted logfile handling for provisioning activities

#pragma once

namespace pEp
{
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