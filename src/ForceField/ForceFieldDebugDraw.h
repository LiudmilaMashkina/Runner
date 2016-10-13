#pragma once

#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#include <Box2D/Common/b2Math.h>
#include "Utils/MacroCreate.h"

class IForceField;

class ForceFieldDebugDraw : public cocos2d::Node
{
public:
	virtual void update(float delta) override;
    CC_CREATE_FUNC_4(ForceFieldDebugDraw, initWithField, const std::shared_ptr<IForceField> &, forceField, const b2Vec2 &, fieldSize, float, drawStep, float, maxForce)
     
private:
	ForceFieldDebugDraw() {}
	float getMaxForce(const b2Vec2 & fieldSize, float drawStep);
	virtual bool initWithField(const std::shared_ptr<IForceField> &forceField, const b2Vec2 &fieldSize, float drawStep, float maxForce);
	float _drawStep;
	float _maxForce;
	std::shared_ptr<IForceField> _forceField;
	std::vector<std::vector<cocos2d::Sprite*>> _arrows;
};
