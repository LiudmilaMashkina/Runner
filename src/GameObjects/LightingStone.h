#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>

#pragma warning(pop)

#include "SimpleGameObject.h"
#include "Utils/MacroCreate.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class LightingStone : public SimpleGameObject
{
public:
    CREATE_FUNC_4(LightingStone, b2Body*, body, cocos2d::Node*, node, cocos2d::Node*, lighting, GameWorld*, world);
    
	virtual ~LightingStone();

	virtual void update(float delta) override;
	
	virtual GameObjectType getType() const override { return GameObjectType::LightingStone; }
    
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
private:
    LightingStone(b2Body* body, cocos2d::Node* node, cocos2d::Node* lighting, GameWorld* world);
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
    bool _isTouched = false;
    cocos2d::Node* _lighting = nullptr;
    float _timer = -150;
};

 
