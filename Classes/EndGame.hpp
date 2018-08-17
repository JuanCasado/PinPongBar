//
//  EndGame.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/9/18.
//

#ifndef EndGame_hpp
#define EndGame_hpp
#include "MainMenu.hpp"
#include "cocos2d.h"

class EndGame : public cocos2d::Scene{
public:
    enum State{
      WIN, LOOSE, DISCONNECTED
    };
    static EndGame *createScene(EndGame::State state);
private:
    EndGame(EndGame::State state);
    virtual bool init() override;
    static EndGame *create(EndGame::State state);
    State state;
    void back (void);
};

#endif /* EndGame_hpp */
