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
	auto backItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LostRoutesLoading::menuBackCallback, this));

	float x = origin.x + visibleSize.width - backItem->getContentSize().width / 2;
	float y = origin.y + backItem->getContentSize().height / 2;
	backItem->setPosition(Vec2(x, y));

	// create menu, it's an autorelease object
	auto menu = Menu::create(backItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

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
    for (size_t i = 1; i <= 4; i++)
    {
        auto frameName =fmt::format("loding{}.png", i);
        CCLOG("frameName = %s", frameName.c_str());
        SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animation->addSpriteFrame(spriteFrame);
    }
    //设置两帧播放时间
    animation->setDelayPerUnit(0.5f);
    animation->setRestoreOriginalFrame(true);

	Animate * action = Animate::create(animation);
	sprite->runAction(RepeatForever::create(action));

	m_nNumberOfLoaded = 0;
	Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
		CC_CALLBACK_1(LostRoutesLoading::loadingTextureCallBack, this, 0));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/setting_texture.png",
		CC_CALLBACK_1(LostRoutesLoading::loadingTextureCallBack, this, 1));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
		CC_CALLBACK_1(LostRoutesLoading::loadingTextureCallBack, this, 2));

    return true;
}

void LostRoutesLoading::menuBackCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->popScene();
}
void LostRoutesLoading::loadingTextureCallBack(cocos2d::Texture2D * texture,int numberOfLoaded) 
{
	++m_nNumberOfLoaded;
	switch (numberOfLoaded)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist", texture);
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/setting_texture.plist", texture);
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist", texture);
		break;
	default:
		CCASSERT(false, "shouldn't be here!");
		break;

	}
	CCLOG(fmt::format("loading {} done", m_nNumberOfLoaded).c_str());
}
void LostRoutesLoading::onExit()
{
    cocos2d::Scene::onExit();
}
