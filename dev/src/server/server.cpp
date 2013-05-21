// server.cpp : 定义控制台应用程序的入口点。
//

#include "server_pch.h"

#include <stdio.h>

#include "ServerApp.h"


#include "../network/Network_BoostASIO.h"
#include <boost/exception/all.hpp>

void on_accept(ldserver::Network::op_context* context)
{

}

int main(int argc, char* argv[])
{
	using namespace ldserver;


	Network_BoostASIO net;

	net.Initialize();

	boost::asio::ip::address addr;


	net.Accept(boost::asio::ip::address::from_string("127.0.0.1"), 8899, 10, on_accept);

	try
	{

		while(true)
		{
			net.Update();

			Sleep(1);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	net.Release();







	ServerApp app;

	app.Run();

	return 0;
}

