#include "pages/MainPage.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "data_models/TestDataCenter.h"
#include "message/Message.h"
#include "message/MessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;

MainPage::MainPage()
{
}

MainPage::~MainPage()
{
}

void MainPage::loadUI()
{
    float height(0);

    // 单元格宽度、高度
    auto    winSize     = CocosWindow::size();
    float   cellHeight  = winSize.height / 3;
    float   cellWidth   = winSize.width;

    // scrollview的container
    Node *container = Node::create();
    int tag(0);
    
    int testCount = TestDataCenter::getInstance()->testDataCount();
    for (int i=0; i<testCount; ++i) 
    {
        auto item = TestItem::create(i, cellWidth, cellHeight);
        item->setPosition(Point(0, height));
        container->addChild(item);
        height += cellHeight;
    }
    container->setContentSize(Size(cellWidth, height));

    auto scroll = ScrollView::create();
    scroll->setContainer(container);
    scroll->setPosition(CocosWindow::center() - Point(winSize / 2));
    scroll->setViewSize(winSize);
    scroll->setContentOffset(Point(0, -height + winSize.height));
    CocosUtil::markCorners(scroll);
    ADD_CHILD_WITH_NAME(this, scroll);
}

void MainPage::onEnterState()
{
    loadUI();
    MsgChangeBackground msg("DemoIcon/grass.jpg");
    MessageCenter::getInstance()->sendMessage(&msg);
    MessageCenter::getInstance()->registerHanlder(
        MessageType::kMessageTypeChangePage, this);
}

void MainPage::onExecuteState()
{

}

void MainPage::onExitState()
{
    unloadUI();
}

void MainPage::onMessageReceived(const Message *msg)
{
    int i;
    i = 1;
}

TestItem * TestItem::create(int id, float width, float height)
{
    TestItem *self = new TestItem(id);
    if (self && self->initWithSize(width, height))
    {
        // notice: don't forget autorelease again.
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool TestItem::initWithSize(float width, float height)
{
    if (!Node::init()) return false;

    auto data = TestDataCenter::getInstance()->getTestDataItemByIndex(itemId_);
    if (data) 
    {
        float sizeX(0), sizeY(0);

        Sprite *icon = Sprite::create(data->icon_.c_str());
        CCAssert(icon, "");
        icon->setAnchorPoint(Vec2::ZERO);
        auto oriSize = icon->getContentSize();
        icon->setScaleX(width / 3 / oriSize.width);
        icon->setScaleY(height / oriSize.height);
        icon->setPosition(Vec2(0, 0));
        CocosUtil::markCorners(icon, 3);
        addChild(icon);

        //LabelTTF *label = LabelTTF::create(data->description_.c_str(), "arial.ttf", 30);
        auto label = Label::createWithSystemFont(data->description_.c_str(), "arial.ttf", 30);
        CCAssert(label, "");
        auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestItem::onItemSelected, this));
        auto labelSize = labelItem->getContentSize();
        labelItem->setPosition(Vec2::ZERO);
        labelItem->setTag(itemId_);
        auto menu = Menu::create(labelItem, nullptr);
        menu->setPosition(Vec2(width * 2 / 3, height / 2));
        addChild(menu);
        CocosUtil::markCorners(label, 2);

        setContentSize(Size(width, height));
        return true;
    }
    return false;
}

void TestItem::onItemSelected(cocos2d::Ref *target)
{
    auto t = dynamic_cast<MenuItemLabel*>(target);
    CCAssert(t, "");
    auto data = TestDataCenter::getInstance()->getTestDataItemByIndex(t->getTag());
    MsgChangePage msg(data->pageName_);
    MessageCenter::getInstance()->sendMessage(&msg);
}

