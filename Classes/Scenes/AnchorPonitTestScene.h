#ifndef __ANCHORPONITTEST_SCENE_H__
#define __ANCHORPONITTEST_SCENE_H__

#include "cocos2d.h"

class AnchorPonitTestScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene ();

    virtual bool init ();

    void update(float dt) override;

    void menuCloseCallback(Ref * pSender);

    void anchorPositionCallback(cocos2d::Ref * pSender, const cocos2d::Vec2 & position);

    void setScaleCallback(cocos2d::Ref * pSender);

    void setRotationCallback(cocos2d::Ref * pSender);

    void playFanQieCallback(cocos2d::Ref * pSender);

    CREATE_FUNC(AnchorPonitTestScene);
private:
    cocos2d::Sprite * helloWorld;
    cocos2d::ProgressTimer * progress1;
};

#endif // __ANCHORPONITTEST_SCENE_H__
