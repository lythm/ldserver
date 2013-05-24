#pragma once

#include <boost/enable_shared_from_this.hpp>

namespace ldserver
{
	class Device;

	class _DLL_CLASS CoreApi : public boost::enable_shared_from_this<CoreApi>
	{
	public:
		CoreApi(void);
		virtual ~CoreApi(void);


		bool											Initialize();
		void											Release();
		void											Update();

		Device*											FindDevice(uint64 id);

		std::vector<std::string>						AppSettings(const std::string& key);

	private:
		
		DeviceManagerPtr								m_pDeviceManager;

		AppConfigPtr									m_pConfig;
	};
}
