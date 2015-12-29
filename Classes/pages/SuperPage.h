#ifndef CPP_DEMO_LAYER_SUPER_PAGE_H
#define CPP_DEMO_LAYER_SUPER_PAGE_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

// since V3.2, use node's own getChildByName if you need.
//#define ADD_CHILD(var_name) addChild((var_name), #var_name)
#define ADD_CHILD_WITH_NAME(parent, var_name) (parent)->addChild((var_name), (var_name)->getLocalZOrder(), #var_name)

class SuperPage : public cocos2d::Layer {
public:

    typedef cocos2d::Layer Super;

    // do init for sub pages, which will calls CCLayer::init() inside.
    bool init() override;

    // should be called in sub page onEnter().
    virtual void loadUI() { }

    // should called in sub page onExit().
    virtual void unloadUI() { removeAllChildren(); }

    // since V3.2, use node's own getChildByName if you need.

    /* template <typename T>
    T* getChild(const std::string &name);

    void addChild(cocos2d::CCNode * child, const std::string &name);
    void addChild(cocos2d::CCNode * child, int zOrder, const std::string &name);
    void addChild(cocos2d::CCNode* child, int zOrder, int tag, const std::string &name);

    void addChildRaw(cocos2d::CCNode * child);
    void addChildRaw(cocos2d::CCNode * child, int zOrder);
    void addChildRaw(cocos2d::CCNode* child, int zOrder, int tag);

private:
    // hide super's public methods. 
    virtual void addChild(cocos2d::CCNode * child) override;
    virtual void addChild(cocos2d::CCNode * child, int zOrder) override;
    virtual void addChild(cocos2d::CCNode* child, int zOrder, int tag) override;

    void bindChildWithName(cocos2d::CCNode *child, const std::string &name);
    */

protected:
    SuperPage();
    virtual ~SuperPage();

private:
    // since V3.2, use node's own getChildByName if you need.
    //typedef std::unordered_map<std::string, cocos2d::Node*> ChildMap;
    //ChildMap    childMap_;
};


// since V3.2 node has getChildByName method, so this getChild method can be 
// ignored.
//template <typename T>
//T* SuperPage::getChild(const std::string &name) {
//    auto iter = childMap_.find(name);
//    if (iter == childMap_.end()) {
//        return nullptr;
//    }
//    else {
//        return dynamic_cast<T*>(iter->second);
//    }
//}

#endif