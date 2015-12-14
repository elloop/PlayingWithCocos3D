#ifndef CPP_DEMO_LOGIC_DIRECTOR_H
#define CPP_DEMO_LOGIC_DIRECTOR_H

#include "cocos2d.h"
#include "util/StateMachine.h"
#include "cocos_include.h"

class LogicDirector : cocos2d::Ref, public Singleton<LogicDirector>
{
    friend Singleton<LogicDirector>;

public:
    void begin();
    void destroyInstance() override;
    void update(float dt);

protected:
    LogicDirector();
    ~LogicDirector();
    void init();
private:
    cocos2d::Scene                  *mainScene_;
    StateMachine<LogicDirector>     *stateMachine_;
};

void globalClearFunction();

#endif