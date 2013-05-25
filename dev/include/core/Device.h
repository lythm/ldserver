#pragma once


#include "platform/platform.h"
#include "core/core_ptr.h"

namespace ldserver
{
	class _DLL_CLASS Device
	{
	public:

		uint64													GetId()
		{
			return m_id;
		}

		virtual std::string										GetName()															= 0;
		virtual bool											Initialize(CoreApiPtr pCore)										= 0;
		virtual void											Release()															= 0;

		virtual void											Update(){}

	protected:
		Device(uint64 id)
		{
			m_id = id;
		}
		virtual ~Device(){}

	protected:

		uint64													m_id;
	};


}



typedef ldserver::Device* (*PTR_ALLOC_DEVICE)();
typedef void (*PTR_FREE_DEVICE)(ldserver::Device*);

#define FUNC_ALLOC_DEVICE_NAME									"device_alloc"
#define FUNC_FREE_DEVICE_NAME									"device_free"

