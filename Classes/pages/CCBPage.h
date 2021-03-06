#ifndef PLAYING_WITH_COCOS3D_PAGE_CCBPAGE_H
#define PLAYING_WITH_COCOS3D_PAGE_CCBPAGE_H

#include "cocos2d.h"
#include "cocosbuilder/CCBMemberVariableAssigner.h"
#include "cocosbuilder/CCBSelectorResolver.h"
#include "pages/SuperPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include <unordered_map>
#include <string>

class PageManager;

class CCBPage 
    : public SuperPage
    , public cocosbuilder::CCBMemberVariableAssigner
    , public cocosbuilder::CCBSelectorResolver
{
    friend PageManager;

public:

    void loadUI() override {};
    void unloadUI() override {};

    void loadFromCcbi(const std::string &ccbi);

    template <typename ChildType = cocos2d::Node>
    ChildType* getCcbiChild(const std::string &name);

    // CCBMemberVariableAssigner
    bool onAssignCCBMemberVariable( cocos2d::Ref* target, 
                                    const char* memberVariableName, 
                                    cocos2d::Node* node) override;

    bool onAssignCCBCustomProperty( cocos2d::Ref* target, 
                                    const char* memberVariableName, 
                                    const cocos2d::Value& value) override;

    // CCBSelectorResolver
    cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(
        cocos2d::Ref * pTarget, const char* pSelectorName) override
    {
        return nullptr;
    }

    cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelectorPassSender(
        cocos2d::Ref * pTarget, 
        const char* pSelectorName, 
        cocos2d::Ref* sender) override;

    cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(
        cocos2d::Ref * pTarget, const char* pSelectorName) override
    {
        return nullptr;
    }

    virtual void onMenuItemSelected(const std::string &actionName, 
                                    cocos2d::Ref *target);

    void clear();

protected:
    void onMenuItemEvent(cocos2d::Ref* target);

    CCBPage();
    virtual ~CCBPage();

private:
    typedef std::unordered_map<std::string, cocos2d::Node*> NodeMap;
    NodeMap     nodes_;

    typedef std::unordered_map<cocos2d::Ref*, std::string> ActionMap;
    ActionMap   actions_;
};

template <typename ChildType>
ChildType* CCBPage::getCcbiChild(const std::string &name)
{
    auto iter = nodes_.find(name);
    if (iter != nodes_.end()) 
    {
        return dynamic_cast<ChildType*>(iter->second);
    }
    return nullptr;
}

#endif  //PLAYING_WITH_COCOS3D_PAGE_CCBPAGE_H