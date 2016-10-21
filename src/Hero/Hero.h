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
    /*
    virtual b2Vec2 getBodySize() override {return b2Vec2();};
    virtual void setRotationRad(float32 radAng) override {};
    virtual void setRotationDeg(float32 degAng) override {};
    virtual bool acceptTouch(b2Vec2 touchPos) override {return false;};
    virtual void onTouchBegan(b2Vec2 touchPos) override {};
    virtual void onTouchMoved(b2Vec2 touchPos) override {};
    virtual void onTouchEnded(b2Vec2 touchPos) override {};
    virtual bool canBeDeleted() override {return false;};
    */
    
    CREATE_FUNC_3(Hero, IGameLavelInfo*, info, cocos2d::Node*, layer, GameWorld*, world);
    
private:
    Hero(IGameLavelInfo* info,
         cocos2d::Node* layer,
         GameWorld* world);

    IGameLavelInfo* _info;
    GameWorld* _world;
    HeroData _data;
    std::map<HeroStateId, std::shared_ptr<IHeroState>> _states;
    std::shared_ptr<IHeroState> _currentState;
    
    // world pointer
    // states + current state
    //
};


#endif /* defined(__Wanderer__Hero__) */
