#pragma once

namespace ldserver
{
	class DLMod;
	class Device;

	class _DLL_CLASS DeviceManager
	{
		struct DeviceInfo
		{
			DLMod*									m_lib;
			Device*									pDevice;
		};

	public:
		DeviceManager(CoreApiPtr pCore);
		virtual ~DeviceManager(void);

		
		bool										Load(const std::vector<std::string>& devs);
		void										UnLoad();

		void										Update();

		bool										LoadDevice(const std::string& dev);
		void										UnLoadDevice(DeviceInfo& d);

		Device*										FindDevice(uint64 id);

	private:
		std::vector<DeviceInfo>						m_devs;
		CoreApiPtr									m_pCore;
	};


}