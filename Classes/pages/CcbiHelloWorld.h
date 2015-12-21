#ifndef PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_H
#define PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_H

#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

class CcbiHelloWorld : public cocos2d::Node
{
public:
    CREATE_FUNC(CcbiHelloWorld);
    bool init() override
    {
        using cocosbuilder::NodeLoaderLibrary;
        using cocosbuilder::CCBReader;

        // 第一步： 创建一个NodeLoaderLibrary
        auto loaderLib = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

        // 第二步: 创建CCBReader
        auto ccbReader = new CCBReader(loaderLib);

        // 第三步： 调用CCBReader的readNodeGraphFromFile的方法，传入ccbi名字
        auto node = ccbReader->readNodeGraphFromFile("ccbi/baozao.ccbi", this);
        ccbReader->release();

        // 解析完毕，可以使用Node了。
        if ( node )
        {
            addChild(node);
        }
        return true;
    }
};

#endif  //PLAYING_WITH_COCOS3D_PAGE_CCB_HELLOWORLD_H