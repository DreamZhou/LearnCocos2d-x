#include "ClippingNodeScene.h"

USING_NS_CC;

cocos2d::Scene * ClippingNodeScene::creatScene()
{
	return ClippingNodeScene::create();
}

bool ClippingNodeScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//*************************
	// 来源shahdza的博客 http://blog.51cto.com/shahdza/1561937
	//
	//一、原理
	//
	//	ClippingNode（裁剪节点）可以用来对节点进行裁剪。ClippingNode是Node的子类，可以像普通节点一样放入Layer，Scene，Node中。
	//	主要是根据一个模板（Stencil）切割图片的节点，生成任何形状的节点显示。
	//	ClippingNode是利用模板遮罩来完成对Node区域裁剪的技术。
	//	ClippingNode(裁剪节点)	Stencil(模板)

	//二 简单遮罩****************
	// 1. 创建 ClippingNode  不适用Stencil
	ClippingNode* simpleClippingNode = ClippingNode::create();
	simpleClippingNode->setPosition(origin.x + 120, visibleSize.height - 120);
	addChild(simpleClippingNode);

	
	

	// 2. 设置 Stencil , 就是Node 节点。Stencil及其子节点，不显示。
	Node * simpleStencil = Node::create();
	std::string ballSrc = "ClippingNode/ball.png";
	auto ball1 = Sprite::create(ballSrc);
	auto ball2 = Sprite::create(ballSrc);
	auto ball3 = Sprite::create(ballSrc);
	auto ball4 = Sprite::create(ballSrc);
	auto ball5 = Sprite::create(ballSrc);

	ball1->setPosition(Vec2(60, 60));
	ball2->setPosition(Vec2(60, -60));
	ball3->setPosition(Vec2(0, 0));
	ball4->setPosition(Vec2(-60, 60));
	ball5->setPosition(Vec2(-60, -60));
     
	simpleStencil->addChild(ball1);
	simpleStencil->addChild(ball2);
	simpleStencil->addChild(ball3);
	simpleStencil->addChild(ball4);
	simpleStencil->addChild(ball5);

	// 3.裁剪节点添加 Stencil 
	simpleClippingNode->setStencil(simpleStencil);

	// 4. 设置裁剪属性  
	simpleClippingNode->setInverted(true);							//是否反转，默认是false  显示被模板裁剪下来的底板内容。 true 反转
	simpleClippingNode->setAlphaThreshold(0.5);						//设置alpha透明度阈值 ，不设置默认为1，即全部

	// 3. 添加 Content 底板, 即要显示的内容
	simpleClippingNode->addChild(Sprite::create("HelloWorld.png"));
	// 4. 设置动作
	//simpleClippingNode->runAction(RepeatForever::create(RotateBy::create(1, 45)));
	simpleStencil->runAction(RepeatForever::create(RotateBy::create(1, 45)));

	//三 简单遮罩****************

	ClippingNode * holesClipper = ClippingNode::create();
	holesClipper->setPosition(visibleSize.width - 200, origin.y + 200);
	addChild(holesClipper,0, 1);

	Node * holesStencil = Node::create();
	auto ball6 = Sprite::create(ballSrc);
	holesStencil->addChild(ball6);

	holesClipper->setStencil(holesStencil);
	holesClipper->setInverted(true);
	holesClipper->setAlphaThreshold(0.5f);

	holesClipper->addChild(Sprite::create("ClippingNode/blocks.png"),-1, "content");

	holesClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
	// 添加触摸事件
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ClippingNodeScene::onToucheBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}
void ClippingNodeScene::onToucheBegan(const std::vector<Touch*>& touches, Event *unused_event) 
{
	//[1].获取触点, 转换为相对holesClipper节点的 相对坐标
	Vec2 point = touches[0]->getLocation();
	auto pholesClipper=this->getChildByTag(1);
	point = pholesClipper->convertToNodeSpace(point);


	//[2].获取底板区域矩形Rect
	Sprite* content = static_cast<Sprite*>(pholesClipper->getChildByName("content"));
	Size contentSize = content->getContentSize();
	Rect rect = Rect(-contentSize.width / 2, -contentSize.height / 2, contentSize.width, contentSize.height);


	//[3].触摸点在底板内部, 进行"打洞"
	if (rect.containsPoint(point))
	{
		pokeHoleAtPoint(point);
	}
}
void ClippingNodeScene::pokeHoleAtPoint(Vec2 point)
{
	CCLOG("Add a Hole!!!");

	auto pholesClipper = static_cast<ClippingNode*>(this->getChildByTag(1));
	//[1].添加底板内容 : 一个洞的痕迹
	auto hole = Sprite::create("ClippingNode/hole_effect.png");
	hole->setPosition(point);
	pholesClipper->addChild(hole);


	//[2].添加模板内容 : 一个小洞
	auto holeStencil = Sprite::create("ClippingNode/hole_stencil.png");
	holeStencil->setPosition(point);
	auto holesStencil = pholesClipper->getStencil();
	holesStencil->addChild(holeStencil);


	//[3].动作效果 : 放大缩小
	pholesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}