#include "util/cocos_util.h"
#include "util/DrawNode3D.h"
#include <cassert>
#include <fstream>
#include <ctime>

USING_NS_CC;

void CocosUtil::markPositionWithDot(
    cocos2d::Node *parent,
    cocos2d::Vec2 pos,
    float radius /*= 10*/,
    cocos2d::Color4F color4f /*= cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f)*/)
{

    assert(parent);
    auto node = DrawNode::create();
    parent->addChild(node);
    node->setPosition(pos);
    node->drawDot(Vec2::ZERO, radius, color4f);
    CCLOG("mark pos: (%.2f, %.2f)\n", pos.x, pos.y);
}

void CocosUtil::log(const char *format, ...)
{
    const int LOG_MAX_LENGTH = 16384;
    char msg[LOG_MAX_LENGTH];
    va_list args;
    va_start(args, format);
    vsnprintf_s(msg, LOG_MAX_LENGTH, LOG_MAX_LENGTH, format, args);
    va_end(args);
    if (logStream_.is_open())
    {
        logStream_ << msg;
    }
}

bool CocosUtil::openLog()
{
    if (logStream_.is_open())
    {
        return true;
    }
    logStream_.open(logName_.c_str(), std::ofstream::app);
    return logStream_.is_open();
}

void CocosUtil::markCorners(cocos2d::Node *parent, float radius/*=5*/)
{
    assert(parent);
    Size size = parent->getContentSize();
    markPositionWithDot(parent, Vec2(0, 0), radius, randomC4f());
    markPositionWithDot(parent, Vec2(0, size.height), radius, randomC4f());
    markPositionWithDot(parent, Vec2(size.width, size.height), radius, randomC4f());
    markPositionWithDot(parent, Vec2(size.width, 0), radius, randomC4f());
}

cocos2d::Color4F CocosUtil::randomC4f(float alpha/* = 1.0*/)
{
    //srand(time(0));
    Color4F c4f;
    c4f.r = CCRANDOM_0_1();
    c4f.g = CCRANDOM_0_1();
    c4f.b = CCRANDOM_0_1();
    c4f.a = alpha;
    return c4f;
}

cocos2d::Color4B CocosUtil::randomC4b(unsigned char alpha /*= 255*/)
{
    //srand(time(0));
    Color4B c4b;
    c4b.r = rand() % 255;
    c4b.g = rand() % 255;
    c4b.b = rand() % 255;
    c4b.a = alpha;
    return c4b;
}

void CocosUtil::closeLog()
{
    if (logStream_.is_open())
    {
        logStream_.close();
    }
}
std::ofstream CocosUtil::logStream_;

std::string CocosUtil::logName_("game.log");

DrawNode3D* CocosUtil::drawGrid(Vec3 center, unsigned int lineCount, unsigned int gap)
{
    float length = (lineCount - 1) * gap;

    float zBegin = center.z - length / 2;
    float xBegin = center.x - length / 2;

    auto drawNode = DrawNode3D::create();

    for (unsigned i = 0; i < lineCount; ++i)
    {
        //draw x.
        drawNode->drawLine(
            Vec3(center.x - length / 2, 0.f, zBegin + i * gap),
            Vec3(center.x + length / 2, 0.f, zBegin + i * gap),
            Color4F(1, 0, 0, 1));

        //draw z.
        drawNode->drawLine(
            Vec3(xBegin + i * gap, 0.f, center.z - length / 2),
            Vec3(xBegin + i * gap, 0.f, center.z + length / 2),
            Color4F(0, 0, 1, 1));
    }

    drawNode->drawLine(
        Vec3(center.x, -length / 2, center.z),
        Vec3(center.x, length / 2, center.z),
        Color4F(0, 1, 0, 1));

    return drawNode;
}
