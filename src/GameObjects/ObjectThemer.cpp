#pragma warning(push, 0)

#pragma warning(pop)
#include "ObjectThemer.h"
#include "Utils/Environment.h"


ObjectThemer::ObjectThemer()
{}

ObjectThemer::ThemeId ObjectThemer::getTheme()
{
    int start = static_cast<int>(ObjectThemer::ThemeId::EnumStart) + 1;
    int end = static_cast<int>(ObjectThemer::ThemeId::EnumEnd) - 1;
    
    return static_cast<ObjectThemer::ThemeId>(Environment::generateIntRand(start, end));
}
