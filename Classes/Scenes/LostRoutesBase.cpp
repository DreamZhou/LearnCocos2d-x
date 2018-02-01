#include "LostRoutes/LostRoutesBase.h"

USING_NS_CC;

LostRoutesBase::LostRoutesBase()
{
}


LostRoutesBase::~LostRoutesBase()
{
}

bool LostRoutesBase::init()
{
    if (!cocos2d::Scene::init()) 
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //背景图
    auto bg = TMXTiledMap::create("map/red_bg.tmx");
    addChild(bg);
    
    //眼睛精灵
    auto glassesSprite = Sprite::createWithSpriteFrameName("setting.glasses.png");
    glassesSprite->setPosition(Vec2(visibleSize.width - glassesSprite->getContentSize().width / 2, 160));
    addChild(glassesSprite);
    
    //OK菜单
    auto okNormal = Sprite::createWithSpriteFrameName("setting.button.ok.png");
    auto okSelected = Sprite::createWithSpriteFrameName("setting.button.ok-on.png");

    auto okMenuItem = MenuItemSprite::create(okNormal, okSelected,
        CC_CALLBACK_1(LostRoutesBase::menuBackCallBack,this));
    auto mu = Menu::create(okMenuItem);
    mu->setPosition(Vec2(visibleSize.width - mu->getContentSize().width / 2 + 60, 60));
    addChild(mu);

	return true;
}

void LostRoutesBase::menuBackCallBack(Ref* pSender) 
{
    Director::getInstance()->popScene();
}