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
#include <atlwin.h>

#include <comutil.h>
#include <comdef.h>
#include <Shlobj.h>

#include <Wininet.h>
#include <intsafe.h>
#include <bcrypt.h>

#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <random>
#include <regex>
#include <iomanip>

#include <assert.h>

#include <Strsafe.h>

#include <pEp/platform.h>
#include <pEp/sync_api.h>
#include <pEp/keymanagement.h>
#include <pEp/key_reset.h>
#include <pEp/openpgp_compat.h>
#include <pEp/sync_codec.h>
#include <pEp/mime.h>

#include <pEp/locked_queue.hh>
#include <pEp/pc_container.hh>
#include <pEp/passphrase_cache.hh>
#include <pEp/callback_dispatcher.hh>
#include <pEp/status_to_string.hh>

#include <pEp/group.h>
#include <pEp/Adapter.hh>

#include "utf8_helper.h"
#include "pEp_utility.h"

#include <boost/algorithm/string/predicate.hpp>

#include "utf8_helper.h"
