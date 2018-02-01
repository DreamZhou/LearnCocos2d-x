#include <tuple>
#include <vector>
#include "MenuScene.h"
#include "Classes/Scenes/SpriteTestScene.h"
#include "Classes/Scenes/LostRoutes/LostRoutesLoading.h"
#include "3rdparty/fmt/fmt/format.h"
#include "3rdparty/fmt/fmt/printf.h"
USING_NS_CC;

std::vector<std::tuple<std::string, std::function<cocos2d::Scene*()>>>
testCases{
    {"SpriteTest",SpriteTest::createScene },
    {"LostRoutesLoading", LostRoutesLoading::createScene },
};

const size_t sceneName = 0;
const size_t sceneCreatFun = 1;
const std::string fontFile = "fonts/Marker Felt.ttf";
const float       fontSize = 30.f;


Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    auto  closemenu = Menu::createWithItem(closeItem);
    closemenu->setPosition(Vec2::ZERO);
    addChild(closemenu, 0);

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
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", fontFile, 24);
    if (label == nullptr)
    {
        problemLoading(fontFile.c_str());
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    fmt::printf("hello world!\n");
    printf("Hello World!\n");
    cocos2d::log("Hello World");
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
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
