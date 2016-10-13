
#ifndef __Wanderer__ITimeProvider__
#define __Wanderer__ITimeProvider__


class ITimeProvider
{
public:
	virtual float getTime() = 0;
	virtual ~ITimeProvider() {}
};

#endif /* defined(__Wanderer__ITimeProvider__) */
