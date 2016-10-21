//
//  Forwards.h
//  Wanderer
//
//  Created by Luda on 05/12/15.
//
//

#ifndef Wanderer_Forwards_h
#define Wanderer_Forwards_h

#include <memory>
#define FORWARD_DECLARE_SHARED(className) \
class className; \
typedef std::shared_ptr<className> className##Ptr; \
typedef std::shared_ptr<const className> className##ConstPtr;


#endif
