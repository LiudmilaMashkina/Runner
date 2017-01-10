#pragma warning(push, 0)
#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>
#pragma warning(pop)
#include "GameObjectComposer.h"
#include "GameObjectFactory.h"
#include "SimpleGameObject.h"
#include "Bomb.h"
#include "Bulb.h"
#include "BridgeColumn.h"
#include "Grass.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"

USING_NS_CC;

GameObjectComposer::GameObjectComposer(GameWorld* world) :
_world(world)
{}

b2Vec2 GameObjectComposer::assembleLine(const LineDef& def)
{
	GameObjectFactory factory = GameObjectFactory(_world);
    
    float curLength = 0.0f;
	for ( ; curLength < def.length; )
	{
		int num = Environment::generateIntRand(0, def.blocks.size() - 1);
		const LineDef::Block& block = def.blocks[num];
		
		b2Vec2 leftCorner(def.startPos.x + curLength, def.startPos.y);
        
        float height = 0;
		auto stone = factory.createStaticStone(leftCorner, block.width, block.textureName, &height);
        
        int randNumber = Environment::generateIntRand(1, 30);
        b2Vec2 jointPos = leftCorner + b2Vec2(block.width / 2, 0);
        
        if (randNumber >= 1 && randNumber <= 3)
        {
            b2Vec2 bombPos = leftCorner;
            bombPos.x += block.width / 2;
            auto bomb = factory.createBomb(bombPos, 0, b2Vec2(0.5, 0.5));
            
            b2WeldJointDef jointDef;
            auto stoneBody = stone->getBody();
            (assert(stoneBody));
            jointDef.bodyA = stoneBody;
            
            jointDef.localAnchorA = stoneBody->GetLocalPoint(jointPos);
            auto bombBody = bomb->getBody();
            (assert(bombBody));
            jointDef.bodyB = bombBody;
            jointDef.localAnchorB = bombBody->GetLocalPoint(jointPos);
            
            _world->getPhysics()->CreateJoint(&jointDef);
            
        }
        else if (randNumber >= 4 && randNumber <= 10)
        {
            b2Vec2 grassSize = {block.width, 0.5};
            b2Vec2 grassPos = leftCorner;
            grassPos.x += block.width / 2;
            grassPos.y += grassSize.y / 2;
            auto grass = factory.createGrass(grassPos, 0, grassSize);
            
            b2WeldJointDef jointDef;
            auto stoneBody = stone->getBody();
            (assert(stoneBody));
            jointDef.bodyA = stoneBody;
            jointDef.localAnchorA = stoneBody->GetLocalPoint(jointPos);
            auto grassBody = grass->getBody();
            (assert(grassBody));
            jointDef.bodyB = grassBody;
            
            jointDef.localAnchorB = grassBody->GetLocalPoint(jointPos);
            _world->getPhysics()->CreateJoint(&jointDef);
        }
        else if (randNumber == 11)
        {
            b2Vec2 wallPos = leftCorner;
            auto wall = factory.createWall("wall_controller", wallPos, 3);
        }
        
        curLength += block.width;
	}
    
    b2Vec2 exitPos = def.startPos;
    exitPos.x += curLength;
    
    return exitPos;
}

