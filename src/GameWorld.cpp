#pragma warning(push, 0)

#pragma warning(pop)
#include <cassert>
#include "GameWorld.h"
#include "GameObjects/IGameObject.h"
#include "ContactListener.h"
#include "Utils/TimeProvider.h"

USING_NS_CC;

GameWorld::GameWorld(const b2Vec2& gravity, Node* rootNode, const std::shared_ptr<TimeProvider>& timeProvider) :
_contactListener(this)
{
	_physics.reset(new b2World(gravity));
	_graphics = rootNode;
    _timeProvider = timeProvider;
    
    _physics->SetContactListener(&_contactListener);
}

GameWorld::~GameWorld()
{}

void GameWorld::addObject(const std::shared_ptr<IGameObject>& object)
{
    assert(object);
	assert(find(_objects.begin(), _objects.end(), object) == _objects.end());
    _objectsMap[object.get()] = object;
	_objects.push_back(object);
}

void GameWorld::removeObject(const std::function<bool (const std::shared_ptr<IGameObject> &)> &predicate)
{
    
    auto startIt = std::partition(_objects.begin(), _objects.end(),
                                  [&](const std::shared_ptr<IGameObject>& obj)
                                  {
                                      return !predicate(obj);
                                  });
    for (auto it = startIt; it != _objects.end(); ++it)
        _objectsMap.erase(it->get());
    _objects.erase(startIt, _objects.end());
    
}

void GameWorld::removeObjectLater(IGameObject* objToDelete)
{
    auto it = _objectsMap.find(objToDelete);
    
    assert(_objectsMap.find(objToDelete) != _objectsMap.end());
    assert(std::find(_objectsToRemove.begin(), _objectsToRemove.end(), it->second) == _objectsToRemove.end());
    
    _objectsToRemove.push_back(it->second);
}

void GameWorld::addContact(IGameObject *a, IGameObject *b)
{
    std::pair<IGameObject*, IGameObject*> contact(a, b);
    _contacts.push_back(contact);
}

void GameWorld::forEach(const std::function<void(std::shared_ptr<IGameObject>)> &func)
{
    for (auto& object : _objects)
        func(object);
}

void GameWorld::update(float delta)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	_physics->Step(delta, velocityIterations, positionIterations);
    
    for (int i = 0; i < _contacts.size(); ++i)
    {
        auto itA = _objectsMap.find(_contacts[i].first);
        auto itB = _objectsMap.find(_contacts[i].second);
        
        assert(itA != _objectsMap.end());
        assert(itB != _objectsMap.end());
        
        itA->second->onContactBegin(itB->second);
        itB->second->onContactBegin(itA->second);
    }
    
    _contacts.clear();

	for (size_t i = 0; i < _objects.size(); ++i)
	{
		_objects[i]->update(delta);
	}
    
    for (auto& obj : _objectsToRemove)
    {
        auto it = std::find(_objects.begin(), _objects.end(), obj);
        assert(it != _objects.end());
        assert(it->use_count() == 3);
        _objects.erase(it);
        _objectsMap.erase(obj.get());
    }
    _objectsToRemove.clear();
}

