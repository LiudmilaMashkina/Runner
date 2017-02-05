//
//  RunState.hpp
//  Wanderer
//
//  Created by Luda on 28/12/15.
//
//

#ifndef RunState_hpp
#define RunState_hpp

#include <Box2D/Common/b2Math.h>
#include "IHeroState.h"
#include "HeroData.h"

FORWARD_DECLARE_SHARED(AnimationEngine)

class GameWorld;
class Hero;

namespace cocos2d
{
    class Node;
}

class RunState : public IHeroState
{
public:
    RunState(GameWorld* world,
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

#endif /* RunState_hpp */
