#pragma once



namespace ldserver
{

	class ServerApp
	{
	public:
		ServerApp(void);
		virtual ~ServerApp(void);

		void											Run();

	private:
		virtual void									MainLoop();
		virtual bool									AppInit();
		virtual void									AppRelease();



	private:
		CoreApiPtr										m_pCoreApi;
		ModManagerPtr									m_pModManager;
	};
}
