#pragma once
#include "cocos2d.h"
class LostRoutesMenu :
    public cocos2d::Scene
{
public:
    LostRoutesMenu();
    ~LostRoutesMenu();
    CREATE_FUNC(LostRoutesMenu);
    static  cocos2d::Scene* createScene();
    virtual bool init() override;
};

