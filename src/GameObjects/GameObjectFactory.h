#pragma once

#pragma warning(push, 0)
#include <2d/CCSprite.h>
#pragma warning(pop)

#include "GameWorld.h"
#include "IGameObject.h"
#include "json/document.h"
#include "AnimationEngine/IAnimation.h"

class SimpleGameObject;
class Bomb;
class Bulb;
class Grass;
class AnimationObject;
class ParticlesObject;
class BridgeColumn;
class WallController;
class Coin;


class GameObjectFactory 
{
public:
	GameObjectFactory(GameWorld* world);
	std::shared_ptr<SimpleGameObject> createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string& fileName);
	
    std::shared_ptr<IGameObject> createStaticStone(const b2Vec2& topLeftCornerPos, float width, const std::string& fileName, const std::string& chippingPrefix, float* outHeight = nullptr);
    
    std::shared_ptr<IGameObject> createLightingStone(const b2Vec2& topLeftCorner, float width, const std::string& fileName, const std::string& lightingName, const std::string& chippingPrefix, float* outHeight = nullptr);
	
    std::shared_ptr<IGameObject> createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string& fileName);
    
    std::shared_ptr<Bomb> createBomb(const b2Vec2& pos,
                                     float angle,
                                     const b2Vec2& size);
    std::shared_ptr<AnimationObject> createBombExplosion(const b2Vec2& pos,
                                                         float scale);
    std::shared_ptr<Grass> createGrass(const b2Vec2& pos,
                                       float angle,
                                       const b2Vec2& size);
    std::shared_ptr<Bulb> createBulb(const b2Vec2& pos, const b2Vec2& size);
    std::shared_ptr<BridgeColumn> createColumn(const std::string& objName, const b2Vec2& pos, float height);
    std::shared_ptr<WallController> createWall(const std::string& controllerName, const b2Vec2& pos, float height);
    std::shared_ptr<Coin> createCoin(const b2Vec2& pos);
private:
    b2Body* createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
    b2Body* createBody(cocos2d::V3F_C4B_T2F* vertices, unsigned short* indices, int indicesSize, const b2Vec2& pos);
    b2Body* createDecorativeBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
    b2Body* createSensor(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
	
    cocos2d::Sprite* createSprite(const std::string& textureName, const b2Vec2& bodySize);
	cocos2d::Sprite* createSprite(const std::string& textureName);
    cocos2d::Sprite* createSprite(const std::string & textureName,
                                  cocos2d::V3F_C4B_T2F* verts, unsigned short * indices,
                                  int indexSize,
                                  int vertSize);
    
    std::shared_ptr<ParticlesObject> createBombParticles(const b2Vec2& pos);
    std::shared_ptr<ParticlesObject> createGrassParticles(const b2Vec2& pos, const b2Vec2& diapason);
    std::shared_ptr<ParticlesObject> createChippingParticles(const std::vector<std::string>& fileNames);
    void createStoneHeap(const b2Vec2& pos, int quantity, const std::string& imageName);
    cocos2d::Vector<cocos2d::SpriteFrame*> createFramesForAnimation(int numFrames, std::string namePrefix, const cocos2d::Size& frameSize);
    
    void addBulbs(int quantity, const b2Vec2& bodySize, const b2Vec2& topLeftCorner, b2Body* body);
    
	static void scale(const b2Vec2& size, cocos2d::Sprite* sprite);
    
    b2Vec2 getLeftMark(const rapidjson::Value &jObject);
    

	GameWorld* _world = nullptr;
}; 
