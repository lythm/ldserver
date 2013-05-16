#ifndef __NETWORK_HEADER__
#define __NETWORK_HEADER__

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>


namespace ldserver
{
	class Network
	{
	public:

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
			op_code				_op;
		};

		struct conn
		{

		};


		typedef boost::function<void (op_context*)>				op_handler;


		struct listener
		{
			boost::asio::ip::address							addr;
			uint32												max_client;
		};

				

		virtual bool													Initialize()					= 0;
		virtual void													Release()						= 0;
		virtual void													Update()						= 0;

		virtual bool													Listen(const listener& l)		= 0;

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
