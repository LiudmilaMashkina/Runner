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
#include "ObjectThemer.h"

GameLevelGenerator::GameLevelGenerator(GameWorld* world) :
_world(world)
{
    _exitPos.x = 0.2f * Environment::getScreenSize().x;
    _exitPos.y = 0.5f * Environment::getScreenSize().y;
    
    _themer = new ObjectThemer();
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
    ObjectThemer::ThemeId theme = _themer->getTheme();
    
    switch (compositionId)
    {
        case CompositionId::Bridge :
            return generateBridge(startPos, theme);
        case CompositionId::Line :
            return generateLine(startPos, theme);
        //case CompositionId::LightingLine :
            //return generateLightingLine(startPos);
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

b2Vec2 GameLevelGenerator::generateBridge(const b2Vec2& startPos, ObjectThemer::ThemeId theme)
{
    GameObjectComposer::BridgeDef bridge;
    bridge.startPos.Set(startPos.x, startPos.y);
    float dirY = Environment::generateFloatRand(-1.0f, 1.0f);
    bridge.direction.Set(1.0f, dirY);
    bridge.linkCount = Environment::generateIntRand(7, 14);
    bridge.linkSize.Set(0.6f, 0.6f);
    bridge.overlap = 0.14f;
    
    GameObjectComposer composer = GameObjectComposer(_world);
    return composer.assembleBridge(bridge, theme);
}

b2Vec2 GameLevelGenerator::generateIceLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}

b2Vec2 GameLevelGenerator::generateLine(const b2Vec2 &startPos, ObjectThemer::ThemeId theme)
{
    std::string themePrefix = "stone";
    std::string fileName = "resources/" + themePrefix + "_line_blue_";
    
    GameObjectComposer::LineDef line;
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "0.png", "", 0.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "1.png", "", 0.75f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "2.png", "", 1.0f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "3.png", "", 2.0f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "4.png", "", 1.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "5.png", "", 0.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block(fileName + "6.png", "", 0.5f));
    line.length = 10;
    line.maxOverlap = 0;
    line.startPos.Set(startPos.x, startPos.y);
    
    GameObjectComposer composer = GameObjectComposer(_world);
    return composer.assembleLine(line);
}

b2Vec2 GameLevelGenerator::generateLightingLine(const b2Vec2 &startPos)
{
    GameObjectComposer::LineDef line;
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/lighting_stone_0.png", "resources/lighting_stone_light_0.png", 0.5f));
    line.blocks.push_back(GameObjectComposer::LineDef::Block("resources/lighting_stone_1.png", "resources/lighting_stone_light_1.png", 0.75f));
    
    int len = Environment::generateIntRand(6, 15);
    line.length = len;
    line.maxOverlap = 0;
    line.startPos.Set(startPos.x, startPos.y);
    
    GameObjectComposer composer = GameObjectComposer(_world);
    return composer.assembleLightingLine(line);
}

b2Vec2 GameLevelGenerator::generateBrownStoneLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}

b2Vec2 GameLevelGenerator::generateMixedStoneLine(const b2Vec2 &startPos)
{
    return {0.0f, 0.0f};
}
