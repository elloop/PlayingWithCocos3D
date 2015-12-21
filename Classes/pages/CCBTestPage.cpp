#include "pages/CCBTestPage.h"
#include "PageManager.h"
USING_NS_CC;

bool ccb_test_page_created = PageManager::getInstance()->registerPage(
    "CCBTestPage", CCBTestPage::create());

CCBTestPage::CCBTestPage()
{
}

CCBTestPage::~CCBTestPage()
{
}

void CCBTestPage::onEnterState()
{
    loadUI();
}

void CCBTestPage::onExecuteState()
{
}

void CCBTestPage::onExitState()
{
    unloadUI();
}

void CCBTestPage::loadUI()
{
    loadFromCcbi("ccbi/baozao.ccbi");
}

void CCBTestPage::unloadUI()
{
    removeAllChildren();
}

void CCBTestPage::onMenuItemSelected(const std::string &actionName, cocos2d::Ref *target)
{
    if ("onClick" == actionName) 
    {
        auto label = getChild<Label>("mLabel");
        if (label) 
        {
            label->runAction(RotateBy::create(0.5, 360));
        }
    }
}
