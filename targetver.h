#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <WinSDKVer.h>

#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0A00 // build for Windows 10 
#endif

#define WINVER _WIN32_WINNT 
