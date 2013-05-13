#pragma once

#ifndef _PLATFORM_H_
#define _PLATFORM_H_



#if defined(WIN32) || defined(_WIN64)

#pragma warning(disable: 4251)
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <io.h>
#include <process.h>


#ifndef _WINDLL

#define _DLL_API									extern"C" __declspec(dllimport)
#define _DLL_CLASS									__declspec(dllimport)
#else

#define _DLL_API									extern"C" __declspec(dllexport)
#define _DLL_CLASS									__declspec(dllexport)
#endif

#endif

#ifdef __linux__

#include <dlfcn.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <iconv.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <errno.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#define _DLL_API									extern"C"
#define _DLL_CLASS

#endif


namespace ldserver
{
	typedef unsigned char							uint8;
	typedef unsigned short							uint16;
	typedef unsigned int							uint32;

	typedef char									int8;
	typedef short									int16;
	typedef int										int32;


#if defined(WIN32) || defined(_WIN64)
	typedef __int64									int64;
	typedef unsigned __int64						uint64;
#endif


#ifdef __linux__
	typedef long long								int64;
	typedef unsigned long long						uint64;
#endif
}

namespace ldserver
{

	_DLL_API uint64						get_tick();


	_DLL_API void* 						load_module(const char* szModule);
	_DLL_API void						unload_module(void* mod);

	_DLL_API void*						find_proc(void* mod, const char* szProc);

	_DLL_API void						sleep(uint32 ms);

	_DLL_API void						console_write(const wchar_t* szText);

	_DLL_API uint64						create_process(const char* szFile, const char* argv[]);
	_DLL_API void						kill_process(uint64 pid);

	_DLL_API int32						int32_interlocked_add(volatile long* v, long a);


	_DLL_API uint64						get_pid();

}

#endif






