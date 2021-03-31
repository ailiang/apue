
#include <memory>
#include <vector>

class Channel;
class Poller;
class EventLoop
{
public:
	EventLoop();
	void Loop();
	void UpdateEvents( Channel* chan );
private:
	Poller* _poll;
	std::vector<Channel*> _activeChannels;
};
