
#ifndef __POLLER_H__
#define __POLLER_H__
#include <map>
#include <vector>
class Channel;

class Poller
{
public:
	virtual void Poll( int timeout, std::vector<Channel*>& activeChanles ) = 0; 
	virtual void UpdateEvent( Channel* chan ) = 0;
	virtual ~Poller(){};
protected:
	std::map<int, Channel*>  _channels;
};
#endif
