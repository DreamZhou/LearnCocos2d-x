#include "LostRoutesLoading.h"
#include "3rdparty/fmt/fmt/format.h"
USING_NS_CC;
cocos2d::Scene * LostRoutesLoading::createScene()
{
    
    return LostRoutesLoading::create();
}


bool LostRoutesLoading::init()
{
    if (!cocos2d::Scene::init())
    {
        return false;
    }

    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Vec2   origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");
    
    //add splash screen
    auto bg = TMXTiledMap::create("map/red_bg.tmx");
    bg->setPosition(origin+Vec2(visibleSize.width / 2, visibleSize.height / 2));
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(bg);

    //add a logo
    auto logo = Sprite::createWithSpriteFrameName("logo.png");
    addChild(logo);
    logo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto sprite = Sprite::createWithSpriteFrameName("loding4.png");
    addChild(sprite);
    sprite->setPosition(logo->getPosition() - Vec2(0, logo->getContentSize().height/2+ 30));

    //动画
    Animation* animation = Animation::create();
    for (size_t i = 0; i < 4; i++)
    {
        auto frameName =fmt::format("loding{}.png", i);
        CCLOG("frameName = %s", frameName.c_str());
        SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animation->addSpriteFrame(spriteFrame);
    }
    //设置两帧播放时间
    animation->setDelayPerUnit(0.5f);
    animation->setRestoreOriginalFrame(true);

    return true;
}


void LostRoutesLoading::onExit()
{
    cocos2d::Scene::onExit();
}