b2Vec2 GameObjectComposer::assembleLightingLine(const LineDef& def)
{
    GameObjectFactory factory = GameObjectFactory(_world);
    
    float curLength = 0.0f;
    for ( ; curLength < def.length; )
    {
        int num = Environment::generateIntRand(0, def.blocks.size() - 1);
        const LineDef::Block& block = def.blocks[num];
        
        b2Vec2 leftCorner(def.startPos.x + curLength, def.startPos.y);
        
        auto stone = factory.createLightingStone(leftCorner, block.width, block.textureName, block.lightingName);
        b2Vec2 coinPos = leftCorner;
        coinPos.x += block.width / 2;
        coinPos.y += 0.5;
        auto coin = factory.createCoin(coinPos);
        
        int randNumber = Environment::generateIntRand(1, 20);
        b2Vec2 jointPos = leftCorner + b2Vec2(block.width / 2, 0);
        
        if (randNumber >= 1 && randNumber <= 4)
        {
            b2Vec2 bombPos = leftCorner;
            bombPos.x += block.width / 2;
            auto bomb = factory.createBomb(bombPos, 0, b2Vec2(0.5, 0.5));
            
            b2WeldJointDef jointDef;
            auto stoneBody = stone->getBody();
            (assert(stoneBody));
            jointDef.bodyA = stoneBody;

            jointDef.localAnchorA = stoneBody->GetLocalPoint(jointPos);
            auto bombBody = bomb->getBody();
            (assert(bombBody));
            jointDef.bodyB = bombBody;
            jointDef.localAnchorB = bombBody->GetLocalPoint(jointPos);
            
            _world->getPhysics()->CreateJoint(&jointDef);
            
        }
        else if (randNumber >= 5 && randNumber <= 18)
        {
            b2Vec2 grassSize = {block.width, 0.5};
            b2Vec2 grassPos = leftCorner;
            grassPos.x += block.width / 2;
            grassPos.y += grassSize.y / 2;
            auto grass = factory.createGrass(grassPos, 0, grassSize);
            
            b2WeldJointDef jointDef;
            auto stoneBody = stone->getBody();
            (assert(stoneBody));
            jointDef.bodyA = stoneBody;
            jointDef.localAnchorA = stoneBody->GetLocalPoint(jointPos);
            auto grassBody = grass->getBody();
            (assert(grassBody));
            jointDef.bodyB = grassBody;
            
            jointDef.localAnchorB = grassBody->GetLocalPoint(jointPos);
            _world->getPhysics()->CreateJoint(&jointDef);
        }
        else if (randNumber == 19)
        {
            b2Vec2 wallPos = leftCorner;
            auto wall = factory.createWall("wall_controller", wallPos, 3);
        }
        
        curLength += block.width;
    }
    
    b2Vec2 exitPos = def.startPos;
    exitPos.x += curLength;
    
    return exitPos;
}

b2Vec2 GameObjectComposer::assembleBridge(const BridgeDef & def)
{
	GameObjectFactory factory = GameObjectFactory(_world);
    
    auto column = factory.createColumn("totem_1", def.startPos, 3);
    auto rm = column->getRightMark();
    auto lm = column->getLeftMark();
    auto gloabalO = def.startPos - lm;
    auto startDynamicPart = gloabalO + rm;
    
	b2Vec2 dir = def.direction;
	dir.Normalize();

	float angle = atan2f(dir.y, dir.x);
    
    b2Vec2 pos{0.0f, 0.0f};

	b2Body* prev = column->getBody();
    
    for (int i = 0; i < def.linkCount; ++i)
	{
        b2BodyType bodyType = b2BodyType::b2_dynamicBody;
        
        float dist = 0.5f * def.linkSize.x + (1 - def.overlap) * i * def.linkSize.x;
        pos = startDynamicPart + dist * dir;
        auto curObj = factory.createBox(pos, angle, def.linkSize, bodyType, "resources/hanging_bridge_0.png");
		b2Body* curBody = curObj->getBody();

        if (i == 0)
		{
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = prev;
            auto correctedPos = curObj->getPosition();
            correctedPos.x -= def.linkSize.x * 0.45f;
            auto localForColumn = prev->GetLocalPoint(correctedPos);
			jointDef.localAnchorA.Set(localForColumn.x, localForColumn.y);
			jointDef.bodyB = curBody;
			jointDef.localAnchorB.Set(-def.linkSize.x * 0.45f, 0.0f);
			_world->getPhysics()->CreateJoint(&jointDef);
		}
        else
        {
            b2RevoluteJointDef jointDef;
            jointDef.bodyA = prev;
            jointDef.localAnchorA.Set(def.linkSize.x * 0.45f, 0.0f);
            jointDef.bodyB = curBody;
            jointDef.localAnchorB.Set(-def.linkSize.x * 0.45f, 0.0f);
            _world->getPhysics()->CreateJoint(&jointDef);
        }
		prev = curBody;
	}
    
    b2Vec2 lastLinkExit = pos;
    lastLinkExit.x += def.linkSize.x * 0.45f;
    
    auto endColumn = factory.createColumn("totem_1", lastLinkExit, 3);
    auto endRm = endColumn->getRightMark();
    auto exitPos = endColumn->getPosition() + endRm;
    
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = prev;
    jointDef.localAnchorA.Set(def.linkSize.x * 0.45f, 0.0f);
    jointDef.bodyB = endColumn->getBody();
    auto t = endColumn->getLeftMark();
    jointDef.localAnchorB.Set(t.x, t.y);
    _world->getPhysics()->CreateJoint(&jointDef);
    
    return exitPos;
}

