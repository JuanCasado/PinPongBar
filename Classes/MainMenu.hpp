#ifndef __MAINMENU_SCENE_HPP__
#define __MAINMENU_SCENE_HPP__

#include "ServerScreen.hpp"
#include "TcpClientScreen.hpp"
#include "Displayer.hpp"
#include "cocos2d.h"

class MainMenu : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
private:
    virtual bool init();
    CREATE_FUNC(MainMenu);
    void btt1Touched();
    void btt2Touched();
    void btt3Touched();
    void btt4Touched();
    void btt5Touched();
    void btt6Touched();
};

#endif // __MAINMENU_SCENE_HPP__
