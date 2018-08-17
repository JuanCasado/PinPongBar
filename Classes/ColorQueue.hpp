//
//  ColorQueue.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#ifndef ColorQueue_hpp
#define ColorQueue_hpp
#include "Controller.hpp"
#include <queue>
#include "cocos2d.h"

class ColorQueue : public cocos2d::Scene{
public:
    static ColorQueue *createScene(cocos2d::Size size, cocos2d::Vec2 pos);
    void addColor(Controll::Color color);
    void removeColor();
    bool hasData();
    bool isFull();
    Controll::Color getData();
private:
    ColorQueue(cocos2d::Size size, cocos2d::Vec2 pos);
    virtual bool init() override;
    static ColorQueue *create(cocos2d::Size size, cocos2d::Vec2 pos);
    cocos2d::Size size;
    cocos2d::Vec2 pos;
    cocos2d::Sprite *c1;
    cocos2d::Sprite *c2;
    cocos2d::Sprite *c3;
    cocos2d::Sprite *c4;
    cocos2d::Sprite *c5;
    cocos2d::Sprite *c6;
    cocos2d::Sprite *c7;
    cocos2d::Sprite *c8;
    cocos2d::Sprite *c9;
    std::queue <Controll::Color> data;
    cocos2d::Color3B getColor(Controll::Color color);
    cocos2d::Sprite *getSprite(unsigned long num);
};

#endif /* ColorQueue_hpp */
