#include "pages/CallFuncTestPage.h"
#include "PageManager.h"
USING_NS_CC;

bool CallFuncTestPage_created = PageManager::getInstance()->registerPage(
    "CallFuncTestPage", CallFuncTestPage::create());

CallFuncTestPage::CallFuncTestPage()
{

}

CallFuncTestPage::~CallFuncTestPage()
{

}

void CallFuncTestPage::loadUI()
{

    // add three btns.
    auto btn1 = MenuItemImage::create(
        "DemoIcon/home_small.png", 
        "DemoIcon/home_small.png", 
        CC_CALLBACK_1(CallFuncTestPage::btnCallback1, this));

    auto btn2 = MenuItemImage::create(
        "DemoIcon/home_small.png",
        "DemoIcon/home_small.png",
        CC_CALLBACK_1(CallFuncTestPage::btnCallback2, this));

    auto btn3 = MenuItemImage::create(
        "DemoIcon/home_small.png",
        "DemoIcon/home_small.png",
        CC_CALLBACK_1(CallFuncTestPage::btnCallback3, this));

    // btn2 in center. btn1 in left, btn3 in right.
    btn2->setPosition(CocosWindow::center());
    btn1->setPosition(btn2->getPositionX() - btn2->getContentSize().width*3/2,
                      btn2->getPositionY());
    btn3->setPosition(btn2->getPositionX() + btn2->getContentSize().width * 3 / 2,
                      btn2->getPositionY());

    auto menu = Menu::create(btn1, btn2, btn3, nullptr);
    menu->setPosition(Vec2::ZERO);

    addChild(menu);
   
}

void CallFuncTestPage::onEnterState()
{
    loadUI();
}

void CallFuncTestPage::onExecuteState()
{
}

void CallFuncTestPage::onExitState()
{
    unloadUI();
}

void CallFuncTestPage::btnCallback1(cocos2d::Ref *sender)
{
    // do CallFunc.
    // 
    runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([](){}), nullptr));

}

void CallFuncTestPage::btnCallback2(cocos2d::Ref *sender)
{
    // do CallFunN
    MessageBox("call2", "CallFuncTestPage");
}

void CallFuncTestPage::btnCallback3(cocos2d::Ref *sender)
{
    // do CallFunND
    MessageBox("call3", "CallFuncTestPage");
}

void CallFuncTestPage::btnCallback4(cocos2d::Ref *sender)
{
    // do CallFunO
    MessageBox("call4", "CallFuncTestPage");
}

