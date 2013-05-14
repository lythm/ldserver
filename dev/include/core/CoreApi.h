#pragma once

namespace ldserver
{
	class _DLL_CLASS CoreApi
	{
	public:
		CoreApi(void);
		virtual ~CoreApi(void);


		bool											Initialize();
		void											Release();
		void											Update();
	};


}