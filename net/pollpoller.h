
#include "poller.h"
#include <vector>
#include <poll.h>

class PollPoller: public Poller
{
public:
	virtual void Poll( int timeout, std::vector<Channel*>& activeChanles );
	virtual void UpdateEvent( Channel* chan );
private:
	void FillActiveChannels(int num, std::vector<Channel*>* channels  );
	std::vector<struct pollfd> _pollfds;
};
