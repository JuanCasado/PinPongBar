//
//  Controller.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <queue>
#include "cocos2d.h"

class Controll : public cocos2d::Scene{
public:
    enum Color{
        red, purple, blue, orange
    };
    static Controll *createScene(cocos2d::Size size, cocos2d::Vec2 pos);
    bool hasData();
    Color getData();
private:
    Controll(cocos2d::Size size, cocos2d::Vec2 pos);
    virtual bool init() override;
    static Controll *create(cocos2d::Size size, cocos2d::Vec2 pos);
    cocos2d::Size size;
    cocos2d::Vec2 pos;
    void redTouched();
    void purpleTouched();
    void blueTouched();
    void orangeTouched();
    std::queue <Color> data;
};

#endif /* Controller_hpp */
