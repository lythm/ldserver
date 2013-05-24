#pragma once


namespace ldserver
{
	enum device_id
	{
		dev_sys						= 0,
		dev_network					= dev_sys + 1,
		dev_custom					= 0xf0000000,
	};
}