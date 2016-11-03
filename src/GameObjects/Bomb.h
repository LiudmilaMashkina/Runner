#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>
#pragma warning(pop)

#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class Bomb : public IGameObject
{
public:
	//Bomb(b2Body* body, cocos2d::Node* node, GameWorld* world);
    Bomb(b2Body* body, GameWorld* world);
    virtual ~Bomb();

	virtual void update(float delta) override;
	
	b2Body* getBody() { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::Bomb; }

private:
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
	GameWorld* _world = nullptr;
};

 
