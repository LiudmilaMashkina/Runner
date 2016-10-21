//
//  HeroData.h
//  Wanderer
//
//  Created by Luda on 28/12/15.
//
//

#ifndef HeroData_h
#define HeroData_h
#include "Utils/Forwards.h"

FORWARD_DECLARE_SHARED(AnimationEngine)

namespace cocos2d
{
    class Node;
}

/* HeroData is a common part for both Hero and hero states
 */
struct HeroData
{
    b2Vec2 acceleration;
    b2Vec2 velocity;
    cocos2d::Node* node = nullptr;
    AnimationEnginePtr animationEngine;
    bool canAttack = true;
};


#endif /* HeroData_h */
