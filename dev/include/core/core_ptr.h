#pragma once


#include <boost/smart_ptr.hpp>



namespace ldserver
{
	class CoreApi;
	class Network;
	class DeviceManager;
	class AppConfig;

	typedef boost::shared_ptr<AppConfig>						AppConfigPtr;
	typedef boost::shared_ptr<CoreApi>							CoreApiPtr;
	typedef boost::shared_ptr<Network>							NetworkPtr;
	typedef boost::shared_ptr<DeviceManager>					DeviceManagerPtr;

	
}