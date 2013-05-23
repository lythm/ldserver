#pragma once

namespace ldserver
{
	class ModManager
	{
	public:

		struct ModInfo
		{
			ModInfo()
			{
				m_pMod = NULL;
				m_pDL = NULL;
			}
			Mod*							m_pMod;
			DLMod*							m_pDL;
		};


		ModManager(void);
		virtual ~ModManager(void);


		bool										Initialize(CoreApiPtr pCore, const char* szMod);

		void										Release();

		void										Update();


	private:
		bool										Load(const char* szFile);
		void										Unload();

	private:
		ModInfo										m_mod;

		CoreApiPtr									m_pCore;
	};


}