#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"
#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class Bulb : public IGameObject
{
public:
    CREATE_FUNC_3(Bulb, b2Body*, body, GameWorld*, world, cocos2d::Node*, node);
    
    virtual ~Bulb();

	virtual void update(float delta) override;
	
	virtual b2Body* getBody() override { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::Bulb; }
    
    //virtual void lightDimmer(bool switchOn, float opacityStep) override;
    void lightOn(bool switchedOn);
    
    virtual void drop() override;
    virtual bool isDroppable() override { return true; }
    
private:
    Bulb(b2Body* body,
         GameWorld* world,
         cocos2d::Node* node);
    
    b2Body* _body = nullptr;
    GameWorld* _world = nullptr;
    cocos2d::Node* _node = nullptr;
    float _targetOpacity = 0.0f;
};

 
