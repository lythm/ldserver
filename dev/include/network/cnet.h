#pragma once


#ifndef __CNET_HEADER__
#define __CNET_HEADER__


#if defined(_WIN32) || defined(_WIN64)
#ifdef _USRDLL

#define _CNET_API									__declspec(dllexport)
#else
#define _CNET_API									__declspec(dllimport)
#endif
#endif

#ifdef __linux__

#define _CNET_API
#endif


typedef void (*cnet_handler)(struct cnet* net, struct cnet_fd* fd, unsigned int op, unsigned int error);


struct cnet
{
	int				inst;
	int				max_fd;
};

struct cnet_fd
{
	unsigned int	fd;
	cnet_handler	cp_handler;
	void*			cp_handler_context;
};

enum
{
	cnet_op_accept,
	cnet_op_recv,
	cnet_op_send,
	cnet_op_close,
	cnet_op_abort,
};

enum
{
	cnet_error_ok,
	cnet_error_unknown,
};



_CNET_API int				cnet_init(int max_fd);
_CNET_API void				cnet_fin(int cnet);

_CNET_API void				cnet_listen(struct cnet_inst* net, struct cnet_fd* fd);

_CNET_API void				cnet_connect(struct cnet_inst* net, struct cnet_fd* fd);

_CNET_API void				cnet_accept(struct cnet_inst* net, struct cnet_fd* fd);

_CNET_API unsigned int		cnet_recv(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes);
_CNET_API void				cnet_send(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes);

_CNET_API unsigned int		cnet_update(struct cnet_inst* net);

_CNET_API void				cnet_close(struct cnet_inst* net, struct cnet_fd* fd);



/*

	cnet_init();

	cnet_listen();

	cnet_update();

	cnet_fin();

*/



#endif
