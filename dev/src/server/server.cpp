// server.cpp : 定义控制台应用程序的入口点。
//



#include <stdio.h>

#include "ServerApp.h"


int main(int argc, char* argv[])
{
	using namespace ldserver;

	ServerApp app;

	app.Run();

	return 0;
}

