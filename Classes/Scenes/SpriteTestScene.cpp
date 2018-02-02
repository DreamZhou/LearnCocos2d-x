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
    if ( !BaseScene::init() )
    {
        return false;
    }

	//指定图片和裁剪的矩形区域来创建精灵
    //Rect 坐标原点在 左上角 x轴向右，y轴向下
	auto * tree1 = Sprite::create("spriteTest/tree1.png", Rect(604, 38, 402, 295));
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
	auto tree3 = Sprite::createWithTexture(cache, Rect(285, 165, 100, 165));
	tree3->setPosition(Vec2(700, 200));
	this->addChild(tree3);

    /*
     * 缓存有 纹理缓存（TextureCache）、精灵帧缓存（SpriteFrameCache）、动画缓存（AnimationCache）
     */

    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("spriteTest/SpirteSheet.plist");

    auto mountain1 = Sprite::createWithSpriteFrameName("mountain1.png");
    mountain1->setAnchorPoint(Vec2::ZERO);
    mountain1->setPosition(Vec2(0, 80));
    addChild(mountain1, 0);

    SpriteFrame * heroSpriteFrame = frameCache->getSpriteFrameByName("hero1.png");
    Sprite * hero1 = Sprite::createWithSpriteFrame(heroSpriteFrame);
    hero1->setPosition(Vec2(800, 200));
    addChild(hero1, 4);

    return true;
}


void SpriteTest::onExit() 
{
    /*
     * 移除精灵帧 缓存函数：
     * 1. 指定具体的精灵帧移除
     *  void removeSpriteFrameByName(const std::string & Name);
     * 2. 移除精灵缓存
     *  void removeSpriteFrames();
     * 3. 移除plist 文件精灵帧
     *  void removeSpriteFramesFromFile(const std::string & plist);
     * 4. 移除没有使用的精灵帧
     *  void removeUnusedSpriteFrames();
     */
    SpriteFrameCache::getInstance()->removeSpriteFrames();
	BaseScene::onExit();
}

cocos2d::Sprite * SpriteTest::getBGNode()
{
	return Sprite::create("spriteTest/background.png");
}
