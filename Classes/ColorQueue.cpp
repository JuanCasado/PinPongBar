//
//  ColorQueue.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#include "ColorQueue.hpp"

USING_NS_CC;

ColorQueue::ColorQueue(cocos2d::Size size, cocos2d::Vec2 pos){
    this->size = size;
    this->pos = pos;
}

ColorQueue* ColorQueue::create(cocos2d::Size size, cocos2d::Vec2 pos){
    ColorQueue *pRet = new(std::nothrow) ColorQueue(size, pos);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

ColorQueue* ColorQueue::createScene(cocos2d::Size size, cocos2d::Vec2 pos){
    return ColorQueue::create(size, pos);
}

bool ColorQueue::init(){
    if ( !Scene::init() ){
        return false;
    }
    auto background = Sprite::create("WhiteRect.png");
    if (background==nullptr){
        return false;
    }
    auto title = Label::createWithTTF("Color Queue", "markf.ttf", 70);
    if (title ==  nullptr){
        return false;
    }
    
    background->setContentSize(size);
    background->setPosition(pos);
    background->setColor(Color3B(193, 242, 185));
    
    auto pipeColor = Color3B(97, 111, 67);
    auto tl = Sprite::createWithTexture(background->getTexture());
    tl->setAnchorPoint(Vec2(0, 1));
    tl->setPosition(Vec2(size.width*0.1, size.height*0.95));
    tl->setContentSize(Size(size.width*0.2, size.height*0.03));
    tl->setColor(pipeColor);
    auto tr = Sprite::createWithTexture(background->getTexture());
    tr->setAnchorPoint(Vec2(1, 1));
    tr->setPosition(Vec2(size.width*0.9, size.height*0.95));
    tr->setContentSize(Size(size.width*0.2, size.height*0.03));
    tr->setColor(pipeColor);
    auto ls = Sprite::createWithTexture(background->getTexture());
    ls->setAnchorPoint(Vec2(1, 1));
    ls->setPosition(Vec2(size.width*0.3, size.height*0.95));
    ls->setContentSize(Size(size.height*0.03, size.height*0.9));
    ls->setColor(pipeColor);
    auto rs = Sprite::createWithTexture(background->getTexture());
    rs->setAnchorPoint(Vec2(0, 1));
    rs->setPosition(Vec2(size.width*0.7, size.height*0.95));
    rs->setContentSize(Size(size.height*0.03, size.height*0.9));
    rs->setColor(pipeColor);
    auto bt = Sprite::createWithTexture(background->getTexture());
    bt->setAnchorPoint(Vec2(0, 1));
    bt->setPosition(Vec2(size.width*0.3, size.height*0.08));
    bt->setContentSize(Size(size.width*0.4, size.height*0.03));
    bt->setColor(pipeColor);
    
    c1 = Sprite::createWithTexture(background->getTexture());
    c1->setPosition(Vec2(size.width*0.5, size.height*0.13));
    c1->setContentSize(Size(size.width*0.39, size.height*0.095));
    c1->setOpacity(0);
    c2 = Sprite::createWithTexture(background->getTexture());
    c2->setPosition(Vec2(size.width*0.5, size.height*0.23));
    c2->setContentSize(Size(size.width*0.39, size.height*0.095));
    c2->setOpacity(0);
    c3 = Sprite::createWithTexture(background->getTexture());
    c3->setPosition(Vec2(size.width*0.5, size.height*0.33));
    c3->setContentSize(Size(size.width*0.39, size.height*0.095));
    c3->setOpacity(0);
    c4 = Sprite::createWithTexture(background->getTexture());
    c4->setPosition(Vec2(size.width*0.5, size.height*0.43));
    c4->setContentSize(Size(size.width*0.39, size.height*0.095));
    c4->setOpacity(0);
    c5 = Sprite::createWithTexture(background->getTexture());
    c5->setPosition(Vec2(size.width*0.5, size.height*0.53));
    c5->setContentSize(Size(size.width*0.39, size.height*0.095));
    c5->setOpacity(0);
    c6 = Sprite::createWithTexture(background->getTexture());
    c6->setPosition(Vec2(size.width*0.5, size.height*0.63));
    c6->setContentSize(Size(size.width*0.39, size.height*0.095));
    c6->setOpacity(0);
    c7 = Sprite::createWithTexture(background->getTexture());
    c7->setPosition(Vec2(size.width*0.5, size.height*0.73));
    c7->setContentSize(Size(size.width*0.39, size.height*0.095));
    c7->setOpacity(0);
    c8 = Sprite::createWithTexture(background->getTexture());
    c8->setPosition(Vec2(size.width*0.5, size.height*0.83));
    c8->setContentSize(Size(size.width*0.39, size.height*0.095));
    c8->setOpacity(0);
    c9 = Sprite::createWithTexture(background->getTexture());
    c9->setPosition(Vec2(size.width*0.5, size.height*0.93));
    c9->setContentSize(Size(size.width*0.39, size.height*0.095));
    c9->setOpacity(0);
    
    background->addChild(tl);
    background->addChild(tr);
    background->addChild(ls);
    background->addChild(rs);
    background->addChild(bt);
    background->addChild(c1);
    background->addChild(c2);
    background->addChild(c3);
    background->addChild(c4);
    background->addChild(c5);
    background->addChild(c6);
    background->addChild(c7);
    background->addChild(c8);
    background->addChild(c9);
    this->addChild(background);
    return true;
}

void ColorQueue::addColor(Controll::Color color){
    data.push(color);
    auto sprite = getSprite(data.size());
    sprite->setColor(getColor(color));
    sprite->setOpacity(255);
}

void ColorQueue::removeColor(){
    for (int x = 1; x<=data.size(); x++){
        getSprite(x)->setOpacity(0);
    }
    data.pop();
    for (int x = 1; x<=data.size(); x++){
        auto sprite = getSprite(x);
        auto color = data.front();
        sprite->setColor(getColor(color));
        sprite->setOpacity(255);
        data.pop();
        data.push(color);
    }
}

Color3B ColorQueue::getColor(Controll::Color color){
    switch (color) {
        case Controll::Color::red:
            return Color3B(241, 151, 144);
        case Controll::Color::purple:
            return Color3B(217, 173, 216);
        case Controll::Color::blue:
            return Color3B(162, 216, 230);
        case Controll::Color::orange:
            return Color3B(255, 184, 118);
    }
}
Sprite *ColorQueue::getSprite(unsigned long num){
    switch (num) {
        case 1:
            return c1;
        case 2:
            return c2;
        case 3:
            return c3;
        case 4:
            return c4;
        case 5:
            return c5;
        case 6:
            return c6;
        case 7:
            return c7;
        case 8:
            return c8;
        default:
            return c9;
    }
}

bool ColorQueue::hasData(){
    return !data.empty();
}
Controll::Color ColorQueue::getData(){
    return data.front();
}
bool ColorQueue::isFull(){
    return data.size()>=9;
}
