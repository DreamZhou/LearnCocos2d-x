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
	// ��Դshahdza�Ĳ��� http://blog.51cto.com/shahdza/1561937
	//
	//һ��ԭ��
	//
	//	ClippingNode���ü��ڵ㣩���������Խڵ���вü���ClippingNode��Node�����࣬��������ͨ�ڵ�һ������Layer��Scene��Node�С�
	//	��Ҫ�Ǹ���һ��ģ�壨Stencil���и�ͼƬ�Ľڵ㣬�����κ���״�Ľڵ���ʾ��
	//	ClippingNode������ģ����������ɶ�Node����ü��ļ�����
	//	ClippingNode(�ü��ڵ�)	Stencil(ģ��)

	//�� ������****************
	// 1. ���� ClippingNode  ������Stencil
	ClippingNode* simpleClippingNode = ClippingNode::create();
	simpleClippingNode->setPosition(origin.x + 120, visibleSize.height - 120);
	addChild(simpleClippingNode);

	
	

	// 2. ���� Stencil , ����Node �ڵ㡣Stencil�����ӽڵ㣬����ʾ��
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

	// 3.�ü��ڵ���� Stencil 
	simpleClippingNode->setStencil(simpleStencil);

	// 4. ���òü�����  
	simpleClippingNode->setInverted(true);							//�Ƿ�ת��Ĭ����false  ��ʾ��ģ��ü������ĵװ����ݡ� true ��ת
	simpleClippingNode->setAlphaThreshold(0.5);						//����alpha͸������ֵ ��������Ĭ��Ϊ1����ȫ��

	// 3. ��� Content �װ�, ��Ҫ��ʾ������
	simpleClippingNode->addChild(Sprite::create("HelloWorld.png"));
	// 4. ���ö���
	//simpleClippingNode->runAction(RepeatForever::create(RotateBy::create(1, 45)));
	simpleStencil->runAction(RepeatForever::create(RotateBy::create(1, 45)));

	//�� ������****************

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
	// ��Ӵ����¼�
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(ClippingNodeScene::onToucheBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}
void ClippingNodeScene::onToucheBegan(const std::vector<Touch*>& touches, Event *unused_event) 
{
	//[1].��ȡ����, ת��Ϊ���holesClipper�ڵ�� �������
	Vec2 point = touches[0]->getLocation();
	auto pholesClipper=this->getChildByTag(1);
	point = pholesClipper->convertToNodeSpace(point);


	//[2].��ȡ�װ��������Rect
	Sprite* content = static_cast<Sprite*>(pholesClipper->getChildByName("content"));
	Size contentSize = content->getContentSize();
	Rect rect = Rect(-contentSize.width / 2, -contentSize.height / 2, contentSize.width, contentSize.height);


	//[3].�������ڵװ��ڲ�, ����"��"
	if (rect.containsPoint(point))
	{
		pokeHoleAtPoint(point);
	}
}
void ClippingNodeScene::pokeHoleAtPoint(Vec2 point)
{
	CCLOG("Add a Hole!!!");

	auto pholesClipper = static_cast<ClippingNode*>(this->getChildByTag(1));
	//[1].��ӵװ����� : һ�����ĺۼ�
	auto hole = Sprite::create("ClippingNode/hole_effect.png");
	hole->setPosition(point);
	pholesClipper->addChild(hole);


	//[2].���ģ������ : һ��С��
	auto holeStencil = Sprite::create("ClippingNode/hole_stencil.png");
	holeStencil->setPosition(point);
	auto holesStencil = pholesClipper->getStencil();
	holesStencil->addChild(holeStencil);


	//[3].����Ч�� : �Ŵ���С
	pholesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}