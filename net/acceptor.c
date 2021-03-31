
#include "acceptor.h"
#include <unistd.h>
#include <functional>
#include "channel.h"
#include <netinet/in.h>
#include <iostream>

Acceptor::Acceptor( EventLoop* loop, int fd ): _loop(loop), _chan( new Channel(loop, fd ) )
{

}

void Acceptor::NewConnection(int fd)
{
	struct sockaddr_in cli_addr;
	socklen_t len = sizeof( cli_addr );
	int connfd = accept( fd, (sockaddr*)&cli_addr, &len);
	Channel* conn_ch = new Channel( _loop, connfd );
	conn_ch->SetReadCB( std::bind(&Acceptor::HandleRead, this, std::placeholders::_1) );
	conn_ch->EnableRead();
	std::cout << "NewConnection " << connfd << "\n";
}
	
void Acceptor::HandleRead( int fd )
{
	std::cout << "HandleRead " << fd << std::endl;
}

void Acceptor::Start()
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(9999);
	bind( _chan->FD(), (sockaddr*)&serv_addr, sizeof(serv_addr) );
	listen( _chan->FD(), 10 );
	_chan->SetReadCB( std::bind(&Acceptor::NewConnection, this, std::placeholders::_1) );
	_chan->EnableRead();
}
