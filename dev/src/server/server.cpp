// server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "server_pch.h"

#include <stdio.h>

#include "ServerApp.h"


int main(int argc, char* argv[])
{
	using namespace ldserver;

	ServerApp app;

	app.Run();

	return 0;
}

