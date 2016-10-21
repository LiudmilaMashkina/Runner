#ifndef __Wanderer__IGame__
#define __Wanderer__IGame__

class IGame
{
public:
	virtual void setPaused(bool doUpdate) = 0;
	virtual bool getPaused() = 0;
};

#endif /* defined(__Wanderer__IGame__) */
