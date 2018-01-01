#ifndef __SPRITETEST_SCENE_H__
#define __SPRITETEST_SCENE_H__

#include "cocos2d.h"

class SpriteTest : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuBackCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SpriteTest);
};

#endif // __SPRITETEST_SCENE_H__
