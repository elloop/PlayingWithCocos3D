#ifndef TEST_COCOS_UTIL_H
#define TEST_COCOS_UTIL_H
#include "cocos2d.h"
#include "util/DrawNode3D.h"
#include <string>

class CocosUtil {
public:
    static void markPositionWithDot(
        cocos2d::Node   *parent,
        cocos2d::Vec2   pos,
        float radius = 10,
        cocos2d::Color4F color4f = cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f));

    static bool openLog();
    static void closeLog();

    // mark four corners for a rectangle shape parent.
    static void markCorners(cocos2d::Node *parent, float radius = 5);
    static cocos2d::Color4F randomC4f(float alpah = 1.0);
    static cocos2d::Color4B randomC4b(unsigned char alpha = 255);

    static cocos2d::DrawNode3D* drawGrid(cocos2d::Vec3 center, unsigned int lineCount, unsigned int gap);

    static void log(const char *format, ...);
    static void log() {}

private:
    static std::string      logName_;
    static std::ofstream    logStream_;    
   
};

#endif