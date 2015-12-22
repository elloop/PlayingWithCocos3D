#include "pages/CCBPage.h"
#include "cocosbuilder/CocosBuilder.h"
#include "cocosbuilder/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

CCBPage::CCBPage()
{

}

CCBPage::~CCBPage()
{
    clear();
}

void CCBPage::loadFromCcbi(const std::string &ccbi)
{
    // 第一步： 创建一个NodeLoaderLibrary
    auto loaderLib = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

    // 第二步: 创建CCBReader
    auto ccbReader = new CCBReader(loaderLib, this);

    // 第三步： 调用CCBReader的readNodeGraphFromFile的方法，传入ccbi名字
    auto node = ccbReader->readNodeGraphFromFile(ccbi.c_str(), this);
    ccbReader->release();

    // 解析完毕，可以使用Node了。
    if (node != NULL)
    {
        addChildRaw(node);
    }
}

bool CCBPage::onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node)
{
    if (target != this) 
    {
        return false;
    }

    std::string name(memberVariableName);

    // strong ref to node.
    node->retain();
    auto iter = nodes_.find(name);
    if (iter == nodes_.end()) 
    {
        nodes_.insert({name, node});
    }
    else
    {
        iter->second->release();
        iter->second = node;
    }

    return true;
}

bool CCBPage::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler CCBPage::onResolveCCBCCMenuItemSelectorPassSender(
    cocos2d::Ref * pTarget, const char* pSelectorName, cocos2d::Ref* sender)
{
    if (pTarget != this)
    {
        return false;
    }

    std::string actionName(pSelectorName);
    auto iter = actions_.find(sender);
    if (iter == actions_.end())
    {
        actions_.insert({ sender, actionName });
    }
    else
    {
        iter->second = actionName;
    }

    return CC_MENU_SELECTOR(CCBPage::onMenuItemEvent);
}

void CCBPage::onMenuItemEvent(cocos2d::Ref* target)
{
    auto iter = actions_.find(target);
    if (iter != actions_.end()) 
    {
        onMenuItemSelected(iter->second, target);
    }
}

void CCBPage::onMenuItemSelected(const std::string &actionName, cocos2d::Ref *target)
{
    CCLOG("warning: [override me].default onMenuItemSelected called, actionName: %s\n", actionName.c_str());
}

void CCBPage::clear()
{
    actions_.clear();
    for (auto &item : nodes_) 
    {
        item.second->release();
    }
    nodes_.clear();
}


