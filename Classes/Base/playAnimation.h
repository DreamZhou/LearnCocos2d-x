#pragma once
#include "cocos2d.h"

class playAnimation
{
public:
    playAnimation();
    ~playAnimation();

    static void  playAnimationFanqie(cocos2d::Node* node, cocos2d::Vec2 Src, cocos2d::Vec2 Des);
};

