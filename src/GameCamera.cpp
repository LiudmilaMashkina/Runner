//
//  GameCamera.cpp
//  GameLib
//
//  Created by Luda on 28/09/16.
//
//

#include "GameCamera.h"
#include "Utils/Convert.h"
#include "Utils/Environment.h"

USING_NS_CC;

GameCamera::GameCamera()
{}

void GameCamera::setPosition(const b2Vec2 &camPos)
{
    _position = camPos;
    
    for (int i = 0; i < _layers.size(); ++i)
    {
        Vec2 layerPos = _layers[i].speedFactor * Convert::toPixels(-camPos);
        Vec2 pixScreenSize = Convert::toPixels(Environment::getScreenSize());
        
        if (!_layers[i].clamp)
            _layers[i].layer->setPosition(layerPos);
        else
        {
            Vec2 pos;
            pos.x = fmodf(layerPos.x, pixScreenSize.x);
            pos.y = fmodf(layerPos.y, pixScreenSize.y);
            
            if (pos.y > 0)
                pos.y -= pixScreenSize.y;
            
            _layers[i].layer->setPosition(pos);
        }
    }
}

b2Vec2 GameCamera::getPosition() const
{
    return _position;
}

void GameCamera::addLayer(const GameCamera::LayerInfo &layer)
{
    _layers.push_back(layer);
}
