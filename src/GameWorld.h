#pragma once

#include <functional>
#pragma warning(push, 0)
#include <Box2D/Box2D.h>
#include <2d/CCNode.h>
#pragma warning(pop)

class IGameObject;

class GameWorld
{
public:
	GameWorld(const b2Vec2& gravity, cocos2d::Node* rootNode);
	~GameWorld();

	void addObject(const std::shared_ptr<IGameObject>& object);

	b2World* getPhysics() { return _physics; }
	cocos2d::Node* getGraphics() { return _graphics; }
    void removeObject(const std::function<bool (const std::shared_ptr<IGameObject>&)> &predicate);

	void update(float delta);

private:
	b2World* _physics = nullptr;
	cocos2d::Node* _graphics = nullptr;
	std::vector<std::shared_ptr<IGameObject>> _objects;
};
