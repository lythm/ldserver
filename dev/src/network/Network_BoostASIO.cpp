#if defined(_WIN32) || defined(_WIN64)

#include "Network_BoostASIO.h"

namespace ldserver
{
	Network_BoostASIO::Network_BoostASIO(void)
	{
	}


	Network_BoostASIO::~Network_BoostASIO(void)
	{
	}
	bool Network_BoostASIO::Initialize()
	{
		return true;
	}
	void Network_BoostASIO::Release()
	{
		m_io.stop();
	}
	void Network_BoostASIO::Update()
	{
		m_io.poll();
	}
	bool Network_BoostASIO::Listen(const listener& l)
	{
		boost::asio::ip::address
		return true;
	}
}

#endif
