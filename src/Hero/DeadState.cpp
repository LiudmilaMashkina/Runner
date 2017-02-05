//
//  DeadState.cpp
//  Wanderer
//
//  Created by Luda on 31/12/15.
//
//

#include "Hero/DeadState.h"
#include "AnimationEngine/AnimationFactory.h"
#include "Utils/Convert.h"
#include "GameWorld.h"
#include "AnimationEngine/AnimationEngine.h"
#include "Utils/b2Vec2Operators.h"

DeadState::DeadState(GameWorld* world,
                     HeroData* data) :
_world(world),
_data(data)
{
    (void)_world; //no unused warning
}

void DeadState::onEnter()
{
    _data->animationEngine->goToAnimationGroup("dead");
}

HeroStateId DeadState::update(float delta)
{
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    
    pos.y += _data->velocity.y * delta + _data->acceleration.y * delta * delta / 2;
    _data->velocity += _data->acceleration * delta;
    _data->node->setPosition(Convert::toPixels(pos));
        
    return getStateId();
}

HeroStateId DeadState::onTapBegan()
{
    return getStateId();
}

HeroStateId DeadState::onTapEnded()
{
    return getStateId();
}

void DeadState::onExit()
{
    
}

HeroStateId DeadState::getStateId() const
{
    return HeroStateId::Dead;
}
