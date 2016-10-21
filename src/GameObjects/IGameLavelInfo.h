#pragma once

class IGameLavelInfo
{
public:
    virtual float getCurrentBottom(float valueX) = 0;
    virtual ~IGameLavelInfo() {};
};
