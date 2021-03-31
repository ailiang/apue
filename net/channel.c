
#include "channel.h"
#include <poll.h>
#include "eventloop.h"
#include <iostream>

const int Channel::NoneEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

Channel::Channel( EventLoop* loop, int fd ) : _loop ( loop ), _fd( fd )
{

}

void Channel::EnableRead()
{
	_events |= ReadEvent;
	UpdateEvents();
}

void Channel::DisableRead()
{
	_events &= ~ReadEvent;
	UpdateEvents();
}

void Channel::EnableWrite()
{
	_events |= WriteEvent;
	UpdateEvents();
}

void Channel::DisableWrite()
{
	_events &= ~WriteEvent;
	UpdateEvents();
}

int Channel::FD() 
{
	return _fd;
}

void Channel::SetREvents( int ev )
{
	_revents = ev;
}

int Channel::Events()
{
	return _events;
}

int Channel::Idx()
{
	return _idx ;
}

void Channel::SetIdx( int i )
{
	_idx = i;
}

void Channel::UpdateEvents()
{
	_loop->UpdateEvents( this );
}

void Channel::HandleEvents()
{
	if( _revents | POLLIN )
	{
		if( _rcb )
		{
			std::cout << " Channel::HandleEvents \n";
			_rcb( _fd );
		}
	}
}

void Channel::SetReadCB( std::function<void(int)> rcb )
{
	_rcb = std::move( rcb );
}
