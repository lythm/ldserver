#pragma once


#include <boost\smart_ptr.hpp>



namespace ldserver
{
	class CoreApi;


	typedef boost::shared_ptr<CoreApi>							CoreApiPtr;
}