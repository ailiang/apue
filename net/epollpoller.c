
#include "epollpoller.h"
#include "channel.h"

EpollPoller::EpollPoller() : _events(20)
{
	_epoll_fd = epoll_create1( 0 );
}

void EpollPoller::Poll( int timeout, std::vector<Channel*>& activeChannels )
{
	int num = epoll_wait(_epoll_fd, &*_events.begin(), _events.size(), timeout );
	if( num > 0 )
	{
		FillActiveChannels( num, &activeChannels );
	}
}

void EpollPoller::UpdateEvent( Channel* chan )
{
	if( chan->Idx() == -1 )
	{
		chan->SetIdx(1);
		_channels[chan->FD()] = chan;
		struct epoll_event ev;
		ev.events = chan->Events();
		ev.data.ptr = chan;
		epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, chan->FD(), &ev);
	}
	else
	{
		struct epoll_event ev;
		ev.events = chan->Events();
		ev.data.ptr = chan;
		epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, chan->FD(), &ev);
	}
}

void EpollPoller::FillActiveChannels(int num, std::vector<Channel*>* channels  )
{
	for( int i = 0; i < num; ++i )
	{
		Channel* ch = static_cast<Channel*>( _events[i].data.ptr );
		auto it = _channels.find( ch->FD() );
		if( it == _channels.end() )
		{
			exit(-1);
		}
		ch->SetREvents( _events[i].events );
		channels->push_back( ch );
	}
}
