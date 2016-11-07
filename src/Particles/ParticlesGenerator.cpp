#pragma warning(push, 0)
#include <2d/CCSprite.h>
#pragma warning(pop)

#include "ParticlesGenerator.h"
#include "Particle.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"
#include "ParticlesSystem.h"

USING_NS_CC;

std::shared_ptr<ParticlesGenerator> ParticlesGenerator::create(const Params &params, cocos2d::Node* layerNode)
{
    return std::shared_ptr<ParticlesGenerator>(new ParticlesGenerator(params, layerNode));
}

ParticlesGenerator::ParticlesGenerator(const Params &params, cocos2d::Node* layerNode) :
_params(params),
_parentNode(layerNode)
{
}

void ParticlesGenerator::update(float delta, ParticlesSystem& system)
{
    _cooldown -= delta;
    if (_cooldown <= 0 && !_paused)
    {
        Particle particle;
        particle.sprite = Sprite::create(_params.fileName);
        float velocityX = Environment::generateFloatRand(_params.velocityRange.min.x, _params.velocityRange.max.x);
        float velocityY = Environment::generateFloatRand(_params.velocityRange.min.y, _params.velocityRange.max.y);
        particle.velocity = b2Vec2(velocityX, velocityY);
        particle.mass = Environment::generateFloatRand(_params.massRange.min, _params.massRange.max);
        float ttl = Environment::generateFloatRand(_params.ttlRange.min, _params.ttlRange.max);
        particle.ttl = ttl;
        particle.constTtl = ttl;
        particle.opacity = 255.0f;
        //particle.sprite->setColor(cocos2d::Color3B::YELLOW);
        b2Vec2 partPos = _params.position;
        partPos.x += Environment::generateFloatRand(_params.generationRange.min.x, _params.generationRange.max.x);
        partPos.y += Environment::generateFloatRand(_params.generationRange.min.y, _params.generationRange.max.y);
        particle.sprite->setPosition(Convert::toPixels(partPos));
        
        _parentNode->addChild(particle.sprite);
        system.addParticle(particle);
        
        _cooldown = 1 / _params.rate;
    }
}

void ParticlesGenerator::setPosition(const b2Vec2 &position)
{
    _params.position = position;
}

void ParticlesGenerator::setPaused(bool paused)
{
    _paused = paused;
}

bool ParticlesGenerator::isPaused()
{
    return _paused;
}
