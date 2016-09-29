//
//  GameLevelGenerator.hpp
//  GameLib
//
//  Created by Luda on 27/09/16.
//
//

#ifndef GameLevelGenerator_hpp
#define GameLevelGenerator_hpp

#include <stdio.h>
#include "GameObjectComposer.h"
#include "GameWorld.h"

enum class CompositionId
{
    EnumStart = 0,
    Bridge,
    //IceLine,
    BlueStoneLine,
    //BrownStoneLine,
    //MIxedStoneLine,
    EnumEnd
};


class GameLevelGenerator
{
public:
    GameLevelGenerator(GameWorld* world);
    void generateUntil(const float frontier);
    b2Vec2 generateComposition(CompositionId compositionId, const b2Vec2& startPos);
    b2Vec2 generateBridge(const b2Vec2& startPos);
    b2Vec2 generateIceLine(const b2Vec2& startPos);
    b2Vec2 generateBlueStoneLine(const b2Vec2& startPos);
    b2Vec2 generateBrownStoneLine(const b2Vec2& startPos);
    b2Vec2 generateMixedStoneLine(const b2Vec2& startPos);
    
    
private:
    GameWorld* _world;
    b2Vec2 _exitPos = {0.0f, 0.0f};
};

#endif /* GameLevelGenerator_hpp */
