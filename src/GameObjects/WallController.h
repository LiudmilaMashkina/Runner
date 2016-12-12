#pragma once

#pragma warning(push, 0)
#pragma warning(pop)

#include "IGameObject.h"
#include "Utils/MacroCreate.h"

class WallStone;
class GameWorld;

class WallController : public IGameObject
{
public:
    CREATE_FUNC_2(WallController, GameWorld*, wold, const b2Vec2&, position);
    
    virtual ~WallController();
    
    virtual void update(float delta) override;
    virtual b2Body* getBody() override { return nullptr; }
    virtual b2Vec2 getPosition() override { return _position; };
    virtual GameObjectType getType() const override { return GameObjectType::WallController; }
    
    //virtual void drop() override; //???
    //virtual bool isDroppable() override { return true; }
    
    void addStone(std::weak_ptr<WallStone> wStone);
    
    void destroyWall(const b2Vec2& hitPos, float maxHitImpulse);
    
private:
    WallController(GameWorld* wold, const b2Vec2& position);
    
    GameWorld* _world = nullptr;
    b2Vec2 _position = {0, 0};
    //std::unordered_map<b2Body*, std::weak_ptr<WallStone>> _stonesMap;
    std::vector<std::weak_ptr<WallStone>> _wStones;
    bool _isDestroyed = false;
};

 
