#pragma once

#include <Box2D/Common/b2Math.h>
#include "ISystemUpdater.h"
#include "2d/CCNode.h"

class IForceField;

template <typename T>
struct Diapason
{
    T min = T();
    T max = T();
    
    void set(const T &min, const T &max)
    {
        this->min = min;
        this->max = max;
    }
};

class ParticlesGenerator : public ISystemUpdater
{
public:
    struct Params
    {
        std::string fileName;
        float rate = 0;
        Diapason<b2Vec2> velocityRange;
        Diapason<float> massRange;
        b2Vec2 position = {0, 0};
        Diapason<b2Vec2> generationRange;
        std::shared_ptr<IForceField> field;
        Diapason<float> ttlRange;
    };
    
    void update(float delta, ParticlesSystem& system) override;
    void setPosition(const b2Vec2 &position);
    static std::shared_ptr<ParticlesGenerator> create(const Params &params, cocos2d::Node* layerNode);
    
private:
    ParticlesGenerator(const Params &params, cocos2d::Node* layerNode);
    
    Params _params;
    cocos2d::Node* _parentNode = nullptr;
    float _cooldown = 0.0;
};
