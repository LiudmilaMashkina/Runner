//
//  GameCamera.cpp
//  GameLib
//
//  Created by Luda on 28/09/16.
//
//

#include "GameCamera.h"
#include "Utils/Convert.h"

USING_NS_CC;

GameCamera::GameCamera(const std::vector<LayerInfo>& layers) :
_layers(layers)
{}

void GameCamera::setPosition(const b2Vec2 &camPos)
{
    for (int i = 0; i < _layers.size(); ++i)
        _layers[i].layer->setPosition(_layers[i].speedFactor * Convert::toPixels(-camPos));
}
