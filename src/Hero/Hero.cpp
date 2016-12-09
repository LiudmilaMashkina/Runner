
#include "Hero.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "AnimationEngine/AnimationFactory.h"
#include "2d/CCSprite.h"
#include "AnimationEngine/AnimationEngine.h"
#include "RunState.h"
#include "FallState.h"
#include "JumpState.h"
#include "AttackState.h"
#include "DeadState.h"
#include "GameObjects/IGameLavelInfo.h"
#include "GameObjects/CollisionCategory.h"
#include "Utils/MacroCreate.h"

#include <iostream>

using namespace cocos2d;


Hero::Hero(IGameLavelInfo* info, cocos2d::Node *layer, GameWorld* world) :
_info(info),
_world(world)
{
    AnimationFactory factory;

    _data.acceleration.Set(0, -5);
    _data.velocity.Set(0, 0);
    
    _data.animationEngine = factory.getEngine("config/hero_animations.json");
    _data.node = _data.animationEngine->start();
    layer->addChild(_data.node);
    
    float height = _data.node->getContentSize().height;
    float scale = Convert::toPixels(1/height);
    _data.node->setScale(scale);
    
    b2Vec2 bodySize = Convert::toMeters(_data.node->getContentSize() * scale);
    b2PolygonShape physShape;
    physShape.SetAsBox(bodySize.x / 2, bodySize.y / 2);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position = b2Vec2(bodySize.x / 2, bodySize.y / 2);
    bodyDef.angle = 0;
    bodyDef.linearDamping = 5;
    bodyDef.angularDamping = 5;

    _data.body = _world->getPhysics()->CreateBody(&bodyDef);
    
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = &physShape;
    bodyFixtureDef.density = 1;
    bodyFixtureDef.isSensor = true;
    bodyFixtureDef.filter.categoryBits = CollisionCategory::HeroCategory;
    bodyFixtureDef.filter.maskBits = CollisionCategory::DefaultCategory;
    _data.body->CreateFixture(&bodyFixtureDef);
    
    IGameObject* ihero = this;
    _data.body->SetUserData(ihero);
    
    std::shared_ptr<RunState> runState(new RunState(world, &_data));
    _states[HeroStateId::Run] = runState;
    
    std::shared_ptr<FallState> fallState(new FallState(world, &_data));
    _states[HeroStateId::Fall] = fallState;
    
    std::shared_ptr<JumpState> jumpState(new JumpState(world, &_data));
    _states[HeroStateId::Jump] = jumpState;
    
    std::shared_ptr<AttackState> attackState(new AttackState(world, &_data));
    _states[HeroStateId::Attack] = attackState;
    
    std::shared_ptr<DeadState> deadState(new DeadState(world, &_data));
    _states[HeroStateId::Dead] = deadState;

    _currentState = runState;
    _currentState->onEnter();
    
    // remove unused warning
    (void)_world;
}

Hero::~Hero()
{

}

void Hero::update(float delta)
{
    _info->getCurrentBottom(getPosition().x); /// delete

    b2Vec2 bodyPos = Convert::toMeters(_data.node->getPosition());
    _data.body->SetTransform(bodyPos, 0);
    
    HeroStateId stateId = _currentState->update(delta);
    
    if (stateId != _currentState->getStateId())
    {
        _currentState->onExit();
        _currentState = _states[stateId];
        _currentState->onEnter();
    }
    
	auto currentButtom = _info->getCurrentBottom(getPosition().x);
    if (getPosition().y < currentButtom)
    {
        _currentState = _states[HeroStateId::Dead];
        _currentState->onEnter();
    }
    else
        _currentState = _states[stateId];
    
    _data.animationEngine->update(delta);

}

void Hero::onTap()
{
    HeroStateId stateId = _currentState->onTap();
    
    if (stateId != _currentState->getStateId())
    {
        _currentState = _states[stateId];
        _currentState->onEnter();
    }
}

void Hero::setPosition(const b2Vec2 &position)
{
    _data.node->setPosition(Convert::toPixels(position));
}

b2Vec2 Hero::getPosition()
{
    b2Vec2 position = Convert::toMeters(_data.node->getPosition());
    
    return position;
}

int Hero::getLifes()
{
    auto state = _currentState->getStateId();
    if (state == HeroStateId::Dead)
    {
        return 0;
    }
    return _lifes;
}

void Hero::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    GameObjectType type = obj->getType();
    if (type == GameObjectType::Bomb)
        decreaseLifes(0);
    else if (type == GameObjectType::WallStone)
    {
        auto stateID = _currentState->getStateId();
        if (stateID != HeroStateId::Attack)
            decreaseLifes(10);
    }
}

void Hero::decreaseLifes(int num)
{
    _lifes -= num;
    
    if (_lifes <= 0)
    {
        _currentState = _states[HeroStateId::Dead];
        _currentState->onEnter();
    }
}



