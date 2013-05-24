#ifndef __NET_BOOST_ASIO__
#define __NET_BOOST_ASIO__

#if defined(_WIN32) || defined(_WIN64)


#include "core/Network.h"

namespace ldserver
{
	class _DLL_CLASS Network_BoostASIO : public Network
	{
	public:

		struct _acceptor_asio : public _acceptor
		{
			_acceptor_asio(boost::asio::io_service& io) : _acceptor(io)
			{

			}
			boost::asio::ip::tcp::endpoint						_ep;
			boost::asio::ip::tcp::acceptor						_acceptor;

			op_handler											_handler;
			op_context											_context;
		};

		struct _socket_asio : public _socket
		{
			_socket_asio(boost::asio::io_service& io) : _sock(io)
			{
			}
			boost::asio::ip::tcp::socket						_sock;

		};

		Network_BoostASIO(void);
		virtual ~Network_BoostASIO(void);

		bool													Initialize(CoreApiPtr pCore);
		void													Release();
		void													Update();

		acceptor_ptr											Listen(const boost::asio::ip::address& addr, 
																					uint32 port,
																					uint32 max_client,
																					op_handler handler);

		socket_ptr												Connect(const boost::asio::ip::address& addr, uint32 port);
		void													Recv(socket_ptr sock, op_handler handler);
		void													Send(socket_ptr sock, void* buffer, uint32 bytes, op_handler handler);
		void													Close(acceptor_ptr acc);
		void													Close(socket_ptr sock);
	private:
		void													start_accept(acceptor_ptr acc);
		void													_on_accept(acceptor_ptr acc, socket_ptr sock, const boost::system::error_code& error);

	private:
		boost::asio::io_service									m_io;

		acceptor_ptr											m_acceptors;
		socket_ptr												m_socks;
		
	};
}

#endif

#endif
