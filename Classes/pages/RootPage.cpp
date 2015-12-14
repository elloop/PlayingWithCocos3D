#include "pages/RootPage.h"
#include "PageManager.h"
#include "message/Message.h"
#include "message/MessageCenter.h"
#include "pages/MainPage.h"
#include "customs/Menu.h"
#include "GUI/CCScrollView/CCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

RootPage::RootPage() 
: backLayer_(nullptr)
, middleLayer_(nullptr)
, frontLayer_(nullptr)
, stateMachine_(nullptr)
{}

RootPage::~RootPage()
{
    if ( stateMachine_ && stateMachine_->currentState() )
    {
        stateMachine_->currentState()->onExitState();
    }
    CC_SAFE_DELETE(stateMachine_);

    CC_SAFE_RELEASE_NULL(backLayer_);
    CC_SAFE_RELEASE_NULL(middleLayer_);
    CC_SAFE_RELEASE_NULL(frontLayer_);
}

void RootPage::loadUI()
{
    addMenuButtons();

    backLayer_ = Layer::create();
    backLayer_->retain();
    addChildRaw(backLayer_);

    middleLayer_ = Layer::create();
    middleLayer_->retain();
    addChildRaw(middleLayer_, 1);

    frontLayer_ = Layer::create();
    frontLayer_->retain();
    frontLayer_->setContentSize(Size(200, 200));
    addChildRaw(frontLayer_, 2);

}

void RootPage::onEnterState()
{
    loadUI();
    stateMachine_ = new StateMachine<RootPage>();
}

void RootPage::onExecuteState()
{
    if ( stateMachine_ )
    {
        stateMachine_->update();
    }
}

void RootPage::onExitState()
{
    unloadUI();
}

void RootPage::addMenuButtons()
{
    auto winSize = CocosWindow::size();
    auto origin = CocosWindow::origin();

    MenuItemImage *quitBtn = MenuItemImage::create(
        "CloseNormal.png", "CloseSelected.png",
        this,
        CC_MENU_SELECTOR(RootPage::quitGame));
    quitBtn->ignoreAnchorPointForPosition(true);
    auto btnSize = quitBtn->getContentSize();
    quitBtn->setPosition(origin + Point(winSize.width - btnSize.width,
        winSize.height - btnSize.height));

    MenuItemImage *homeBtn = MenuItemImage::create(
        "DemoIcon/home_small.png", "DemoIcon/home_small.png",
        this,
        CC_MENU_SELECTOR(RootPage::goHome));
    homeBtn->ignoreAnchorPointForPosition(true);
    btnSize = homeBtn->getContentSize();
    homeBtn->setPosition(origin + Point(0, winSize.height - btnSize.height));

    //using elloop::Menu;
    elloop::Menu *menu = elloop::Menu::create(quitBtn, homeBtn, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChildRaw(menu, 3);
}

void RootPage::quitGame(Ref *sender)
{
    CCDirector::sharedDirector()->end();
}

void RootPage::goHome(Ref *sender)
{
    MsgChangePage msg("MainPage");
    MessageCenter::getInstance()->sendMessage(&msg);
}

RootPage* rootPage()
{
    static RootPage *rootPage = RootPage::create();
    return rootPage;
}
