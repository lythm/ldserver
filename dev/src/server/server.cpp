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

	ServerApp app;

	app.Run();

	return 0;
}

