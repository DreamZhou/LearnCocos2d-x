#include "MenuScene.h"
#include "AnchorPonitTestScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    Sprite * bg = Sprite::create ("bg.png");
    bg->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    addChild (bg, -1);

    Label * labelAnchorPonitTest = Label::createWithBMFont ("fonts/fnt2.fnt", "AnchorPonitTest");
    MenuItemLabel * MenuAnchorPonitTest = MenuItemLabel::create (labelAnchorPonitTest, CC_CALLBACK_1(MenuScene::OnClickMenuAnchorPonitTest,this));

    

    Menu * menuTest = Menu::create (MenuAnchorPonitTest, nullptr);
    menuTest->alignItemsVertically ();
    addChild (menuTest);

    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void MenuScene::OnClickMenuAnchorPonitTest (Ref* )
{
    auto sc = AnchorPonitTestScene::createScene();
    auto  reScene = TransitionSlideInR::create (0.5f, sc);
    Director::getInstance()->pushScene(reScene);
}
