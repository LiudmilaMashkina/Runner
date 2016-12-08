#pragma warning(push, 0)
#include <2d/CCSpriteFrame.h>
#pragma warning(pop)

#include "GameObjectFactory.h"
#include "IGameObject.h"
#include "SimpleGameObject.h"
#include "Bomb.h"
#include "Bulb.h"
#include "BridgeColumn.h"
#include "Grass.h"
#include "AnimationObject.h"
#include "ParticlesObject.h"
#include "WallController.h"
#include "WallStone.h"
#include "Particles/ParticlesFactory.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"
#include "json/document.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;

GameObjectFactory::GameObjectFactory(GameWorld* world) :
	_world(world)
{}

std::shared_ptr<SimpleGameObject> GameObjectFactory::createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string& fileName)
{
	Sprite* sprite = createSprite(fileName, size); 
	
	b2PolygonShape physShape;
	physShape.SetAsBox(size.x / 2, size.y / 2);
	b2Body* body = createBody(type, &physShape, pos, angle);
	
	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);
    
    IGameObject* iobj = obj.get();
    body->SetUserData(iobj);

	return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createStaticStone(const b2Vec2 & topLeftCornerPos, float width, const std::string & fileName, float* outHeight)
{
	Sprite* sprite = createSprite(fileName);

	Vec2 spriteSize = sprite->getContentSize();
	float scale = width / Convert::toMeters(spriteSize.x);

	sprite->setScale(scale);

	b2Vec2 bodySize = Convert::toMeters(spriteSize * scale);
	b2Vec2 bodyCenter = topLeftCornerPos + b2Vec2(bodySize.x / 2, -bodySize.y / 2);

	b2PolygonShape physShape;
	physShape.SetAsBox(bodySize.x / 2, bodySize.y / 2);
	b2Body* body = createBody(b2BodyType::b2_staticBody, &physShape, bodyCenter, 0);
    
	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

    IGameObject* iobj = obj.get();
    body->SetUserData(iobj);
    
    if (outHeight)
        *outHeight = bodySize.y;
    
    int bulbQuantity = Environment::generateIntRand(1, 4);
    
    addBulbs(bulbQuantity, bodySize, topLeftCornerPos, body);
    
    return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string& fileName)
{
	b2CircleShape physShape;
	physShape.m_p.Set(0, 0);
	physShape.m_radius = radius;

	b2Body* body = createBody(b2BodyType::b2_dynamicBody, &physShape, pos, angle);

	Sprite* sprite = createSprite(fileName, b2Vec2(radius * 2, radius * 2));

	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

	return obj;
}

std::shared_ptr<Bomb> GameObjectFactory::createBomb(const b2Vec2 &pos, float angle, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, angle);
    
    auto particles = createBombParticles(pos);
    
    std::shared_ptr<Bomb> obj = Bomb::create(body, _world, particles);
    _world->addObject(obj);
    
    IGameObject* ibomb = obj.get();
    body->SetUserData(ibomb);
    
    return obj;
}

std::shared_ptr<Grass> GameObjectFactory::createGrass(const b2Vec2 &pos, float angle, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, angle);
    auto sprite = createSprite("resources/grass_1.png", size);
    auto particles = createGrassParticles(pos, size);
    
    std::shared_ptr<Grass> obj = Grass::create(body, _world, sprite, particles);
    _world->addObject(obj);
    
    particles->setPaused(true);

    IGameObject* igrass = obj.get();
    body->SetUserData(igrass);
    
    return obj;
}

std::shared_ptr<Bulb> GameObjectFactory::createBulb(const b2Vec2 &pos, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, 0);
    auto sprite = createSprite("resources/spongebob.png", size);
    
    std::shared_ptr<Bulb> obj = Bulb::create(body, _world, sprite);
    _world->addObject(obj);
    
    IGameObject* ibulb = obj.get();
    body->SetUserData(ibulb);
    
    return obj;
}

