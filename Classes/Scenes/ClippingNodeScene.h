#ifndef _CLIPPING_NODE_SCENE_H__
#define _CLIPPING_NODE_SCENE_H__

#include "Base/BaseScene.h"

class ClippingNodeScene :
	public BaseScene
{
public:
	static cocos2d::Scene * creatScene();
	bool init() override;

	void onToucheBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event);

	void pokeHoleAtPoint(cocos2d::Vec2 point);

	CREATE_FUNC(ClippingNodeScene);
};




#endif // !_CLIPPING_NODE_SCENE_H__



