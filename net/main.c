

#include "eventloop.h"
#include "channel.h"
#include <unistd.h>
#include "acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	EventLoop loop;
	int fd = socket( AF_INET, SOCK_STREAM, 0 );
	Acceptor acc( &loop, fd );
	acc.Start();
	loop.Loop();
	return 0;
}


