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

    // button callbacks
    void btnCallback1(cocos2d::Ref *sender);
    void btnCallback2(cocos2d::Ref *sender);
    void btnCallback3(cocos2d::Ref *sender);
    void btnCallback4(cocos2d::Ref *sender);

    struct UserData
    {
        UserData(int i=0) : i_(i) {}
        int i_;
    };

    // callbacks for CallFuncs.
    void callfunc1param(int i);
    void callfunc2param(int i, int j);
    void callfunc3param(int i, int j, UserData userData);

protected:
    CallFuncTestPage();
    ~CallFuncTestPage();
};


#endif 
