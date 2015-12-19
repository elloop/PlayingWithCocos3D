#include "CocosWindow.h"
USING_NS_CC;

Vec2 CocosWindow::center() {
    return origin() + Vec2(size().width/2, size().height/2);
}

Size CocosWindow::size() {
    return CCDirector::getInstance()->getVisibleSize();
}

Vec2 CocosWindow::origin() {
    return CCDirector::getInstance()->getVisibleOrigin();
}
