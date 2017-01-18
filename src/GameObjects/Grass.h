#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"
#include "SimpleGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;
class ParticlesObject;

class Grass : public SimpleGameObject
{
public:
    CREATE_FUNC_4(Grass, b2Body*, body, GameWorld*, world, cocos2d::Node*, node, const std::weak_ptr<ParticlesObject>&, particles);
    
    virtual ~Grass();

	virtual void update(float delta) override;
	
	virtual GameObjectType getType() const override { return GameObjectType::Grass; }
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
private:
    Grass(b2Body* body,
         GameWorld* world,
          cocos2d::Node* node,
          const std::weak_ptr<ParticlesObject>& particles);
    
    std::weak_ptr<ParticlesObject> _particles;
};

 
