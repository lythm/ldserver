#ifndef __NETWORK_HEADER__
#define __NETWORK_HEADER__


#include "platform\platform.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#if defined(_WIN32) || defined(_WIN64)
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0501
#endif
#endif
#include <boost/asio.hpp>

#include "core/linked.h"

namespace ldserver
{
	class Network
	{
	public:

		struct _socket : public Linked<_socket>
		{
			_socket()
			{
				_remote_addr.from_string("0.0.0.0");
				_port = 0;
			}
			boost::asio::ip::address									_remote_addr;
			uint32														_port;
		};
		
		typedef boost::shared_ptr<_socket>								socket_ptr;

		struct _acceptor : public Linked<_acceptor>
		{
			_acceptor()
			{
				_addr.from_string("0.0.0.0");
				_port = 0;
				_max_client = 0;
			}

			boost::asio::ip::address									_addr;
			uint32														_port;
			uint32														_max_client;
		};

		typedef boost::shared_ptr<_acceptor>							acceptor_ptr;

		enum op_code
		{
			op_accept,
			op_recv,
			op_sent,
			op_abort,
			op_error,

		};

		struct op_context
		{
			op_code														_op;
			void*														_handler_context;
		};

		typedef boost::function<void (op_context*)>						op_handler;
					

		virtual bool													Initialize()					= 0;
		virtual void													Release()						= 0;
		virtual void													Update()						= 0;

		virtual acceptor_ptr											Accept(const boost::asio::ip::address& addr, 
																					uint32 port,
																					uint32 max_client,
																					op_handler handler)	= 0;

		virtual void													Connect()						= 0;
		virtual void													Send()							= 0;
		virtual void													Close()							= 0;


	protected:
		Network(void){}
		virtual ~Network(void){}
	private:

	};
}



#endif
