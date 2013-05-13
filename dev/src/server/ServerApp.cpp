#include "ServerApp.h"

#include "platform/platform.h"

namespace ldserver
{
	ServerApp::ServerApp(void)
	{
	}


	ServerApp::~ServerApp(void)
	{
	}

	void ServerApp::Run()
	{
		if(AppInit() == false)
		{
			return;
		}

		printf("server started.");

		MainLoop();

		printf("server stopped.");

		AppRelease();
	}
	void ServerApp::MainLoop()
	{

		while(true)
		{
			ldserver::sleep(1);
		}
	}
	bool ServerApp::AppInit()
	{
		return true;
	}
	void ServerApp::AppRelease()
	{
	}
}
