#include "BaseScene.h"

USING_NS_CC;

bool BaseScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = getBGNode();
	bg->setPosition(getVisbleCentrePos());
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	addChild(bg);

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BaseScene::menuBackCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	auto  closemenu = Menu::createWithItem(closeItem);
	closemenu->setPosition(Vec2::ZERO);
	addChild(closemenu, 0);
	return true;
}

Sprite* BaseScene::getBGNode()
{
	return Sprite::create("bg.png");
}
void BaseScene::menuBackCallback(Ref * )
{
	Director::getInstance()->popScene();
}
void BaseScene::problemLoading(const std::string& filename)
{
	printf("Error while loading: %s\n", filename.c_str());
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Vec2 BaseScene::getVisbleCentrePos()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
}
