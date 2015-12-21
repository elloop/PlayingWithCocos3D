#include "pages/TouchTestPage.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool touchTestPageRegistered = PageManager::getInstance()->registerPage(
    "TouchTestPage", TouchTestPage::create());

void TouchTestPage::loadUI()
{
    auto layerListenter = EventListenerTouchOneByOne::create();
    layerListenter->onTouchBegan = CC_CALLBACK_2(TouchTestPage::onTouchBegan, this);
    layerListenter->onTouchMoved = CC_CALLBACK_2(TouchTestPage::onTouchMoved, this);
    layerListenter->onTouchEnded = CC_CALLBACK_2(TouchTestPage::onTouchEnded, this);
    layerListenter->onTouchCancelled = CC_CALLBACK_2(TouchTestPage::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(layerListenter, this);
    //setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    //setTouchEnabled(true);

    //setTouchMode(kTouchesOneByOne);

    auto winSize = CocosWindow::size();
    auto origin = CocosWindow::origin();

    Size colorLayerSize(winSize.width / 4, winSize.height / 4);
    auto colorLayer = LayerColor::create(CocosUtil::randomC4b());
    colorLayer->setContentSize(colorLayerSize);
    colorLayer->setPosition(CocosWindow::center() -
                            Vec2(colorLayerSize.width / 2, colorLayerSize.height / 2));
    ADD_CHILD(colorLayer);

    // from left to right, add 3 dogs for touching.
    for ( int i = 1; i < 4; ++i )
    {
        auto dog = Dog::create("DemoIcon/dog_160.png");
        CCAssert(dog, "");
        dog->setTag(i);
        auto dogSize = dog->getContentSize();
        dog->setPosition(origin +
                         Vec2(dogSize.width / 2 + ( i - 1 ) * dogSize.width, dogSize.height / 2));

        CocosUtil::markCorners(dog);
        // dog1, dog2, dog3.
        addChild(dog, "dog" + StringUtil::toString(i));
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(Dog::onTouchBegan, dog);
        listener->onTouchMoved = CC_CALLBACK_2(Dog::onTouchMoved, dog);
        listener->onTouchEnded = CC_CALLBACK_2(Dog::onTouchEnded, dog);
        listener->onTouchCancelled = CC_CALLBACK_2(Dog::onTouchCancelled, dog);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, dog);
    }

    // test Custom Menu
    auto menuItemImage1 = MenuItemImage::create(
        "DemoIcon/home_small.png", "DemoIcon/home_small.png",
        CC_CALLBACK_1(TouchTestPage::menuCallback, this));

    auto menuItemImage2 = MenuItemImage::create(
        "DemoIcon/home_small.png", "DemoIcon/home_small.png",
        CC_CALLBACK_1(TouchTestPage::menuCallback, this));

    menuItemImage2->setPosition(Vec2(menuItemImage1->getContentSize().width, 
        0));

    //auto label = LabelTTF::create("hello", "arial.ttf", 20);
    auto label = Label::createWithSystemFont("hello", "arial.ttf", 20);
    auto menuItemLabel = MenuItemLabel::create(label);
    menuItemLabel->setPosition(Vec2(menuItemImage2->getPositionX() + menuItemImage1->getContentSize().width, 0));

    //using elloop::Menu;
    elloop::Menu *menu = elloop::Menu::create(menuItemImage1, menuItemImage2, menuItemLabel, nullptr);
    ADD_CHILD(menu);
}

void TouchTestPage::unloadUI()
{
    removeAllChildren();
}

void TouchTestPage::onEnterState()
{
    loadUI();
}

void TouchTestPage::onExecuteState()
{}

void TouchTestPage::onExitState()
{
    unloadUI();
}

TouchTestPage::TouchTestPage()
: isTouchingColorLayer_(false)
, touchBeginPoint_(Vec2::ZERO)
{}

TouchTestPage::~TouchTestPage()
{}

bool TouchTestPage::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto pos = pTouch->getLocation();
    CCLOG("(%.2f, %.2f)", pos.x, pos.y);
    auto colorLayer = getChild<LayerColor>("colorLayer");
    if ( colorLayer )
    {
        auto posInLayer = colorLayer->convertToNodeSpace(pos) * colorLayer->getScale();
        CCLOG("in color layer: (%.2f, %.2f)", posInLayer.x, posInLayer.y);

        // judge if click in the colorLayer.
        Rect rect;
        rect.origin = Vec2::ZERO;
        rect.size = colorLayer->getContentSize();
        if ( rect.containsPoint(posInLayer) )
        {
            touchBeginPoint_ = pTouch->getLocation();
            isTouchingColorLayer_ = true;
            CCLOG("touch swallowed by color layer");
            return true;
        }
    }
    return false;
}

void TouchTestPage::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    if ( isTouchingColorLayer_ )
    {
        auto colorLayer = getChild<LayerColor>("colorLayer");
        if ( colorLayer )
        {
            auto posDiff = pTouch->getLocation() - pTouch->getPreviousLocation();
            colorLayer->setPosition(colorLayer->getPosition() + posDiff);
        }
    }
}

void TouchTestPage::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    isTouchingColorLayer_ = false;
}

void TouchTestPage::onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    isTouchingColorLayer_ = false;
}

void TouchTestPage::menuCallback(cocos2d::Ref * target)
{
    //CCMessageBox("HouseMenuClcked", "TouchTestPage");
    //ScrollMessageBox::
}

//----------------------------------- Dog Imp ---------------------------------
Dog::~Dog()
{}

Dog::Dog()
{}

Dog* Dog::create(const char *name)
{
    auto self = new Dog();
    if ( self && self->initWithString(name) )
    {
        self->autorelease();
        return self;
    }
    CC_SAFE_DELETE(self);
    return nullptr;
}

bool Dog::initWithString(const char *name)
{
    if ( NodeGrid::init() )
    {
        sprite_ = Sprite::create(name);
        addChild(sprite_);
        setAnchorPoint(Vec2(0.5, 0.5));
        setContentSize(sprite_->getContentSize());
        return true;
    }
    return false;
}

cocos2d::Rect Dog::rect() const
{
    Rect rect;
    rect.origin = Vec2::ZERO;
    rect.size = getContentSize();
    return rect;
}

bool Dog::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto pos = pTouch->getLocation();
    CCLOG("(%.2f, %.2f)", pos.x, pos.y);
    CCLOG("in dog%d: (%.2f, %.2f)\n", getTag(),
          convertToNodeSpace(pos).x * getScaleX(), getScaleY()*convertToNodeSpace(pos).y);
    if ( rect().containsPoint(convertToNodeSpace(pos)) )
    {
        auto act = CCRotateBy::create(0.5, 90);
        runAction(act);
        CCLOG("touch swallowed by dog%d\n", getTag());
        return true;
    }
    else
    {
        // not touch in th dog, just shake.
        auto shake = CCShaky3D::create(0.5, CCSize(20, 20), 5, false);
        runAction(shake);
    }
    return false;
}

void Dog::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{}

void Dog::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{}

void Dog::onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{}


