#include <tuple>
#include <vector>
#include "MenuScene.h"
#include "3rdparty/fmt/fmt/format.h"
#include "3rdparty/fmt/fmt/printf.h"

#include "Classes/Scenes/SpriteTestScene.h"
#include "Classes/Scenes/LostRoutes/LostRoutesLoading.h"
#include "Classes/Scenes/AnchorPonitTestScene.h"
#include "Classes/Scenes/ClippingNodeScene.h"
USING_NS_CC;

std::vector<std::tuple<std::string, std::function<cocos2d::Scene*()>>>
testCases{
	{"SpriteTest",SpriteTest::createScene },
	{"LostRoutesLoading", LostRoutesLoading::createScene },
	{"AnchorPonitTestScene",AnchorPonitTestScene::createScene},
	{"ClippingNodeScene",ClippingNodeScene::creatScene},
};

const size_t sceneName = 0;
const size_t sceneCreatFun = 1;
const std::string fontFile = "fonts/Marker Felt.ttf";
const float       fontSize = 30.f;


Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    Vector<MenuItem*> menuItemArray;
    for (size_t i = 0; i < testCases.size(); i++)
    {
        auto spriteTest = Label::createWithTTF(std::get<sceneName>(testCases.at(i)), fontFile, fontSize);
        auto spriteTestItem = MenuItemLabel::create(spriteTest,
            CC_CALLBACK_1(MenuScene::menuChangeSceneCallback, this, i));
        menuItemArray.pushBack(spriteTestItem);
    }

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(menuItemArray);
    menu->setPosition(Vec2(origin.x + menu->getContentSize().width / 2, origin.y + visibleSize.height / 2));
    menu->alignItemsVertically();
    addChild(menu, 1);

    return true;
}


void MenuScene::menuBackCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MenuScene::menuChangeSceneCallback(Ref* pSender, size_t index)
{
    CCAssert(index <= testCases.size()," index error");

    auto scene = std::get<sceneCreatFun>(testCases.at(index))();
	//TODO 增加切换动画
	Director::getInstance()->pushScene(scene);
}
