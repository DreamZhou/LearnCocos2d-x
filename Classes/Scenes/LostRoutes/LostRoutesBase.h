#pragma once
#include "cocos2d.h"
class LostRoutesBase :
    public cocos2d::Scene
{
public:
    LostRoutesBase();
    ~LostRoutesBase();
    CREATE_FUNC(LostRoutesBase);
    virtual bool init() override;

    void menuBackCallBack(Ref * pSender);

};

