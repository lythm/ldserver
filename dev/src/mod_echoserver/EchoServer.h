#pragma once


class EchoServer : public ldserver::Mod
{
public:
	EchoServer(void);
	virtual ~EchoServer(void);

	bool											Initialize(ldserver::CoreApiPtr pCoreApi);
	update_result									Update(ldserver::uint64 tick);
	void											Release();

};

