// server.cpp : 定义控制台应用程序的入口点。
//

#include "server_pch.h"

#include <stdio.h>

#include "ServerApp.h"


#include "../network/Network_BoostASIO.h"
#include <boost/exception/all.hpp>


ldserver::Network::socket_ptr g_sock;
void on_accept(ldserver::Network::op_context* context)
{
	using namespace ldserver;

	switch(context->_op)
	{
	case Network::op_accept:
		g_sock = context->_sock;
		break;

	case Network::op_abort:
		{
			std::cout << context->_error << std::endl;
		}
		break;
	default:
		assert(0);
		break;
	}
}

int main(int argc, char* argv[])
{
	using namespace ldserver;


	Network_BoostASIO net;

	net.Initialize();

	boost::asio::ip::address addr;

	Network::acceptor_ptr p_acc;

	try
	{
		p_acc = net.Listen(boost::asio::ip::address::from_string("192.168.0.203"), 9118, 10, on_accept);

		for(int i = 0; i < 500000; ++i)
		{
			net.Update();

			Sleep(1);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	net.Close(g_sock);
	net.Close(p_acc);

	net.Release();

	ServerApp app;

	app.Run();

	return 0;
}

