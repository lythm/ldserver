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

#include "core/Device.h"
#include "core/device_id.h"

namespace ldserver
{
	class _DLL_CLASS Network : public Device
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
			uint64														_error;
			socket_ptr													_sock;
		};

		typedef boost::function<void (op_context*)>						op_handler;
					


		virtual std::string												GetName(){return "device_network";};
		virtual bool													Initialize(CoreApiPtr pCore)	= 0;
		virtual void													Release()						= 0;
		virtual void													Update()						= 0;

		virtual acceptor_ptr											Listen(const boost::asio::ip::address& addr, 
																					uint32 port,
																					uint32 max_client,
																					op_handler handler)	= 0;

		//virtual void													Connect()						= 0;
		//virtual void													Send()							= 0;
		virtual void													Close(acceptor_ptr acc)			= 0;
		virtual void													Close(socket_ptr sock)			= 0;


	protected:
		Network(void) :Device(dev_network){}
		virtual ~Network(void){}
	private:

	};
}



#endif
