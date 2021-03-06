#ifndef CPP_DEMO_LAYER_ROOTPAGE_H
#define CPP_DEMO_LAYER_ROOTPAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"

namespace extension {
    class ScrollView;
}

class PageManager;
class RootPage : public SuperPage, public State<LogicDirector>
{
    friend PageManager;
public:
    CREATE_FUNC(RootPage);

    void loadUI() override;
    void unloadUI() override { removeAllChildrenWithCleanup(true); }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

protected:
    RootPage();
    ~RootPage();
    void addMenuButtons();
    void quitGame(cocos2d::Ref *sender);
    void goHome(cocos2d::Ref *sender);

private:
    cocos2d::Layer        *backLayer_;
    cocos2d::Layer        *middleLayer_;
    cocos2d::Layer        *frontLayer_;
    StateMachine<RootPage>  *stateMachine_;
    extension::ScrollView *scrollView_;
};

RootPage* rootPage();

#endif