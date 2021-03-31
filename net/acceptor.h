
#include <memory>

class Channel;
class EventLoop;
class Acceptor
{
public:
	Acceptor( EventLoop* loop, int fd );
	void NewConnection(int fd);
	void Start();
	void HandleRead( int fd );
private:
	std::unique_ptr<Channel> _chan;
	EventLoop* _loop;
};
