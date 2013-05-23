#pragma once

#include "platform/platform.h"


namespace ldserver
{
	class CoreApi;

	class Mod
	{
	public:

		enum update_result
		{
			ret_continue,
			ret_quit,
			ret_abort,
		};

		virtual bool											Initialize(CoreApiPtr pCoreApi)				= 0;
		virtual update_result									Update(uint64 tick)							= 0;
		virtual void											Release()									= 0;


	protected:

		Mod(void){}

		virtual ~Mod(void){}

	};

}

typedef ldserver::Mod* (*MOD_ALLOC)();
typedef void (*MOD_FREE)(ldserver::Mod*);

#define MOD_ALLOC_NAME			"mod_alloc"
#define MOD_FREE_NAME			"mod_free"
