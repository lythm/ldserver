#pragma once

#include "platform/platform.h"

namespace ldserver
{
	class _DLL_CLASS AppConfig
	{
		
	public:

		typedef std::string											app_string;
		typedef char												app_char;

		typedef std::map<app_string, std::vector<app_string> >		SettingsMap;

		AppConfig(void);
		virtual ~AppConfig(void);

		void														Clear();

		bool														Load(const char* cfg);

		void														AddSetting(const app_string& key, const app_string& value);

		void														ReplaceSetting(const app_string& key, std::vector<app_string>& list);

		const std::vector<app_string>&								Settings(const app_string& key);

		const SettingsMap&											Settings();
	private:
		void														ParseLine(app_char* line);
		app_char*													ReplaceWhiteLeft(app_char* line, app_char c);
		app_char*													FindWhite(app_char* line);
		void														ReplaceWhiteRight(app_char* line, app_char c);
	private:
		SettingsMap													m_settings;
	};
}