#ifdef __linux__

#include "network/Network_Epoll.h"


namespace ldserver
{
	Network_Epoll::Network_Epoll(void)
	{
	}


	Network_Epoll::~Network_Epoll(void)
	{
	}

}

_DLL_API ldserver::Device* device_alloc()
{
	return new ldserver::Network_Epoll;
}
_DLL_API void device_free(ldserver::Device* pDevice)
{
	delete (ldserver::Network_Epoll*)pDevice;

}
#endif