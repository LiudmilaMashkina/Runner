//
//  AttackState.hpp
//  Wanderer
//
//  Created by Luda on 29/12/15.
//
//

#ifndef AttackState_hpp
#define AttackState_hpp

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

class AttackState : public IHeroState
{
public:
    AttackState(GameWorld* world,
              HeroData* data);
    
    virtual void onEnter() override;
    virtual HeroStateId update(float delta) override;
    virtual HeroStateId onTap() override;
    virtual void onExit() override;
    virtual HeroStateId getStateId() const override;
    
private:
	GameWorld* _world = nullptr;
    HeroData* _data = nullptr;
    b2Vec2 _backupVelocity;
    float _attackTime = 0;
};


#endif /* AttackState_hpp */
