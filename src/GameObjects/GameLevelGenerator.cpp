//
//  GameLevelGenerator.cpp
//  GameLib
//
//  Created by Luda on 27/09/16.
//
//

#include <cassert>
#include "GameLevelGenerator.h"
#include "Utils/Environment.h"

GameLevelGenerator::GameLevelGenerator(GameWorld* world) :
_world(world)
{
    _exitPos.x = 0.2f * Environment::getScreenSize().x;
    _exitPos.y = 0.5f * Environment::getScreenSize().y;
}

float GameLevelGenerator::getCurrentBottom(float valueX)
{
    return -5.0f;
}

void GameLevelGenerator::generateUntil(const float frontier)
{
    while (_exitPos.x <= frontier)
    {
        int start = static_cast<int>(CompositionId::EnumStart) + 1;
        int end = static_cast<int>(CompositionId::EnumEnd) - 1;
        CompositionId random = static_cast<CompositionId>(Environment::generateIntRand(start, end));
        
        _exitPos = generateComposition(random, _exitPos);
        _exitPos.x += 3;
    }
}

b2Vec2 GameLevelGenerator::generateComposition(CompositionId compositionId, const b2Vec2& startPos)
{
    switch (compositionId)
    {
        case CompositionId::Bridge :
            return generateBridge(startPos);
        //case CompositionId::IceLine :
          //  generateIceLine(startPos);
            //break;
        case CompositionId::BlueStoneLine :
            return generateBlueStoneLine(startPos);
        /*
        case CompositionId::BrownStoneLine :
            generateBrownStoneLine(startPos);
            break;
        case CompositionId::MIxedStoneLine :
            generateMixedStoneLine(startPos);
            break;
        */    
        default:
            assert(false);
    }
    
    return {0.0f, 0.0f};
}

b2Vec2 GameLevelGenerator::generateBridge(const b2Vec2& startPos)
{
    GameObjectComposer::BridgeDef bridge;
    //bridge.startPos.Set(winSize.x / 5, winSize.y * 0.75f);
    bridge.startPos.Set(startPos.x, startPos.y);
    bridge.direction.Set(1.0f, 0);
    bridge.linkCount = 5;
    bridge.linkSize.Set(0.6f, 0.6f);
    bridge.overlap = 0.14f;
    
    GameObjectComposer composer = GameObjectComposer(_world);
    return composer.assembleBridge(bridge);
}

b2Vec2 GameLevelGenerator::generateIceLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}

b2Vec2 GameLevelGenerator::generateBlueStoneLine(const b2Vec2 &startPos)
{
    GameObjectComposer::LineDef line;
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_0.png", 0.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_1.png", 0.75f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_2.png", 1.0f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_3.png", 2.0f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_4.png", 1.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_5.png", 0.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/stone_line_blue_6.png", 0.5f));
    line.length = 3;
    line.maxOverlap = 0;
    line.startPos.Set(startPos.x, startPos.y);
    
    GameObjectComposer composer = GameObjectComposer(_world);
    return composer.assembleLine(line);
}

b2Vec2 GameLevelGenerator::generateBrownStoneLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}

b2Vec2 GameLevelGenerator::generateMixedStoneLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}
