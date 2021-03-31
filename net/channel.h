
#include <functional>
class EventLoop;
class Channel
{
public:
	Channel( EventLoop* loop, int fd );
	void EnableRead();
	void DisableRead();
	void EnableWrite();
	void DisableWrite();

	int FD(); 
	void SetREvents( int ev );
	int Events();
	int Idx();
	void SetIdx( int i );

	void HandleEvents();

	void SetReadCB( std::function<void(int)> rcb );

private:
	int _fd = -1;
	int _events = 0;
	int _revents = 0;
	int _idx = -1;
	EventLoop* _loop;

	const static int NoneEvent;
	const static int ReadEvent;
	const static int WriteEvent;

	void UpdateEvents();

	std::function<void(int)> _rcb;
};
