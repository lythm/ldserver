#if defined(_WIN32) || defined(_WIN64)

#include "Network_BoostASIO.h"
#include "boost/bind.hpp"

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
	Network_BoostASIO::acceptor_ptr	Network_BoostASIO::Listen(const boost::asio::ip::address& addr, uint32 port, uint32 max_client, op_handler handler)
	{
		using namespace boost::asio::ip;
		
		boost::shared_ptr<_acceptor_asio> acc = boost::shared_ptr<_acceptor_asio>(new _acceptor_asio(m_io));

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
		

		
		if(m_acceptors == nullptr)
		{
			m_acceptors = acceptor_ptr(acc);
		}
		else
		{
			_acceptor::Insert(m_acceptors, acceptor_ptr(acc));
		}

		start_accept(acc);
		
		return acc;
	}
	void Network_BoostASIO::_on_accept(acceptor_ptr acc, socket_ptr sock, const boost::system::error_code& error)
	{
		using namespace boost;


		shared_ptr<_acceptor_asio> pa = dynamic_pointer_cast<_acceptor_asio>(acc);


		if(error)
		{
			std::cout << error.message() << std::endl;
			

			pa->_context._error = error.value();
			pa->_context._op = op_abort;
			pa->_context._sock = sock;
			pa->_handler(&pa->_context);
			
			Close(sock);

			start_accept(acc);
			return;
		}

		std::cout << "new conn" << std::endl;

		pa->_context._error = error.value();
		pa->_context._op = op_accept;
		pa->_context._sock = sock;
		pa->_handler(&pa->_context);

		start_accept(acc);
	}
	void Network_BoostASIO::start_accept(acceptor_ptr acc)
	{
		using namespace boost::asio::ip;

		boost::shared_ptr<_socket_asio> sock = boost::shared_ptr<_socket_asio>(new _socket_asio(m_io));
		
		if(m_socks == nullptr)
		{
			m_socks = sock;
		}
		else
		{
			_socket::Insert(m_socks, sock);
		}

		((_acceptor_asio*)acc.get())->_acceptor.async_accept(sock->_sock, boost::bind(&Network_BoostASIO::_on_accept, this, acc, sock, boost::asio::placeholders::error));
	}
	void Network_BoostASIO::Close(acceptor_ptr acc)
	{
		using namespace boost;
		if(acc == nullptr)
		{
			return;
		}
		shared_ptr<_acceptor_asio> pa = dynamic_pointer_cast<_acceptor_asio>(acc);

		pa->_acceptor.close();

		pa->Unlink();

	}
	void Network_BoostASIO::Close(socket_ptr sock)
	{
		using namespace boost;

		if(sock == nullptr)
		{
			return;
		}
		shared_ptr<_socket_asio> p_sock = dynamic_pointer_cast<_socket_asio>(sock);
		p_sock->_sock.close();

		sock->Unlink();
	}
	Network_BoostASIO::socket_ptr Network_BoostASIO::Connect(const boost::asio::ip::address& addr, uint32 port)
	{
		using namespace boost::asio::ip;

		boost::shared_ptr<_socket_asio> sock = boost::shared_ptr<_socket_asio>(new _socket_asio(m_io));
		
		if(m_socks == nullptr)
		{
			m_socks = sock;
		}
		else
		{
			_socket::Insert(m_socks, sock);
		}

		sock->_sock.connect(tcp::endpoint(addr, port));

		return sock;
	}
	void Network_BoostASIO::Recv(socket_ptr sock, void* buffer, uint32 bytes, op_handler handler)
	{
		boost::shared_ptr<_socket_asio> asock = boost::dynamic_pointer_cast<_socket_asio>(sock);

		//asock->_sock.async_receive(boost::asio::buffer(buffer, bytes), 0, handler);
		//asock->_sock.async_receive(
	}
	void Network_BoostASIO::Send(socket_ptr sock, void* buffer, uint32 bytes, op_handler handler)
	{
		boost::shared_ptr<_socket_asio> asock = boost::dynamic_pointer_cast<_socket_asio>(sock);
	}
}

#endif
