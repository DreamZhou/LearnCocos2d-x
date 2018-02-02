#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Base/BaseScene.h"

class MenuScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    virtual bool init() override;
    
    // a selector callback
    void menuBackCallback(cocos2d::Ref* pSender) override;
    void menuChangeSceneCallback(Ref * pSender, size_t index);
    

};

#endif // __MENU_SCENE_H__
