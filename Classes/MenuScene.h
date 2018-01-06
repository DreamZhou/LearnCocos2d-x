#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeSceneCallback(Ref * pSender);
    

};

#endif // __MENU_SCENE_H__
