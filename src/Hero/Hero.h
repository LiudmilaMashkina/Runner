//
//  Hero.h
//  Wanderer
//
//  Created by Luda on 06/11/15.
//
//

#ifndef __Wanderer__Hero__
#define __Wanderer__Hero__

#include <map>
#include "GameObjects/IGameObject.h"
#include "GameObjects/GameObjectType.h"
#include "Utils/Forwards.h"
#include "HeroStateId.h"
#include "HeroData.h"
#include "IHeroState.h"
#include "Utils/MacroCreate.h"

class GameWorld;
class IGameLavelInfo;

class Hero : public IGameObject
{
public:
    virtual ~Hero();
    
    virtual void update(float delta) override;
    
    void onTap();
    
    virtual void setPosition(const b2Vec2 &position);
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::Hero; }
    virtual b2Body* getBody() override { return _data.body; }
    
    int getLifes();
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
    CREATE_FUNC_3(Hero, IGameLavelInfo*, info, cocos2d::Node*, layer, GameWorld*, world);
    
    std::shared_ptr<IHeroState> getState() { return _currentState; }
    
private:
    Hero(IGameLavelInfo* info,
         cocos2d::Node* layer,
         GameWorld* world);

    void decreaseLifes(int num);
    
    IGameLavelInfo* _info;
    GameWorld* _world;
    HeroData _data;
    std::map<HeroStateId, std::shared_ptr<IHeroState>> _states;
    std::shared_ptr<IHeroState> _currentState;
    int _lifes = 100;
    
    // world pointer
    // states + current state
    //
};


#endif /* defined(__Wanderer__Hero__) */
