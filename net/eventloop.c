
#include "eventloop.h"
#include "pollpoller.h"
#include "epollpoller.h"
#include "channel.h"

EventLoop::EventLoop(): _poll( new EpollPoller() )
{
}

void EventLoop::UpdateEvents( Channel* chan )
{
	_poll->UpdateEvent( chan );
}

void EventLoop::Loop()
{
	while( 1 )
	{
		_activeChannels.clear();
		_poll->Poll( -1, _activeChannels );
		for( auto& ch : _activeChannels )
		{
			ch->HandleEvents();
		}
	}
}
