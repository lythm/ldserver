#ifndef __NET_BOOST_ASIO__
#define __NET_BOOST_ASIO__

#if defined(_WIN32) || defined(_WIN64)


#include "core/Network.h"
#include <boost/asio.hpp>


namespace ldserver
{
	class Network_BoostASIO : public Network
	{
	public:
		Network_BoostASIO(void);
		virtual ~Network_BoostASIO(void);

		bool													Initialize();
		void													Release();
		void													Update();

		bool													Listen(const listener& l);


	private:
		boost::asio::io_service									m_io;
	};


}

#endif

#endif