std::shared_ptr<BridgeColumn> GameObjectFactory::createColumn(const std::string & objName, const b2Vec2& pos, float height)
{
    std::string content = FileUtils::getInstance()->getStringFromFile("resources/objects.json");
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    
    const rapidjson::Value &jObject = doc[objName.c_str()];
    std::string texturePath = jObject["texture_path"].GetString(); // don't use yet
    
    const rapidjson::Value &jSize = jObject["original_size"];
    b2Vec2 originalSize;
    originalSize.x = jSize["x"].GetDouble();
    originalSize.y = jSize["y"].GetDouble();
    
    float scale = height / originalSize.y;
    
    const rapidjson::Value &jVertices = jObject["vertices"];
    unsigned int verticesSize = jVertices.Size();
    V3F_C4B_T2F* vertices = new V3F_C4B_T2F[verticesSize];
    for (rapidjson::SizeType i = 0; i < verticesSize; ++i)
    {
        const rapidjson::Value &jVertex = jVertices[i];
        
        V3F_C4B_T2F vert;
        
        b2Vec2 pos;
        pos.x = jVertex["pos"]["x"].GetDouble() * scale;
        pos.y = jVertex["pos"]["y"].GetDouble() * scale;
        
        b2Vec2 tex_co;
        tex_co.x = jVertex["tex_co"]["u"].GetDouble();
        tex_co.y = 1 - jVertex["tex_co"]["v"].GetDouble();
        
        vert.vertices.set(pos.x, pos.y, 0);
        vert.texCoords = Tex2F(tex_co.x, tex_co.y);
        vert.colors = Color4B::WHITE;
        
        vertices[i] = vert;
    }
    
    const rapidjson::Value &jIndices = jObject["indices"];
    size_t indicesSize = jIndices.Size();
    unsigned short* indices = new unsigned short[indicesSize];
    for (rapidjson::SizeType i = 0; i < indicesSize; ++i)
    {
        const rapidjson::Value &jIndex = jIndices[i];
        indices[i] = jIndex.GetUint();
    }
    
    b2Vec2 lm = getLeftMark(jObject);
    lm.x *= scale;
    lm.y *= scale;
    
    b2Vec2 globOriginPos = pos - lm;

    b2Body* body = createBody(vertices, indices, indicesSize, globOriginPos);
    
    ////////////////////////////////////////
    
    // use function createSprite(...)
    float PTM = Environment::getPTMratio();
    
    for (size_t i = 0; i < verticesSize; ++i)
    {
        vertices[i].vertices.x *= PTM;
        vertices[i].vertices.y *= PTM;
    }
    Sprite* sprite = createSprite("resources/totem-pole.png", vertices, indices, indicesSize, verticesSize);
    _world->getGraphics()->addChild(sprite);
    
    std::shared_ptr<BridgeColumn> column = BridgeColumn::create(body, sprite, _world);
    
    const rapidjson::Value &jChildren = jObject["children"];
    size_t childrenSize = jChildren.Size();
    for (rapidjson::SizeType i = 0; i < childrenSize; ++i)
    {
        const rapidjson::Value &jChild = jChildren[i];
        std::string childType = jChild["type"].GetString();
        
        if (childType == "left_mark")
        {
            const rapidjson::Value &jLocation = jChild["location"];
            b2Vec2 leftMark;
            leftMark.x = jLocation["x"].GetDouble() * scale;
            leftMark.y = jLocation["y"].GetDouble() * scale;
            column->setLeftMark(leftMark);
        }
        else if (childType == "right_mark")
        {
            const rapidjson::Value &jLocation = jChild["location"];
            b2Vec2 rightMark;
            rightMark.x = jLocation["x"].GetDouble() * scale;
            rightMark.y = jLocation["y"].GetDouble() * scale;
            column->setRightMark(rightMark);
        }
        
        else if (childType == "bomb")
        {
            const rapidjson::Value &jLocation = jChild["location"];
            b2Vec2 bombPos;
            bombPos.x = jLocation["x"].GetDouble() * scale;
            bombPos.y = jLocation["y"].GetDouble() * scale;
            bombPos += globOriginPos;
            
            auto bomb = createBomb(bombPos, 0, b2Vec2(0.5, 0.5));
            
            b2WeldJointDef jointDef;
            jointDef.bodyA = body;
            
            auto localForColumn = body->GetLocalPoint(bombPos);
            jointDef.localAnchorA.Set(localForColumn.x, localForColumn.y);
            auto bombBody = bomb->getBody();
            (assert(bombBody));
            jointDef.bodyB = bombBody;
            jointDef.localAnchorB.Set(0.0f, 0.0f);
            _world->getPhysics()->CreateJoint(&jointDef);
        }
    }
    _world->addObject(column);
    
    IGameObject* icolumn = column.get();
    body->SetUserData(icolumn);
    
    return column;
}

