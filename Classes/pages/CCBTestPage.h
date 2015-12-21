#ifndef PLAYING_WITH_COCOS3D_CCBPAGE_TEST_H
#define PLAYING_WITH_COCOS3D_CCBPAGE_TEST_H

#include "cocos2d.h"
#include "cocos_include.h"
#include "pages/SuperPage.h"
//#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "pages/CCBPage.h"

class RootPage;

class CCBTestPage : public CCBPage, public State<RootPage>
{

public:
    CREATE_FUNC(CCBTestPage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void onMenuItemSelected(const std::string &actionName, cocos2d::Ref *target)
        override;

protected:

    CCBTestPage();
    ~CCBTestPage();

private:
};

#endif  //PLAYING_WITH_COCOS3D_CCBPAGE_TEST_H