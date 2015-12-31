#ifndef CPP_DEMO_PAGES_CallFuncTestPagePAGE_H
#define CPP_DEMO_PAGES_CallFuncTestPagePAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class CallFuncTestPage
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(CallFuncTestPage);

    void loadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void noparam();

    // button callbacks
    void btnCallback1(cocos2d::Ref *sender);
    void btnCallback2(cocos2d::Ref *sender);
    void btnCallback3(cocos2d::Ref *sender);
    void btnCallback4(cocos2d::Ref *sender);

protected:
    CallFuncTestPage();
    ~CallFuncTestPage();
};


#endif 
