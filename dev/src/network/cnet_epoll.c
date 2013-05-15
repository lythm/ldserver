#include "network/cnet.h"

#ifdef __linux__

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int					cnet_init(int max_fd)
{
	int epfd = -1;

	epfd = epoll_create(max_fd + 1);

	return epfd;
}
void				cnet_fin(int cnet)
{
	close(cnet);
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
