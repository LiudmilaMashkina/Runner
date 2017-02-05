//
//  AttackState.cpp
//  Wanderer
//
//  Created by Luda on 29/12/15.
//
//

#include "AttackState.h"
#include "AnimationEngine/AnimationFactory.h"
#include "Utils/b2Utils.h"
#include "Utils/Convert.h"
#include "GameWorld.h"
#include "AnimationEngine/AnimationEngine.h"
#include "Utils/b2Vec2Operators.h"

AttackState::AttackState(GameWorld* world,
                     HeroData* data) :
_world(world),
_data(data)
{}

void AttackState::onEnter()
{
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    float hitDistance = b2Utils::raycast(_world->getPhysics(),
                                              b2Vec2(pos.x, pos.y + 0.5),
                                              b2Vec2(0, -1), _data->collisionFilter);
    
    if (hitDistance > 1.1)
    {
        _attackTime = 1.0;
        _backupVelocity = _data->velocity;

        _data->velocity.y = 0;
        _data->velocity.x += 7;
        _data->animationEngine->goToAnimationGroup("attack");
    }
}

HeroStateId AttackState::update(float delta)
{
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    float32 hitDistance =  b2Utils::raycast(_world->getPhysics(),
                                              b2Vec2(pos.x, pos.y + 0.5),
                                              b2Vec2(0, -1), _data->collisionFilter);
    
    if (hitDistance > 1.1 && _attackTime > 0)
    {
        _attackTime -= delta;
        b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
        pos.x += _data->velocity.x * delta;
        _data->node->setPosition(Convert::toPixels(pos));
    }
    else
    {
        _data->velocity = _backupVelocity;
        
        return HeroStateId::Fall;
    }
    
    return getStateId();
}

HeroStateId AttackState::onTapBegan()
{
    return getStateId();
}

HeroStateId AttackState::onTapEnded()
{
    return getStateId();
}

void AttackState::onExit()
{
    _data->canAttack = false;
}

HeroStateId AttackState::getStateId() const
{
    return HeroStateId::Attack;
}
