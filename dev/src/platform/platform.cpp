#include "platform/platform.h"

#include <string>


#if defined(_WIN32) || defined(_WIN64)

namespace ldserver
{

	uint64	get_tick()
	{
		return GetTickCount();
	}

	void* load_module(const char* szModule)
	{
		return LoadLibraryA(szModule);
	}
	void unload_module(void* mod)
	{
		FreeLibrary((HMODULE)mod);
	}

	void* find_proc(void* mod, const char* szProc)
	{
		return GetProcAddress((HMODULE)mod, szProc);
	}

	void sleep(uint32 ms)
	{
		Sleep(ms);
	}

	uint64 create_process(const char* szFile, const char* argv[])
	{
		std::string cmdline = ""; 

		for(int i = 0; argv[i]; ++i)
		{
			cmdline += argv[i];
			cmdline += " ";
		}

		std::string filename(szFile);

		//cmdline = filename + " " + cmdline;

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		if(FALSE == CreateProcessA(szFile, (char*)cmdline.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			return uint64(-1);
		}

		return pi.dwProcessId;
	}

	void kill_process(uint64 pid)
	{
		HANDLE processhandle = OpenProcess(1,0,(DWORD)pid);
		if(processhandle !=NULL)
			TerminateProcess(processhandle,0);
	}

	int32 int32_interlocked_add(volatile long* v, long a)
	{
		return InterlockedExchangeAdd(v, a);
	}


	uint64	get_pid()
	{
		return _getpid();
	}


}


#endif






#ifdef __linux__


namespace ldserver
{

	uint64 get_tick()
	{
		struct timeval current;
		gettimeofday(&current,NULL);
		return current.tv_sec*1000+ current.tv_usec/1000;
		//timespec current;
		//clock_gettime(CLOCK_MONOTONIC, &current);
		//return current.tv_sec*1000 + current.tv_nsec/1000;

	}
	void* load_module(const char* szModule)
	{
		void* ret = dlopen(szModule,RTLD_NOW);

		if(ret == NULL)
		{
			printf("# platform::load_module[%s] failed %s\n", szModule, dlerror());
		}
		return ret;
	}
	void unload_module(void* mod)
	{
		dlclose(mod);
	}

	void* find_proc(void* mod, const char* szProc)
	{
		return dlsym(mod, szProc);
	}

	void sleep(uint32 ms)
	{
		usleep( ms * 1000);
	}


	uint64 create_process(const char* szFile, const char* argv[])
	{
		uint64 pid = fork();

		if(pid == 0)
		{
			execv(szFile, (char*const*)argv);
		}

		return pid;
	}
	void kill_process(uint64 pid)
	{
		kill(pid,9);		
	}

	int32 int32_interlocked_add(volatile long* v, long a)
	{
		return __sync_add_and_fetch(v, a);
	}



	uint64	get_pid()
	{
		return getpid();
	}


}


#endif
