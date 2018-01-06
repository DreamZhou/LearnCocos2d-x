#ifndef __LOST_ROUTES_LOADING_H
#define __LOST_ROUTES_LOADING_H

#include "cocos2d.h"


class LostRoutesLoading :
    public cocos2d::Scene
{
public:
    virtual bool init() override;
    CREATE_FUNC(LostRoutesLoading);
    static cocos2d::Scene* createScene();
    virtual void onExit();

private:

};

#endif // !__LOST_ROUTES_LOADING_H
