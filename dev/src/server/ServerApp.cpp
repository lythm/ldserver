#include "server_pch.h"
#include "ServerApp.h"

#include "platform/platform.h"

#include "core/Network.h"

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

		printf("server started.\n");

		MainLoop();

		printf("server stopped.\n");

		AppRelease();
	}
	void ServerApp::MainLoop()
	{
		while(true)
		{
			
			m_pCoreApi->Update();


			ldserver::sleep(1);
		}
	}
	bool ServerApp::AppInit()
	{
		m_pCoreApi = CoreApiPtr(new CoreApi);
		if(m_pCoreApi->Initialize() == false)
		{
			return false;
		}

		return true;
	}
	void ServerApp::AppRelease()
	{


		if(m_pCoreApi)
		{
			m_pCoreApi->Release();
			m_pCoreApi.reset();
		}
	}
}

