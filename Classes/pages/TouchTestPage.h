#ifndef CPP_DEMO_PAGES_MENU_PAGE_H
#define CPP_DEMO_PAGES_MENU_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class TouchTestPage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(TouchTestPage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
        override;
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
        override;
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
        override;
    void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
        override;

    // menu item callback
    void menuCallback(cocos2d::Ref * target);
protected:
    TouchTestPage();
    ~TouchTestPage();

private:
    bool                isTouchingColorLayer_;
    cocos2d::Point    touchBeginPoint_;
};

class Dog : public cocos2d::Sprite
{
public:
    static Dog* create(const char *name);
    bool initWithString(const char *name);
    cocos2d::Rect rect() const;

    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

protected:
    Dog();
    ~Dog();
};

#endif