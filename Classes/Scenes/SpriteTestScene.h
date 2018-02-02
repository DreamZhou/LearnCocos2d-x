#ifndef __SPRITETEST_SCENE_H__
#define __SPRITETEST_SCENE_H__

#include "Base/BaseScene.h"

class SpriteTest : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually

    virtual bool init() override;
    virtual void onExit() override;
	CREATE_FUNC(SpriteTest);
public:
	cocos2d::Sprite* getBGNode() override;
};

#endif // __SPRITETEST_SCENE_H__