std::shared_ptr<WallController> GameObjectFactory::createWall(const std::string& controllerName, const b2Vec2& pos, float height)
{
    std::shared_ptr<WallController> controller = WallController::create(_world, pos);
    std::string content = FileUtils::getInstance()->getStringFromFile("resources/objects.json");
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    
    const rapidjson::Value &jObject = doc[controllerName.c_str()];
    float totalHeight = jObject["total_height"].GetDouble();
    float totalScale = height / totalHeight;
    
    const rapidjson::Value &jChildren = jObject["children"];
    
    size_t childrenSize = jChildren.Size();
    for (rapidjson::SizeType i = 0; i < childrenSize; ++i)
    {
        const rapidjson::Value &jStone = jChildren[i];
        
        std::string texturePath = jStone["texture_path"].GetString();
        std::size_t found = texturePath.find("/");
        std::string imageName = texturePath.substr(found + 1, texturePath.size() - 1);
        std::string texture = "resources/" + imageName;
        
        const rapidjson::Value &jLocation = jStone["location"];
        b2Vec2 globalPos = pos;
        globalPos.x += jLocation["x"].GetDouble() * totalScale;
        globalPos.y += jLocation["y"].GetDouble() * totalScale;
        
        const rapidjson::Value &jVertices = jStone["vertices"];
        unsigned int verticesSize = jVertices.Size();
        V3F_C4B_T2F* vertices = new V3F_C4B_T2F[verticesSize];
        for (rapidjson::SizeType j = 0; j < verticesSize; ++j)
        {
            const rapidjson::Value &jVertex = jVertices[j];
            
            V3F_C4B_T2F vert;
            
            b2Vec2 vertPos;
            vertPos.x = jVertex["pos"]["x"].GetDouble() * totalScale;
            vertPos.y = jVertex["pos"]["y"].GetDouble() * totalScale;
            
            b2Vec2 tex_co;
            tex_co.x = jVertex["tex_co"]["u"].GetDouble();
            tex_co.y = 1 - jVertex["tex_co"]["v"].GetDouble();
            
            vert.vertices.set(vertPos.x, vertPos.y, 0);
            vert.texCoords = Tex2F(tex_co.x, tex_co.y);
            vert.colors = Color4B::WHITE;
            
            vertices[j] = vert;
        }
        
        const rapidjson::Value &jIndices = jStone["indices"];
        size_t indicesSize = jIndices.Size();
        unsigned short* indices = new unsigned short[indicesSize];
        for (rapidjson::SizeType j = 0; j < indicesSize; ++j)
        {
            const rapidjson::Value &jIndex = jIndices[j];
            indices[j] = jIndex.GetUint();
        }
        
        b2Body* body = createBody(vertices, indices, indicesSize, globalPos);
        
        ////////////////////////////////////////
        
        // use function createSprite(...)
        float PTM = Environment::getPTMratio();
        
        for (size_t j = 0; j < verticesSize; ++j)
        {
            vertices[j].vertices.x *= PTM;
            vertices[j].vertices.y *= PTM;
        }
        Sprite* sprite = createSprite(texture, vertices, indices, indicesSize, verticesSize);
        _world->getGraphics()->addChild(sprite);
        
        std::shared_ptr<WallStone> stone = WallStone::create(body, sprite, _world, controller);
        
        _world->addObject(stone);
        
        IGameObject* istone = stone.get();
        body->SetUserData(istone);
        
        controller->addStone(stone);
    }
    _world->addObject(controller);

    return controller;
}


std::shared_ptr<AnimationObject> GameObjectFactory::createBombExplosion(const b2Vec2& pos)
{
    Vector<SpriteFrame*> frames;
    
    for (int i = 0; i < 4; ++i)
    {
        std::string fString = "resources/bomb_" + std::to_string(i) + ".png";
        Rect fRect;
        fRect.size = Size(64, 64);
        fRect.origin = Vec2(0, 0);
        SpriteFrame* frame = SpriteFrame::create(fString, fRect);
        
        frames.pushBack(frame);
    }
    
    std::shared_ptr<AnimationObject> animation = std::shared_ptr<AnimationObject>(new AnimationObject(_world, frames, 10, false));
    animation->setPosition(pos);
    _world->addObject(animation);
    
    return animation;
}

