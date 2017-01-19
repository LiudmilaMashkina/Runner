#pragma once

#pragma warning(push, 0)

#pragma warning(pop)

class ObjectThemer
{
public:
    enum class ThemeId
    {
        EnumStart = 0,
        Stone,
        Ice,
        Wood,
        EnumEnd
    };

	ObjectThemer();
    ~ObjectThemer();

    ThemeId getTheme();
    
private:
    ThemeId _currentTheme = ThemeId::Stone;
};

 
