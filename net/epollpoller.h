
#include "poller.h"
#include <sys/epoll.h>
class EpollPoller : public Poller
{
public:
	EpollPoller(); 
	virtual void Poll( int timeout, std::vector<Channel*>& activeChanles ); 
	virtual void UpdateEvent( Channel* chan );
private:
	int _epoll_fd;
	std::vector<struct epoll_event> _events;
	void FillActiveChannels(int num, std::vector<Channel*>* channels  );

};
