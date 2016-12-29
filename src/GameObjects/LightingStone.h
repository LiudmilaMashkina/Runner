#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>

#pragma warning(pop)

#include "IGameObject.h"
#include "Utils/MacroCreate.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class LightingStone : public IGameObject
{
public:
    CREATE_FUNC_4(LightingStone, b2Body*, body, cocos2d::Node*, node, cocos2d::Node*, lighting, GameWorld*, world);
    
	virtual ~LightingStone();

	virtual void update(float delta) override;
	
	virtual b2Body* getBody() override { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::LightingStone; }
    
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
    virtual void drop() override;
    virtual bool isDroppable() override { return true; }
    
private:
    LightingStone(b2Body* body, cocos2d::Node* node, cocos2d::Node* lighting, GameWorld* world);
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
    bool _isTouched = false;
    cocos2d::Node* _lighting = nullptr;
	GameWorld* _world = nullptr;
    float _timer = -150;
};

 
