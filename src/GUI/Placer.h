#pragma once
#include <memory>
#include "View.h"
#include "Alignment.h"

namespace gui
{
    enum class Anchor
    {
        Center,
        BottomLeft,
        BottomRight,
        TopLeft,
        TopRight
    };
    
    class Placer
    {
    public:
        Placer(const std::shared_ptr<View> &view);
        ~Placer();
        
        Placer align(Anchor anchorType);
        Placer atScreenCenter();
        Placer under(std::shared_ptr<View> baseView, Alignment alignment);
        
    private:
        void setPosition(const Vec2 &pos);
        
        std::shared_ptr<View> _view;
        Vec2 _anchor;
    };
    
    Placer place(const std::shared_ptr<View> &view);
}

