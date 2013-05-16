#ifndef __NET_EPOLL__
#define __NET_EPOLL__

#ifdef __linux__

#include  "core/Network.h"


namespace ldserver
{
	class Network_Epoll : public Network
	{
	public:
		Network_Epoll(void);
		virtual ~Network_Epoll(void);
	};


}

#endif


#endif