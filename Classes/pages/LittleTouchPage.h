#ifndef CPP_DEMO_LITTLE_TOUCH_PAGE_H
#define CPP_DEMO_LITTLE_TOUCH_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class TouchableLayer
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(TouchableLayer);

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

protected:
    TouchableLayer();
    ~TouchableLayer();

};

#endif