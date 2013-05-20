#if defined(_WIN32) || defined(_WIN64)

#include "Network_BoostASIO.h"

namespace ldserver
{
	Network_BoostASIO::Network_BoostASIO(void)
	{
		
	}


	Network_BoostASIO::~Network_BoostASIO(void)
	{
	}
	bool Network_BoostASIO::Initialize()
	{
		
		
		return true;
	}
	void Network_BoostASIO::Release()
	{
		m_io.stop();
	}
	void Network_BoostASIO::Update()
	{
		m_io.poll();
	}
	Network_BoostASIO::acceptor_ptr	Network_BoostASIO::Accept(const boost::asio::ip::address& addr, uint32 port, uint32 max_client, op_handler handler)
	{
		using namespace boost::asio::ip;
		
		_acceptor_asio* acc = new _acceptor_asio(m_io);

		acc->_addr = addr;
		acc->_port = port;
		acc->_max_client = max_client;

		acc->_ep = tcp::endpoint(addr, port);

		acc->_handler = handler;
		acc->_context._handler_context = 0;

		
		acc->_acceptor.open(boost::asio::ip::tcp::v4());
		
		acc->_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acc->_acceptor.bind(acc->_ep);
		acc->_acceptor.listen();
		
		start_accept(acceptor_ptr(acc));
		
		return acceptor_ptr(acc);
	}
	void Network_BoostASIO::_on_accept(socket_ptr sock, const boost::system::error_code& error)
	{

	}
	void Network_BoostASIO::start_accept(acceptor_ptr acc)
	{
		using namespace boost::asio::ip;

		_socket_asio* sock = new _socket_asio;
		


	}
}

#endif
