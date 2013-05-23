#include "mod_echo_pch.h"
#include "EchoServer.h"


EchoServer::EchoServer(void)
{
}


EchoServer::~EchoServer(void)
{
}
bool EchoServer::Initialize(ldserver::CoreApiPtr pCoreApi)
{
	return true;
}
EchoServer::update_result EchoServer::Update(ldserver::uint64 tick)
{
	
	return ret_continue;
}

void EchoServer::Release()
{

}









_DLL_API ldserver::Mod* mod_alloc()
{
	return new EchoServer;
}

_DLL_API void mod_free(ldserver::Mod* pMod)
{
	delete (EchoServer*)pMod;
}
