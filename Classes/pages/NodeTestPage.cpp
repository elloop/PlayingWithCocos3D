#include "pages/NodeTestPage.h"
#include "cocos_include.h"
#include "message/MessageCenter.h"
#include "PageManager.h"

USING_NS_CC;

bool nodeTestPageCreated = PageManager::getInstance()->registerPage(
    "NodeTestPage", NodeTestPage::create());

NodeTestPage::NodeTestPage()
{

}

NodeTestPage::~NodeTestPage()
{

}
void NodeTestPage::loadUI()
{
    // delete background.
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);

    // test getChildByName, parent only search son, won't search grandson.
    auto son = LayerColor::create(CocosUtil::randomC4b(),
        CocosWindow::size().width / 4, CocosWindow::size().height / 4);
    son->setPosition(Vec2(CocosWindow::size().width / 4,
        CocosWindow::size().height / 2 - son->getContentSize().height / 2));
    ADD_CHILD_WITH_NAME(this, son);

    auto grandSon = LayerColor::create(CocosUtil::randomC4b(),
        CocosWindow::size().width / 6, CocosWindow::size().height / 6);
    ADD_CHILD_WITH_NAME(son, grandSon);

    auto label = Label::createWithSystemFont("", "arial.ttf", 30);
    label->setPosition(Point(son->getPositionX() + son->getContentSize().width, 
        son->getPositionY() - label->getContentSize().height));
    ADD_CHILD_WITH_NAME(this, label);
}

void NodeTestPage::onEnterState()
{
    loadUI();
    auto son = getChildByName("son");
    if (son)
    {
        son->runAction(RotateBy::create(1.5, 360));

        auto delay1s = DelayTime::create(1.5);
        auto seq = Sequence::create(DelayTime::create(1.5),
            CallFunc::create(CC_CALLBACK_0(NodeTestPage::getGrandSon, this)),
            nullptr);

        son->runAction(seq);
    }
}

void NodeTestPage::onExecuteState()
{

}

void NodeTestPage::onExitState()
{
    unloadUI();
}

void NodeTestPage::getGrandSon()
{
    auto grandSon = getChildByName("grandSon");
    if (!grandSon)
    {
        //MessageBox("no child called grandSon", "warning");
        auto label = getChildByName<Label*>("label");
        label->setString("no child called grandSon");
    }

    auto grand = getChildByName("son")->getChildByName("grandSon");
    if (grand) 
    {
        grand->runAction(RotateBy::create(0.5, -180));
    }
}

void NodeTestPage::addMoreChild()
{
    Node *c1 = Node::create();
    ADD_CHILD_WITH_NAME(this, c1);

}

// 14 05 内测试 2D
// 151205 3D VR WEB VR
