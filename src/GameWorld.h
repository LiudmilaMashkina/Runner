#pragma once

#include <functional>
#pragma warning(push, 0)
#include <Box2D/Box2D.h>
#include <2d/CCNode.h>
#pragma warning(pop)

#include "IUpdatable.h"
#include "ContactListener.h"

class IGameObject;
class TimeProvider;

class GameWorld : public IUpdatable
{
public:
    GameWorld(const b2Vec2& gravity, cocos2d::Node* rootNode, const std::shared_ptr<TimeProvider>& timeProvider);
	~GameWorld();

	void addObject(const std::shared_ptr<IGameObject>& object);

	std::shared_ptr<b2World> getPhysics() { return _physics; }
	cocos2d::Node* getGraphics() { return _graphics; }
    void removeObject(const std::function<bool (const std::shared_ptr<IGameObject>&)> &predicate);
    void removeObjectLater(IGameObject* objToDelete);
    void addContact(IGameObject* a, IGameObject* b);
    
	virtual void update(float delta) override;

    std::shared_ptr<TimeProvider> getTimeProvider() { return _timeProvider; }
    
private:
    std::shared_ptr<b2World> _physics = nullptr;
	cocos2d::Node* _graphics = nullptr;
	std::vector<std::shared_ptr<IGameObject>> _objects;
    std::vector<std::pair<IGameObject*, IGameObject*>> _contacts;
    std::unordered_map<IGameObject*, std::shared_ptr<IGameObject>> _objectsMap;
    std::vector<std::shared_ptr<IGameObject>> _objectsToRemove;
    ContactListener _contactListener;
    std::shared_ptr<TimeProvider> _timeProvider;

};
