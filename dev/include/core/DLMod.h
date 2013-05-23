#pragma once

namespace ldserver
{
	class _DLL_CLASS DLMod
	{
	public:
		DLMod(void);
		virtual ~DLMod(void);

		bool							Load(const std::string& szFile);

		bool							Reload();

		void							Unload();

		void*							GetProcAddr(const char* szProc) const;

		const std::string&				GetFileName();

		//! Loaded or not
		bool							IsLoaded() const;

	private:
		DLMod(const DLMod& other);

	private:
		std::string						m_filename;
		void*							m_lib;

	};


}