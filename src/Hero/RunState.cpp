//
//  RunState.cpp
//  Wanderer
//
//  Created by Luda on 28/12/15.
//
//

#include "RunState.h"
#include "AnimationEngine/AnimationFactory.h"
#include "Utils/b2Utils.h"
#include "Utils/Convert.h"
#include "GameWorld.h"
#include "AnimationEngine/AnimationEngine.h"

RunState::RunState(GameWorld* world,
                   HeroData* data) :
_world(world),
_data(data)
{}

void RunState::onEnter()
{
    _data->velocity.x = 3;
    _data->velocity.y = 0;
    
    _data->animationEngine->goToAnimationGroup("run");
    _data->canAttack = true;
}

HeroStateId RunState::update(float delta)
{
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    
    float hitDistance = b2Utils::raycast(_world->getPhysics(),
                                             b2Vec2(pos.x, pos.y + 0.5),
                                             b2Vec2(0, -1));
    
    if (hitDistance < 1.2)
    {
        pos.x += _data->velocity.x * delta;
        pos.y += 1 - hitDistance;
        _data->velocity.y = 0;
        _data->node->setPosition(Convert::toPixels(pos));
    }
    if (hitDistance >= 1.2)
    {
        return HeroStateId::Fall;
    }

    return getStateId();
}

HeroStateId RunState::onTap()
{
    return HeroStateId::Jump;
}

void RunState::onExit()
{
    
}

HeroStateId RunState::getStateId() const
{
    return HeroStateId::Run;
}








