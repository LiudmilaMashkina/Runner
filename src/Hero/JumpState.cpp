//
//  JumpState.cpp
//  Wanderer
//
//  Created by Luda on 29/12/15.
//
//

#include "Hero/JumpState.h"
#include "AnimationEngine/AnimationFactory.h"
#include "Utils/b2Utils.h"
#include "Utils/Convert.h"
#include "GameWorld.h"
#include "AnimationEngine/AnimationEngine.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Cfg.h"

JumpState::JumpState(GameWorld* world,
                     HeroData* data) :
_world(world),
_data(data)
{}

void JumpState::onEnter()
{
    _jumpIncreaseTimeLeft = 0.5f;
    
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    float hitDistance =  b2Utils::raycast(_world->getPhysics(), b2Vec2(pos.x, pos.y + 0.5),
                                              b2Vec2(0, -1), _data->collisionFilter);
    
    if (hitDistance < 1.1 && _data->velocity.y <= 0)
    {
        _data->velocity.y += Cfg::Hero::JumpVelocityY;
        _data->animationEngine->goToAnimationGroup("jump");
    }
}

HeroStateId JumpState::update(float delta)
{
    float velocityTimeDelta = delta;
    if (_jumpIncreaseTimeLeft < delta)
        velocityTimeDelta = std::max(0.0f, _jumpIncreaseTimeLeft - delta);
    
    _data->velocity.y += velocityTimeDelta * Cfg::Hero::JumpVelocityY;
    _jumpIncreaseTimeLeft -= delta;
    
    
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    
    float32 hitDistance = b2Utils::raycast(_world->getPhysics(),
                                             b2Vec2(pos.x, pos.y + 0.5),
                                             b2Vec2(0, -1), _data->collisionFilter);
    
    if (hitDistance > 1 || _data->velocity.y > 0)
    {
        pos.x += _data->velocity.x * delta;
        pos.y += _data->velocity.y * delta + _data->acceleration.y * delta * delta / 2;
        _data->velocity += _data->acceleration * delta;
        _data->node->setPosition(Convert::toPixels(pos));
        
        return getStateId();
    }
    if (hitDistance <= 1 && _data->velocity.y <= 0)
        return HeroStateId::Run;
    else
        return HeroStateId::Fall;
}

HeroStateId JumpState::onTapBegan()
{
    if (_data->canAttack)
        return HeroStateId::Attack;
    else
        return getStateId();
}

HeroStateId JumpState::onTapEnded()
{
    _jumpIncreaseTimeLeft = 0;
    return getStateId();
}

void JumpState::onExit()
{
    
}

HeroStateId JumpState::getStateId() const
{
    return HeroStateId::Jump;
}

