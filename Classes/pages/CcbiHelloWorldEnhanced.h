#ifndef PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_ENHANCED_H
#define PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_ENHANCED_H

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"
#include "cocosbuilder/CCBMemberVariableAssigner.h"
#include "cocosbuilder/CCBSelectorResolver.h"

class CcbiHelloWorldEnhanced 
    : public cocos2d::Node
    , public cocosbuilder::CCBMemberVariableAssigner
    , public cocosbuilder::CCBSelectorResolver
{
public:
    CREATE_FUNC(CcbiHelloWorldEnhanced);

    bool init() override
    {
        using cocosbuilder::NodeLoaderLibrary;
        using cocosbuilder::CCBReader;

        // 第一步： 创建一个NodeLoaderLibrary
        auto loaderLib = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

        // 第二步: 创建CCBReader
        auto ccbReader = new CCBReader(loaderLib);

        // 第三步： 调用CCBReader的readNodeGraphFromFile的方法，传入ccbi名字
        auto node = ccbReader->readNodeGraphFromFile("ccbi/hello.ccbi", this);
        ccbReader->release();

        // 解析完毕，可以使用Node了。
        if (node)
        {
            addChild(node);
        }
        return true;
    }

    // CCBMemberVariableAssigner
    bool onAssignCCBMemberVariable( cocos2d::Ref* target,
                                    const char* memberVariableName,
                                    cocos2d::Node* node) override
    {
        std::string name(memberVariableName);
        if (name == "mLabel") 
        {
            node->retain();
            label_ = dynamic_cast<cocos2d::Label*>(node);
            if (!label_) 
            {
                node->release();
            }
            return true;
        }
        else if (name == "mBtn") 
        {
            node->retain();
            menuItemImage_ = dynamic_cast<cocos2d::MenuItemImage*>(node);
            if (!menuItemImage_)
            {
                node->release();
            }
            return true;
        }

        return false;
    }

    // CCBSelectorResolver
    cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(
        cocos2d::Ref * pTarget, const char* pSelectorName) override
    {
        if (std::string(pSelectorName) == "onClick") 
        {
            return CC_MENU_SELECTOR(CcbiHelloWorldEnhanced::onClicked);
        }
        return nullptr;
    }

    cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(
        cocos2d::Ref * pTarget, const char* pSelectorName) override
    {
        return nullptr;
    }

    virtual void onClicked(cocos2d::Ref *sender)
    {
        CCAssert(menuItemImage_ == sender, "sender should be the item binded");

        if (label_) 
        {
            label_->runAction(cocos2d::RotateBy::create(0.5, 360));
        }
    }
    
    CcbiHelloWorldEnhanced() : label_(nullptr), menuItemImage_(nullptr) {}
    ~CcbiHelloWorldEnhanced() 
    {
        CC_SAFE_RELEASE(label_);
        CC_SAFE_RELEASE(menuItemImage_);
    }

    cocos2d::Label          *label_;
    cocos2d::MenuItemImage  *menuItemImage_;
};

#endif  //PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_ENHANCED_H