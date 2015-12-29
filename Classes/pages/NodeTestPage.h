#ifndef CPP_DEMO_PAGES_NODE_TEST_PAGE_H
#define CPP_DEMO_PAGES_NODE_TEST_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class NodeTestPage
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(NodeTestPage);

    void loadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void getGrandSon();

    void addMoreChild();
protected:
    NodeTestPage();
    ~NodeTestPage();
};


#endif // CPP_DEMO_PAGES_NODE_TEST_PAGE_H
