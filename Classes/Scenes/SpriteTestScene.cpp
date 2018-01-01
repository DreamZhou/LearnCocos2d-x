#include "SpriteTestScene.h"

USING_NS_CC;

Scene* SpriteTest::createScene()
{
    return SpriteTest::create();
}



// on "init" you need to initialize your instance
bool SpriteTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//添加背景   --指定图片创建精灵
	auto background = Sprite::create("spriteTest/background.png");
	//background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(background, 0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto backItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SpriteTest::menuBackCallback, this));

    float x = origin.x + visibleSize.width - backItem->getContentSize().width/2;
    float y = origin.y + backItem->getContentSize().height/2;
	backItem->setPosition(Vec2(x,y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
	//指定图片和裁剪的矩形区域来创建精灵

	auto * tree1 = Sprite::create("spriteTest/tree1.png", Rect(604, 38, 302, 295));
	tree1->setPosition(Vec2(200, 300));
	this->addChild(tree1, 2);
	
	// 创建空精灵 setTexture
	Texture2D * cache = Director::getInstance()->getTextureCache()->addImage("spriteTest/tree1.png");
	auto tree2 = Sprite::create();
	tree2->setTexture(cache);
	tree2->setTextureRect(Rect(73, 72,182,270));
	tree2->setPosition(Vec2(500, 200));
	this->addChild(tree2, 3);

	//通过纹理创建精灵
	auto tree3 = Sprite::createWithTexture(cache, Rect(270, 330, 370, 160));
	tree3->setPosition(Vec2(700, 200));
	this->addChild(tree3);

    return true;
}


void SpriteTest::menuBackCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
	Director::getInstance()->popScene();
}
