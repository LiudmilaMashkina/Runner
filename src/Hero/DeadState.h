//
//  DeadState.hpp
//  Wanderer
//
//  Created by Luda on 31/12/15.
//
//

#ifndef DeadState_hpp
#define DeadState_hpp

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

class DeadState : public IHeroState
{
public:
    DeadState(GameWorld* world,
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

#endif /* DeadState_hpp */
