#pragma once

#include <boost/smart_ptr.hpp>

#if defined(_WIN32) || defined(_WIN64)
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0501
#endif
#endif
#include <boost/asio.hpp>


#include "platform/platform.h"

#include "core/core_ptr.h"

#include "core/CoreApi.h"

#include "core/DLMod.h"
#include "core/Mod.h"
#include "core/Device.h"




