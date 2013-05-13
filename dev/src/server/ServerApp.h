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
		void											MainLoop();
		bool											AppInit();
		void											AppRelease();
	};


}