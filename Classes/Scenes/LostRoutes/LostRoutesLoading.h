#ifndef __LOST_ROUTES_LOADING_H
#define __LOST_ROUTES_LOADING_H

#include "cocos2d.h"


class LostRoutesLoading :
    public cocos2d::Scene
{
public:
    virtual bool init() override;
    CREATE_FUNC(LostRoutesLoading);
    static cocos2d::Scene* createScene();
	void menuBackCallback(Ref * pSender);
	void loadingTextureCallBack(cocos2d::Texture2D * texture, int numberOfLoaded);
	virtual void onExit();

private:
	int m_nNumberOfLoaded = 0;
};

#endif // !__LOST_ROUTES_LOADING_H
