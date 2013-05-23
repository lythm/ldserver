#include "core_pch.h"
#include "..\..\include\core\DLMod.h"

namespace ldserver
{
	DLMod::DLMod()
	{
		m_filename		= "";
		m_lib			= NULL;
	}

	DLMod::~DLMod(void)
	{
		Unload();
	}
	bool DLMod::Reload()
	{
		Unload();
		m_lib = load_module(m_filename.c_str());
		if(m_lib == NULL)
			return false;
		return true;
	}
	void DLMod::Unload()
	{
		if(m_lib)
		{
			unload_module(m_lib );
			m_lib = NULL;
		}
	}
	bool DLMod::Load(const std::string& szFile)
	{
		m_filename = szFile;
		return Reload();
	}
	void* DLMod::GetProcAddr(const char* szProc) const
	{
		if(m_lib == NULL)
			return NULL;

		void* addr = NULL;
		addr = find_proc(m_lib, szProc);
		return addr;
	}
	const std::string& DLMod::GetFileName()
	{
		return m_filename;
	}
	bool DLMod::IsLoaded() const
	{
		return m_lib != NULL;
	}

}
