#include "core_pch.h"
#include "core/DeviceManager.h"
#include "core/DLMod.h"
#include "core/Device.h"
namespace ldserver
{
	DeviceManager::DeviceManager(CoreApiPtr pCore)
	{
		m_pCore = pCore;
	}


	DeviceManager::~DeviceManager(void)
	{
	}
	bool DeviceManager::Load(const std::vector<std::string>& devs)
	{
		const std::vector<std::string>& devices = devs;


		for(size_t i = 0; i < devices.size(); ++i)
		{
			bool ret = LoadDevice(devices[i].c_str());
			if(ret == false)
			{
				printf("#failed to load device: %s\n", devices[i].c_str());

				return false;
			}
		}

		return true;
	}

	

	void DeviceManager::UnLoad()
	{
	
		for(int i = (m_devs.size() - 1); i >= 0; --i)
		{
			UnLoadDevice(m_devs[i]);
		}
		m_devs.clear();
	}


	Device* DeviceManager::FindDevice(uint64 id)
	{
		for(size_t i = 0; i < m_devs.size(); ++i)
		{
			if(m_devs[i].pDevice->GetId() == id)
				return m_devs[i].pDevice;
		}
		return NULL;
	}
	bool DeviceManager::LoadDevice(const std::string& dev)
	{
		DLMod* pMod = new DLMod;
		Device* pDevice = NULL;

		if(false == pMod->Load(dev))
		{
			printf("failed load module: %s\n", dev.c_str());
			return false;
		}

		PTR_ALLOC_DEVICE dev_alloc = (PTR_ALLOC_DEVICE)pMod->GetProcAddr(FUNC_ALLOC_DEVICE_NAME);

		if(dev_alloc == NULL)
		{
			printf("failed to get dev_alloc\n");
			pMod->Unload();
			delete pMod;
			return false;
		}

		pDevice = dev_alloc();
		if(pDevice == NULL)
		{
			printf("failed to alloc device\n");
			pMod->Unload();
			delete pMod;
			return false;
		}

		DeviceInfo info;
		info.pDevice = pDevice;
		info.m_lib = pMod;

		if(NULL != FindDevice(pDevice->GetId()))
		{
			UnLoadDevice(info);
			return false;
		}

		std::string devName = info.pDevice->GetName();

		if(info.pDevice->Initialize(m_pCore) == false)
		{
			printf("failed to init device\n");
			UnLoadDevice(info);

			return false;
		}

		std::string msg = std::string("#device ") + "[" + devName + "] (" + dev + ") loaded.\n";

		printf("%s", msg.c_str());
		m_devs.push_back(info);

		return true;
	}
	void DeviceManager::UnLoadDevice(DeviceInfo& d)
	{
		if(d.m_lib == NULL)
			return;

		if(d.m_lib->IsLoaded() == false)
			return;

		if(d.pDevice != NULL)
		{
			d.pDevice->Release();

			PTR_FREE_DEVICE dev_free = (PTR_FREE_DEVICE)d.m_lib->GetProcAddr(FUNC_FREE_DEVICE_NAME);

			if(dev_free)
			{
				dev_free(d.pDevice);
			}
		}

		d.m_lib->Unload();

		delete d.m_lib;
		d.m_lib = NULL;
	}
}
