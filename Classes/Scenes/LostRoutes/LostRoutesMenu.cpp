#include "LostRoutesMenu.h"



LostRoutesMenu::LostRoutesMenu()
{
}


LostRoutesMenu::~LostRoutesMenu()
{
}

cocos2d::Scene * LostRoutesMenu::createScene()
{
    return LostRoutesMenu::create();
}

bool LostRoutesMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    return true;
}