std::shared_ptr<ParticlesObject> GameObjectFactory::createBombParticles(const b2Vec2& pos)
{
    auto system = ParticlesFactory::createBombParticles(_world->getTimeProvider(), _world->getGraphics());
    std::shared_ptr<ParticlesObject> obj = ParticlesObject::create(system, _world) ;
    _world->addObject(obj);

    return obj;
}

std::shared_ptr<ParticlesObject> GameObjectFactory::createGrassParticles(const b2Vec2 &pos, const b2Vec2& diapason)
{
    auto system = ParticlesFactory::createGrassParticles(_world->getTimeProvider(), _world->getGraphics(), diapason);
    std::shared_ptr<ParticlesObject> obj = ParticlesObject::create(system, _world);
    _world->addObject(obj);
    
    return obj;
}

b2Body* GameObjectFactory::createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = pos;
	bodyDef.angle = angle;
	bodyDef.linearDamping = 5;
	bodyDef.angularDamping = 5;
	b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = shape;
	bodyFixtureDef.density = 1;
	body->CreateFixture(&bodyFixtureDef);

	return body;
}

b2Body* GameObjectFactory::createBody(V3F_C4B_T2F* vertices, unsigned short* indices, int indicesSize, const b2Vec2& pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = pos;
    b2Body *body = _world->getPhysics()->CreateBody(&bodyDef);
    
    for (int i = 0; i < indicesSize; i += 3)
    {
        int a0 = indices[i];
        int a1 = indices[i + 1];
        int a2 = indices[i + 2];
        
        b2Vec2 verts[3];
        verts[0] = b2Vec2(vertices[a0].vertices.x, vertices[a0].vertices.y);
        verts[1] = b2Vec2(vertices[a1].vertices.x, vertices[a1].vertices.y);
        verts[2] = b2Vec2(vertices[a2].vertices.x, vertices[a2].vertices.y);
        
        b2PolygonShape physShape;
        physShape.Set(verts, 3);
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &physShape;
        fixtureDef.density = 1;
        fixtureDef.friction = 0.3;
        body->CreateFixture(&fixtureDef);
    }
    
    return body;
}

b2Body* GameObjectFactory::createSensor(b2BodyType type, b2Shape *shape, const b2Vec2 &pos, float angle)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position = pos;
    bodyDef.angle = angle;
    bodyDef.linearDamping = 5;
    bodyDef.angularDamping = 5;
    b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);
    
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = shape;
    bodyFixtureDef.density = 1;
    bodyFixtureDef.isSensor = true;
    body->CreateFixture(&bodyFixtureDef);
    
    return body;
}

Sprite* GameObjectFactory::createSprite(const std::string& textureName, const b2Vec2& bodySize)
{
	auto sprite = Sprite::create(textureName);
	_world->getGraphics()->addChild(sprite);

	scale(bodySize, sprite);

	return sprite;
}

Sprite* GameObjectFactory::createSprite(const std::string& textureName)
{
	auto sprite = Sprite::create(textureName);
	_world->getGraphics()->addChild(sprite);

	return sprite;
}

