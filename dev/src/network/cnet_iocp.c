#include "network/cnet.h"

#if defined(_WIN32) || defined(_WIN64)



unsigned int		cnet_init(int max_fd)
{

	return 0;
}
void				cnet_fin(int cnet)
{

	
}

void				cnet_listen(struct cnet_inst* net, struct cnet_fd* fd)
{


}

void				cnet_connect(struct cnet_inst* net, struct cnet_fd* fd)
{

}

void				cnet_accept(struct cnet_inst* net, struct cnet_fd* fd)
{

}

unsigned int		cnet_recv(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes)
{

	return 0;
}
void				cnet_send(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes)
{

}

unsigned int		cnet_update(struct cnet_inst* net)
{

	return 0;
}

void				cnet_close(struct cnet_inst* net, struct cnet_fd* fd)
{

}





#endif
