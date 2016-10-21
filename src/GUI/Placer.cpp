#pragma warning(push, 0)
#include <base/CCDirector.h>
#pragma warning(pop)

#include "Placer.h"

USING_NS_CC;

namespace gui
{
    Placer::Placer(const std::shared_ptr<View> &view) : _view(view), _anchor(-1, -1)
    {
        
    }
    
    Placer::~Placer()
    {
        
    }
    
    Placer Placer::align(gui::Anchor anchorType)
    {
        switch (anchorType) {
            case Anchor::Center:
                _anchor.set(0.5f, 0.5f);
                break;

            case Anchor::BottomLeft:
                _anchor.set(0, 0);
                break;

            case Anchor::BottomRight:
                _anchor.set(0, 1);
                break;

            case Anchor::TopLeft:
                _anchor.set(0, 1);
                break;

            case Anchor::TopRight:
                _anchor.set(1, 1);
                break;
                
            default:
                assert(false);
        }
        
        return *this;
    }
    
    Placer Placer::atScreenCenter()
    {
        assert(_anchor.x > 0 && _anchor.y > 0); //call align first
        
        Size screenSize = Director::getInstance()->getWinSize();
        setPosition({screenSize.width / 2, screenSize.height / 2});
        
        return *this;
    }
    
    Placer Placer::under(std::shared_ptr<View> baseView, Alignment alignment)
    {
        Vec2 baseViewPos = baseView->getPosition();
        Vec2 viewSize = _view->getSize();
        Vec2 baseViewSize = baseView->getSize();
        
        Vec2 viewPos;
        viewPos.y = baseViewPos.y - viewSize.y + _anchor.y * viewSize.y;
        
        if (alignment == Alignment::Left)
            viewPos.x = baseViewPos.x + _anchor.x * viewSize.x;
        else if (alignment == Alignment::Center)
            viewPos.x = baseViewPos.x + baseViewSize.x / 2 - (viewSize.x / 2 - _anchor.x * viewSize.x);
        else if (alignment == Alignment::Right)
            viewPos.x = baseViewPos.x + baseViewSize.x - _anchor.x * viewSize.x;
        
        setPosition(viewPos);
        
        return *this;
    }
    
    void Placer::setPosition(const Vec2 &pos)
    {
        Vec2 viewSize = _view->getSize();
        Vec2 offset(viewSize.x * _anchor.x, viewSize.y * _anchor.y);
        _view->setPosition(pos - offset);
    }
    
    Placer place(const std::shared_ptr<View> &view)
    {
        return Placer(view);
    }
}

