#pragma once

#pragma warning(push, 0)
#include <Box2D/Box2D.h>
#include <2d/CCNode.h>
#pragma warning(pop)

class IGameObject;

class GameWorld
{
public:
	GameWorld(const b2Vec2& gravity);
	~GameWorld();

	void addObject(std::shared_ptr<IGameObject> object);

	b2World* getPhysics() { return _physics; }
	cocos2d::Layer* getGraphics() { return _graphics; }

	void update(float delta);

private:
	b2World* _physics = nullptr;
	cocos2d::Layer* _graphics = nullptr;
	std::vector<std::shared_ptr<IGameObject>> _objects;
	
};