#ifndef _BASE_SCENE_H__
#define _BASE_SCENE_H__

#include "cocos2d.h"

class BaseScene :public cocos2d::Scene 
{
public:

	bool init() override;

	virtual cocos2d::Sprite * getBGNode();

	virtual void menuBackCallback(Ref *);

	void problemLoading(const std::string & filename);

	cocos2d::Vec2 getVisbleCentrePos();

};




#endif // !_BASE_SCENE_H__