Sprite* GameObjectFactory::createSprite(const std::string & textureName, V3F_C4B_T2F* verts, unsigned short * indices, int indexSize, int vertSize)
{
    assert(vertSize > 0);
    
    cocos2d::Vec2 bl; //bottm left
    cocos2d::Vec2 tr; //top right
    
    auto compareByX = [](const V3F_C4B_T2F &left, const V3F_C4B_T2F &right)
    {
        return left.vertices.x < right.vertices.x;
    };
    
    auto compareByY = [](const V3F_C4B_T2F &left, const V3F_C4B_T2F &right)
    {
        return left.vertices.y < right.vertices.y;
    };
    
    bl.x = std::min_element(verts, verts + vertSize, compareByX)->vertices.x;
    bl.y = std::min_element(verts, verts + vertSize, compareByY)->vertices.y;
    
    tr.x = std::max_element(verts, verts + vertSize, compareByX)->vertices.x;
    tr.y = std::max_element(verts, verts + vertSize, compareByY)->vertices.y;
    
    for (int i = 0; i < vertSize; ++i)
    {
        verts[i].vertices.x -= bl.x;
        verts[i].vertices.y -= bl.y;
    }
    
    PolygonInfo info;
    info.filename = textureName;
    info.rect.setRect(0, 0, tr.x - bl.x, tr.y - bl.y);
    
    TrianglesCommand::Triangles data;
    data.verts = verts;
    data.vertCount = vertSize;
    data.indices = indices;
    data.indexCount = indexSize;
    
    info.triangles = data;
    
    auto sprite = Sprite::create(info);
    cocos2d::Vec2 anchorPoint(-bl.x / (tr.x - bl.x), -bl.y / (tr.y - bl.y));
    sprite->setAnchorPoint(anchorPoint);
    
    //scale(bodySize, sprite);
    
    return sprite;
}

void GameObjectFactory::addBulbs(int quantity, const b2Vec2 &bodySize, const b2Vec2 &topLeftCorner, b2Body *body)
{
    for (; quantity > 0; --quantity)
    {
        int side = Environment::generateIntRand(1, 4);
        b2Vec2 bulbPos = topLeftCorner;
        
        if (side == 1)
        {
            float posX = Environment::generateFloatRand(0.0f, bodySize.x);
            bulbPos.x += posX;
        }
        else if (side == 2)
        {
            bulbPos.x = topLeftCorner.x + bodySize.x;
            float posY = Environment::generateFloatRand(0.0f, bodySize.y);
            bulbPos.y -= posY;
        }
        else if (side == 3)
        {
            float posX = Environment::generateFloatRand(0.0f, bodySize.x);
            bulbPos.x += posX;
            bulbPos.y = topLeftCorner.y - bodySize.y;
        }
        else if (side == 4)
        {
            float posY = Environment::generateFloatRand(0.0f, bodySize.y);
            bulbPos.y -= posY;
        }
        
        float bSize = Environment::generateFloatRand(0.15, 0.4);
        auto bulb = createBulb(bulbPos, b2Vec2(bSize, bSize));
        
        bulb->lightOn(false);
        
        b2WeldJointDef jointDef;
        jointDef.bodyA = body;
        
        auto localForStone = body->GetLocalPoint(bulbPos);
        jointDef.localAnchorA.Set(localForStone.x, localForStone.y);
        auto bulbBody = bulb->getBody();
        (assert(bulbBody));
        jointDef.bodyB = bulbBody;
        jointDef.localAnchorB.Set(0.0f, 0.0f);
        _world->getPhysics()->CreateJoint(&jointDef);
    }
}

void GameObjectFactory::scale(const b2Vec2& size, cocos2d::Sprite * sprite)
{
	Size spriteSize = sprite->getContentSize();

	float x = Convert::toPixels(size.x) / spriteSize.width;
	float y = Convert::toPixels(size.y) / spriteSize.height;

	sprite->setScale(x, y);
}

b2Vec2 GameObjectFactory::getLeftMark(const rapidjson::Value &jObject)
{
    const rapidjson::Value &jChildren = jObject["children"];
    size_t childrenSize = jChildren.Size();
    for (rapidjson::SizeType i = 0; i < childrenSize; ++i)
    {
        const rapidjson::Value &jChild = jChildren[i];
        std::string childType = jChild["type"].GetString();
        
        if (childType == "left_mark")
        {
            const rapidjson::Value &jLocation = jChild["location"];
            b2Vec2 leftMark;
            leftMark.x = jLocation["x"].GetDouble();
            leftMark.y = jLocation["y"].GetDouble();
            
            return leftMark;
        }
    }
    return {0, 0};
}
    
    /*
     std::vector<std::string> GameObjectFactory::getListOfGrounds()
{
    std::string content = FileUtils::getInstance()->getStringFromFile("objects.json");
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    
    std::vector<std::string> objects;
    
    for (auto it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
    {
        std::string objName = it->name.GetString();
        objects.push_back(objName);
    }
    
    return objects;
}

*/


