//
//  FallState.hpp
//  Wanderer
//
//  Created by Luda on 29/12/15.
//
//

#ifndef FallState_hpp
#define FallState_hpp

#include <stdio.h>
#include "Box2D/Common/b2Math.h"
#include "IHeroState.h"
#include "HeroData.h"

FORWARD_DECLARE_SHARED(AnimationEngine)

namespace cocos2d
{
    class Node;
}

class GameWorld;
class Hero;

class FallState : public IHeroState
{
public:
    FallState(GameWorld* world,
                HeroData* data);
        
    virtual void onEnter() override;
    virtual HeroStateId update(float delta) override;
    virtual HeroStateId onTapBegan() override;
    virtual HeroStateId onTapEnded() override;
    virtual void onExit() override;
    virtual HeroStateId getStateId() const override;
        
private:
	GameWorld* _world = nullptr;
    HeroData* _data = nullptr;
};

#endif /* FallState_hpp */
