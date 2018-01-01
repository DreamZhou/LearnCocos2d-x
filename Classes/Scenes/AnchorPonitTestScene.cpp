#include "AnchorPonitTestScene.h"
#include "Utility/playAnimation.h"
using namespace cocos2d;
cocos2d::Scene * AnchorPonitTestScene::createScene ()
{
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = AnchorPonitTestScene::create();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

bool AnchorPonitTestScene::init ()
{
    if (!Layer::init ())
    {
        return false;
    }
    Size visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    //����
    Sprite * bg = Sprite::create ("bg.png");
    Vec2 VisibleMiddle(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    bg->setPosition (VisibleMiddle);
    addChild (bg, -1);

    //�رհ�ť
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create (
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1 (AnchorPonitTestScene::menuCloseCallback, this));

    closeItem->setPosition (Vec2 (origin.x + visibleSize.width - closeItem->getContentSize ().width / 2,
        origin.y + closeItem->getContentSize ().height / 2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    helloWorld = Sprite::create("HelloWorld.png");
    helloWorld->setPosition(VisibleMiddle);
    addChild(helloWorld);


    MenuItemFont::setFontName("Microsoft YaHei");
    MenuItemFont::setFontSize(42);

    MenuItemFont* anchorZero    = MenuItemFont::create("AnchorZero", 
        CC_CALLBACK_1(AnchorPonitTestScene::anchorPositionCallback,this,Vec2::ANCHOR_BOTTOM_LEFT));
    MenuItemFont* anchorMiddle  = MenuItemFont::create("AnchorMiddle", 
        CC_CALLBACK_1(AnchorPonitTestScene::anchorPositionCallback, this,Vec2::ANCHOR_MIDDLE));
    MenuItemFont* anchorTopLeft = MenuItemFont::create("AnchorTopLeft",
        CC_CALLBACK_1(AnchorPonitTestScene::anchorPositionCallback, this, Vec2::ANCHOR_TOP_LEFT));
    MenuItemFont* anchorBottomRight = MenuItemFont::create("AnchorBottomRight",
        CC_CALLBACK_1(AnchorPonitTestScene::anchorPositionCallback, this, Vec2::ANCHOR_BOTTOM_RIGHT));
    MenuItemFont* anchorTopRight = MenuItemFont::create("AnchorTopRight",
        CC_CALLBACK_1(AnchorPonitTestScene::anchorPositionCallback, this, Vec2::ANCHOR_TOP_RIGHT));
    MenuItemFont* scale2 = MenuItemFont::create("SetScale2",
        CC_CALLBACK_1(AnchorPonitTestScene::setScaleCallback, this));
    MenuItemFont* rotation = MenuItemFont::create("SetRotation",
        CC_CALLBACK_1(AnchorPonitTestScene::setRotationCallback, this));

    MenuItemFont* playFanQie = MenuItemFont::create("playFanQie",
        CC_CALLBACK_1(AnchorPonitTestScene::playFanQieCallback, this));

    Menu * mn = Menu::create(anchorZero, anchorMiddle, anchorTopLeft, anchorBottomRight,
        anchorTopRight, scale2, rotation,playFanQie,nullptr);

    mn->alignItemsVertically();
    mn->setPosition(200, VisibleMiddle.y);
    addChild(mn);

    auto processNode = cocos2d::Node::create();
    processNode->setPosition(400, 400);
    addChild(processNode);
    Sprite *progressbgSprite = Sprite::create("DianLiangBack.png");

    processNode->addChild(progressbgSprite, 1);

    ////����һ������������  
    //Sprite *progressSprite = Sprite::create("DianLiang.png");
    //
    //progress1 = ProgressTimer::create(progressSprite);
    ////���ý���������ΪBAR  
    //progress1->setType(ProgressTimer::Type::BAR);//(kCCProgressTimerTypeBar);  

    ////���ȶ����˶����򣬿��Զ��Լ���ֵ������Ч��  
    ////��������߱仯//������  
    //progress1->setMidpoint(Vec2(0, 0));
    //progress1->setBarChangeRate(Vec2(1, 0));
    //progress1->setPercentage(0);//Ĭ������,���������޸�  
    //processNode->addChild(progress1, 1);
    //processNode->setScale(5.0f);

    //this->scheduleUpdate();
    return true;

}
void AnchorPonitTestScene::update(float dt)
{
    //static int percent = 0;
    //percent++;
    //if (percent  > 100)
    //{
    //    percent = 0;
    //}
    //progress1->setPercentage(percent);
}
void AnchorPonitTestScene::menuCloseCallback (cocos2d::Ref* )
{
    Director::getInstance()->popScene();
}
void AnchorPonitTestScene::anchorPositionCallback(cocos2d::Ref * pSender, const cocos2d::Vec2 &  position)
{
    helloWorld->setAnchorPoint(position);
}
void AnchorPonitTestScene::setScaleCallback(cocos2d::Ref * pSender)
{
    float scale= helloWorld->getScale();
    helloWorld->setScale(scale == 2.0f ? 1.0f : 2.0f);
}
void AnchorPonitTestScene::setRotationCallback(cocos2d::Ref * pSender) 
{
    static float rotation =0;
    rotation += 90.0f;
    helloWorld->setRotation(rotation);
    
}
void AnchorPonitTestScene::playFanQieCallback(cocos2d::Ref* pSender) 
{
    playAnimation::playAnimationFanqie(this, Vec2(20, 20), Vec2(500, 500));
}