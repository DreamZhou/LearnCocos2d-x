#include "playAnimation.h"
#include <vector>
#include "3rd\fmt\fmt\format.h"


playAnimation::playAnimation()
{
}


playAnimation::~playAnimation()
{
}

void playAnimation::playAnimationFanqie(cocos2d::Node * node, cocos2d::Vec2 Src, cocos2d::Vec2 Des)
{
        auto frameCache = cocos2d::SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile("animation/fanqie_effect.plist");
        auto sprite1 = cocos2d::Sprite::createWithSpriteFrameName("fanqie.png");
        sprite1->setPosition(Src);
        node->addChild(sprite1);
        cocos2d::Vector<cocos2d::SpriteFrame*> mSprite;
        for (int i = 1; i < 13; i++)
        {
                auto frame = frameCache->getSpriteFrameByName(fmt::format("fanqie_{}.png",i));
                mSprite.pushBack(frame);
        }
    
        auto mAnimation2 = cocos2d::Animation::createWithSpriteFrames(mSprite, 0.15f);
    
        mAnimation2->setLoops(1);//
    
        mAnimation2->setRestoreOriginalFrame(true);
    
        auto mAnimate2 = cocos2d::Animate::create(mAnimation2);
    
        //sprite1->runAction(mAnimate2);

        
        cocos2d::ActionInterval* moveto = cocos2d::MoveTo::create(0.5f, Des);
    
        cocos2d::ActionInterval * fadeout1 = cocos2d::FadeOut::create(0.0f);
        
        auto action1 = cocos2d::Sequence::create(moveto, mAnimate2, fadeout1, nullptr);
  
        sprite1->runAction(action1);
}
