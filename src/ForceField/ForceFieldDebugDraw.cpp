//
//  ForceFieldDebugDraw.cpp
//  Wanderer
//
//  Created by Luda on 26/10/15.
//
//

#include "ForceFieldDebugDraw.h"
#include "IForceField.h"
#include "2d/CCSprite.h"
#include "Utils/Convert.h"

USING_NS_CC;

bool ForceFieldDebugDraw::initWithField(const std::shared_ptr<IForceField> &forceField, const b2Vec2 &fieldSize, float drawStep, float maxForce)
{
	if (!Node::init())
		return false;
	_forceField = forceField;
	_drawStep = drawStep;
	_maxForce = maxForce;

	for (float x = 0; x < fieldSize.x; x += drawStep)
	{
		std::vector<Sprite*> spritesY;
		for (float y = 0; y < fieldSize.y; y += drawStep)
		{
			auto sprite = Sprite::create("resources/force_arrow.png");
			sprite->setAnchorPoint(Vec2(0, 0.5));
            sprite->setPosition(Convert::toPixels(x), Convert::toPixels(y));
			sprite->setScaleY(0.2f);
			spritesY.push_back(sprite);
			addChild(sprite);
		}
		_arrows.push_back(spritesY);
	}
	return true;
}

void ForceFieldDebugDraw::update(float delta)
{
	for (float x = 0; x < _arrows.size(); ++x)
	{
		for (float y = 0; y < _arrows[x].size(); ++y)
		{
			b2Vec2 force = _forceField->getForce(b2Vec2(x * _drawStep, y * _drawStep));
			float forceLength = force.Length();
			float normalizedLength = forceLength * _drawStep / _maxForce;
            float scale = normalizedLength / Convert::toMeters(_arrows[x][y]->getContentSize().width);
			_arrows[x][y]->setScaleX(scale);

			b2Vec2 normalizedForce = force;
			normalizedForce.Normalize();

			float radAngel = atan2(normalizedForce.y, normalizedForce.x);
			float degAngel = CC_RADIANS_TO_DEGREES(radAngel);
			_arrows[x][y]->setRotation(-degAngel);
		}
	}
}

float ForceFieldDebugDraw::getMaxForce(const b2Vec2 & fieldSize, float drawStep)
{
	float maxForceLength = (_forceField->getForce(b2Vec2(0, 0))).Length();

	for (float x = 0; x < fieldSize.x; x += drawStep)
	{
		for (float y = 0; y < fieldSize.y; y += drawStep)
		{
			b2Vec2 force = _forceField->getForce(b2Vec2(x, y));
			float forceLength = force.Length();
			if (forceLength > maxForceLength)
				maxForceLength = forceLength;
		}
	}
	return maxForceLength;
}
