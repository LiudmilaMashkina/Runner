//
//  IHeroState.hpp
//  Wanderer
//
//  Created by Luda on 28/12/15.
//
//

#ifndef IHeroState_hpp
#define IHeroState_hpp

#include <memory>
#include "HeroStateId.h"

class IHeroState
{
public:
    virtual ~IHeroState() {}
    
    virtual void onEnter() = 0;
    virtual HeroStateId update(float delta) = 0;
    virtual HeroStateId onTapBegan() = 0;
    virtual HeroStateId onTapEnded() = 0;
    virtual void onExit() = 0;
    virtual HeroStateId getStateId() const = 0;
};

#endif /* IHeroState_hpp */
