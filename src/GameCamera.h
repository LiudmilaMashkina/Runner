#pragma once

#include <Box2D/Box2D.h>
#include <2d/CCNode.h>
#include "IUpdatable.h"
#include "Utils/MacroCreate.h"

class GameCamera
{
public:
    struct LayerInfo
    {
        cocos2d::Node* layer = nullptr;
        float speedFactor = 0.0f;
        float zoomFactor = 0.0f;
        bool clamp = false;
    };
    
    CREATE_FUNC_0(GameCamera);
    
    void update(float delta);
    
    void setPosition(const b2Vec2& camPos);
    b2Vec2 getPosition() const;
    
    void addLayer(const LayerInfo& layer);
    
private:
    GameCamera();
    
    std::vector<LayerInfo> _layers;
    b2Vec2 _position = {0, 0};
};
