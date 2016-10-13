#pragma once

#include <Box2D/Box2D.h>
#include <2d/CCNode.h>
#include <stdio.h>

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
    
    GameCamera(const std::vector<LayerInfo>& layers);
    
    void update(float delta);
    void setPosition(const b2Vec2& camPos);
    
private:
    std::vector<LayerInfo> _layers;
};
