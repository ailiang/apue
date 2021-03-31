
#include "poller.h"
class EpollPoller : public Poller
{
public:
	virtual void Poll( int timeout, std::vector<Channel*>& activeChanles ); 
	virtual void UpdateEvent( Channel* chan );
private:
	int _epoll_fd;
	std::vector<struct epoll_event> _events;

};
