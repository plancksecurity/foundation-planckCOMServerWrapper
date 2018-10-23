// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlsafe.h>

#include <comutil.h>
#include <comdef.h>

#include <Wininet.h>
#include <intsafe.h>
#include <bcrypt.h>

#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <random>
#include <iomanip>

#include <assert.h>

#include <pEp/pEpEngine.h>
#include <pEp/keymanagement.h>
#include <pEp/message_api.h>
#include <pEp/stringpair.h>
#include <pEp/blacklist.h>
#include <pEp/sync_api.h>
#include <pEp/openpgp_compat.h>
