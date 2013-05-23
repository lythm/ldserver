#include "server_pch.h"
#include "ModManager.h"

namespace ldserver
{
	ModManager::ModManager(void)
	{
	}


	ModManager::~ModManager(void)
	{
	}
	bool ModManager::Initialize(CoreApiPtr pCore, const char* szMod)
	{
		m_pCore = pCore;

		m_mod.m_pDL = new DLMod;
		if(false == Load(szMod))
			return false;

		return true;
	}

	void ModManager::Release()
	{
		Unload();
		delete m_mod.m_pDL;
		
		m_mod.m_pMod = NULL;
		m_mod.m_pDL = NULL;

	}
	void ModManager::Update()
	{
		if(m_mod.m_pMod)
		{
			m_mod.m_pMod->Update(0);
		}
	}
	bool ModManager::Load(const char* szFile)
	{
		if(false == m_mod.m_pDL->Load(szFile))
			return false;

		MOD_ALLOC s_alloc = (MOD_ALLOC)m_mod.m_pDL->GetProcAddr(MOD_ALLOC_NAME);

		if(s_alloc == NULL)
		{
			m_mod.m_pDL->Unload();
			return false;
		}

		m_mod.m_pMod = s_alloc();

		if(false == m_mod.m_pMod->Initialize(m_pCore))
		{
			m_mod.m_pDL->Unload();
			return false;
		}

		return true;
	}
	void ModManager::Unload()
	{
		if(m_mod.m_pMod == NULL)
			return;

		m_mod.m_pMod->Release();

		MOD_FREE s_free = (MOD_FREE)m_mod.m_pDL->GetProcAddr(MOD_FREE_NAME);

		if(s_free)
		{
			s_free(m_mod.m_pMod);
		}
		m_mod.m_pMod = NULL;

	}
}
