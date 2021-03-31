
#include "pollpoller.h"
#include "channel.h"
#include <poll.h>

void PollPoller::Poll( int timeout, std::vector<Channel*>& activeChannels )
{
	int num = ::poll(&*_pollfds.begin(), _pollfds.size(), timeout );
	if( num > 0 )
	{
		FillActiveChannels( num, &activeChannels );
	}
}

void PollPoller::UpdateEvent( Channel* chan )
{
	if( chan->Idx() == -1 )
	{
		struct pollfd pfd;
		pfd.fd = chan->FD();
		pfd.events = chan->Events();
		pfd.revents = 0;
		_pollfds.push_back( pfd );
		chan->SetIdx( _pollfds.size() - 1 );
		_channels[chan->FD()] = chan;
	}
	else
	{
		auto& pfd = _pollfds[chan->Idx()];
		pfd.fd = chan->FD();
		pfd.events = chan->Events();
		pfd.revents = 0;
		if( chan->Events() == 0 )
		{
			pfd.fd = -chan->FD() - 1;
		}
	}
}

void PollPoller::FillActiveChannels(int num, std::vector<Channel*>* channels  )
{
	for( auto it = _pollfds.begin(); it != _pollfds.end() && num > 0; ++it )
	{
		if( it->revents > 0 )
		{
			--num;
			auto ch_it = _channels.find( it->fd );

			if( ch_it == _channels.end() )
			{
				exit( -1 );
			}
			auto chan = ch_it->second;
			if( chan->FD() != it->fd )
			{
				exit(-2);
			}
			chan->SetREvents( it->revents);
			channels->push_back( chan );
		}
	}
}

