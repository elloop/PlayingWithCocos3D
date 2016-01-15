#include "pages/CameraTest.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
USING_NS_CC;

bool CallFuncTestPage_created = PageManager::getInstance()->registerPage(
    "CallFuncTestPage", CameraTest::create());

CameraTest::CameraTest()
{

}

CameraTest::~CameraTest()
{

}

void CameraTest::loadUI()
{

    // 3D sprites.
    auto s1 = Sprite3D::create("3d/girl.c3b");
    s1->setPosition3D(Vec3(200, 0, 300));
    ADD_CHILD_WITH_NAME(this, s1);

    auto s2 = Sprite3D::create("3d/girl.c3b");
    s1->setPosition3D(Vec3(400, 0, -20));
    ADD_CHILD_WITH_NAME(this, s1);

    auto s3 = Sprite3D::create("3d/girl.c3b");
    s1->setPosition3D(Vec3(600, 0, 300));
    ADD_CHILD_WITH_NAME(this, s1);

    // add three btns.
    auto btn1 = MenuItemImage::create(
        "DemoIcon/home_small.png", 
        "DemoIcon/home_small.png", 
        CC_CALLBACK_1(CameraTest::btnCallback1, this));

    auto btn2 = MenuItemImage::create(
        "DemoIcon/home_small.png",
        "DemoIcon/home_small.png",
        CC_CALLBACK_1(CameraTest::btnCallback2, this));

    auto btn3 = MenuItemImage::create(
        "DemoIcon/home_small.png",
        "DemoIcon/home_small.png",
        CC_CALLBACK_1(CameraTest::btnCallback3, this));

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

void CameraTest::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);

    loadUI();
    auto noparamCallback = CallFunc::create(
        CC_CALLBACK_0(CameraTest::noparam, this));

    runAction(Sequence::create(DelayTime::create(1.0), 
        noparamCallback, nullptr));
}

void CameraTest::onExecuteState()
{
}

void CameraTest::onExitState()
{
    unloadUI();
}

void CameraTest::noparam()
{
    MessageBox("noparam called", "callfunc test");
}

void CameraTest::btnCallback1(cocos2d::Ref *sender)
{
    // do CallFunc.
    MessageBox("call1", "CallFuncTestPage");
}

void CameraTest::btnCallback2(cocos2d::Ref *sender)
{
    // do CallFunN
    MessageBox("call2", "CallFuncTestPage");
}

void CameraTest::btnCallback3(cocos2d::Ref *sender)
{
    // do CallFunND
    MessageBox("call3", "CallFuncTestPage");
}

void CameraTest::btnCallback4(cocos2d::Ref *sender)
{
    // do CallFunO
    MessageBox("call4", "CallFuncTestPage");
}

