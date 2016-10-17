#include "UpdaterFunc.h"

UpdaterFunc::UpdaterFunc(const std::function<void(float)> &delegate) :
_delegate(delegate)
{}

void UpdaterFunc::update(float delta)
{
    _delegate(delta);
}
