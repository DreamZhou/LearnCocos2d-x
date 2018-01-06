#ifndef __SYSTEM_HEADER_H
#define __SYSTEM_HEADER_H
#include <string>
#include "cocos2d.h"

const std::string SoundKey("sound_key");
const std::string MusicKey("music_key");
const std::string HighScoreKey("highscore_key");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

const std::string bg_music_home("sound/home_bg.aifc");
const std::string bg_music_game("sound/game_bg.aifc");
const std::string bg_blip("sound/Blip.aifc");
const std::string bg_explosion("sound/Explosion.aifc");

#else

const std::string bg_music_home("sound/home_bg.mp3");
const std::string bg_music_game("sound/game_bg.mp3");
const std::string bg_blip("sound/Blip.mp3");
const std::string bg_explosion("sound/Explosion.mp3");

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)




#endif // !__SYSTEM_HEADER_H

