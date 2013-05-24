#include "core_pch.h"
#include "core/CoreApi.h"
#include "core/DeviceManager.h"
#include "core/AppConfig.h"

namespace ldserver
{
	CoreApi::CoreApi(void)
	{
	}


	CoreApi::~CoreApi(void)
	{
	}
	bool CoreApi::Initialize()
	{
		m_pConfig = AppConfigPtr(new AppConfig);

		if(m_pConfig->Load("./sys.conf")== false)
		{
			return false;
		}

		m_pDeviceManager = DeviceManagerPtr(new DeviceManager(shared_from_this()));

		if(false == m_pDeviceManager->Load(m_pConfig->Settings("device")))
		{
			return false;
		}

		return true;
	}
	void CoreApi::Release()
	{
		if(m_pDeviceManager)
		{
			m_pDeviceManager->UnLoad();
			m_pDeviceManager.reset();
		}


		m_pConfig.reset();
	}
	void CoreApi::Update()
	{
	}
	Device*	CoreApi::FindDevice(uint64 id)
	{
		return m_pDeviceManager->FindDevice(id);
	}
	std::vector<std::string> CoreApi::AppSettings(const std::string& key)
	{
		return m_pConfig->Settings(key);
	}
}
