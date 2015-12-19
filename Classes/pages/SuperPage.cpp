#include "pages/SuperPage.h"
#include "cocos_include.h"

USING_NS_CC;

void SuperPage::bindChildWithName(Node *child, const std::string &name)
{
    auto iter = childMap_.find(name);
    if (iter == childMap_.end())
    {
        childMap_.insert({ name, child });
    }
    else
    {
        CocosUtil::log("warning: repeated child name : %s\n", name.c_str());
        iter->second = child;
    }
}

void SuperPage::addChild(Node * child, const std::string &name)
{
    addChild(child, child->getLocalZOrder(), child->getTag());
    bindChildWithName(child, name);
}

void SuperPage::addChild(Node * child, int zOrder, const std::string &name)
{
    addChild(child, zOrder, child->getTag());
    bindChildWithName(child, name);
}

void SuperPage::addChild(Node* child, int zOrder, int tag, const std::string &name)
{
    addChild(child, zOrder, tag);
    bindChildWithName(child, name);
}

void SuperPage::addChildRaw(Node * child)
{
    addChild(child, child->getLocalZOrder(), child->getTag());
}

void SuperPage::addChildRaw(Node * child, int zOrder)
{
    addChild(child, zOrder, child->getTag());
}

void SuperPage::addChildRaw(Node* child, int zOrder, int tag)
{
    addChild(child, zOrder, tag);
}

//----------------------------------- parent method -------------------------------
void SuperPage::addChild(Node * child)
{
    Node::addChild(child, child->getLocalZOrder(), child->getTag());
}

void SuperPage::addChild(Node * child, int zOrder)
{
    Node::addChild(child, zOrder, child->getTag());
}

void SuperPage::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
}

SuperPage::~SuperPage()
{
    childMap_.clear();
}

SuperPage::SuperPage()
{

}

void SuperPage::loadUI()
{

}

void SuperPage::unloadUI()
{

}

bool SuperPage::init()
{
    return Super::init();
}


