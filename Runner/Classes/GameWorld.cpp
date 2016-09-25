#pragma warning(push, 0)

#pragma warning(pop)
#include <cassert>
#include "GameWorld.h"
#include "GameObjects/IGameObject.h"

USING_NS_CC;

GameWorld::GameWorld(const b2Vec2& gravity, Node* rootNode)
{
	_physics = new b2World(gravity);
	_graphics = rootNode;
}

GameWorld::~GameWorld()
{}

void GameWorld::addObject(const std::shared_ptr<IGameObject>& object)
{
	assert(find(_objects.begin(), _objects.end(), object) == _objects.end());
	_objects.push_back(object);
}

void GameWorld::update(float delta)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	_physics->Step(delta, velocityIterations, positionIterations);

	for (size_t i = 0; i < _objects.size(); ++i)
	{
		_objects[i]->update(delta);
	}
}

