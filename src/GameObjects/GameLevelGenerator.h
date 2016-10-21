#pragma once

#include <stdio.h>
#include "GameObjectComposer.h"
#include "GameWorld.h"
#include "Utils/MacroCreate.h"
#include "IGameLavelInfo.h"

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


class GameLevelGenerator : public IGameLavelInfo
{
public:
    CREATE_FUNC_1(GameLevelGenerator, GameWorld*, world);
    
    virtual float getCurrentBottom(float valueX) override;
    
    void generateUntil(const float frontier);
    b2Vec2 generateComposition(CompositionId compositionId, const b2Vec2& startPos);
    b2Vec2 generateBridge(const b2Vec2& startPos);
    b2Vec2 generateIceLine(const b2Vec2& startPos);
    b2Vec2 generateBlueStoneLine(const b2Vec2& startPos);
    b2Vec2 generateBrownStoneLine(const b2Vec2& startPos);
    b2Vec2 generateMixedStoneLine(const b2Vec2& startPos);
    
    
private:
    GameLevelGenerator(GameWorld* world);

    GameWorld* _world;
    b2Vec2 _exitPos = {0.0f, 0.0f};
};
