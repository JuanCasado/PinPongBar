//
//  Controller.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#include "Controller.hpp"

USING_NS_CC;

Controll::Controll(cocos2d::Size size, cocos2d::Vec2 pos){
    this->size = size;
    this->pos = pos;
}

Controll* Controll::create(cocos2d::Size size, cocos2d::Vec2 pos){
    Controll *pRet = new(std::nothrow) Controll(size, pos);
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

Controll* Controll::createScene(cocos2d::Size size, cocos2d::Vec2 pos){
    return Controll::create(size, pos);
}

bool Controll::init(){
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
    
    auto bttSize = Size(size.width*0.16, size.width*0.18);
    
    auto redBackgroudStill = Sprite::createWithTexture(background->getTexture());
    redBackgroudStill->setContentSize(bttSize);
    redBackgroudStill->setColor(Color3B(241, 151, 144));
    auto redBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    redBackgroundClicked->setContentSize(bttSize);
    redBackgroundClicked->setColor(Color3B(217, 63, 63));
    auto redBackground = MenuItemSprite::create(redBackgroudStill, redBackgroundClicked, CC_CALLBACK_0(Controll::redTouched, this));
    auto purBackgroudStill = Sprite::createWithTexture(background->getTexture());
    purBackgroudStill->setContentSize(bttSize);
    purBackgroudStill->setColor(Color3B(217, 173, 216));
    auto purBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    purBackgroundClicked->setContentSize(bttSize);
    purBackgroundClicked->setColor(Color3B(170, 0, 224));
    auto purBackground = MenuItemSprite::create(purBackgroudStill, purBackgroundClicked, CC_CALLBACK_0(Controll::purpleTouched, this));
    auto bluBackgroudStill = Sprite::createWithTexture(background->getTexture());
    bluBackgroudStill->setContentSize(bttSize);
    bluBackgroudStill->setColor(Color3B(162, 216, 230));
    auto bluBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    bluBackgroundClicked->setContentSize(bttSize);
    bluBackgroundClicked->setColor(Color3B(45, 122, 211));
    auto bluBackground = MenuItemSprite::create(bluBackgroudStill, bluBackgroundClicked, CC_CALLBACK_0(Controll::blueTouched, this));
    auto oraBackgroudStill = Sprite::createWithTexture(background->getTexture());
    oraBackgroudStill->setContentSize(bttSize);
    oraBackgroudStill->setColor(Color3B(255, 184, 118));
    auto oraBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    oraBackgroundClicked->setContentSize(bttSize);
    oraBackgroundClicked->setColor(Color3B(229, 122, 78));
    auto oraBackground = MenuItemSprite::create(oraBackgroudStill, oraBackgroundClicked, CC_CALLBACK_0(Controll::orangeTouched, this));
    Vector <MenuItem*> menuItems;
    menuItems.pushBack(redBackground);
    menuItems.pushBack(bluBackground);
    menuItems.pushBack(purBackground);
    menuItems.pushBack(oraBackground);
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsHorizontallyWithPadding(25);
    buttonHolder->setPosition(Vec2(size.width*0.5, size.height*0.5));
    
    background->addChild(buttonHolder);
    this->addChild(background);
    return true;
}

void Controll::redTouched(){
    data.push(Color::red);
}
void Controll::purpleTouched(){
    data.push(Color::purple);
}
void Controll::blueTouched(){
    data.push(Color::blue);
}
void Controll::orangeTouched(){
    data.push(Color::orange);
}

bool Controll::hasData(){
    return !data.empty();
}

Controll::Color Controll::getData(){
    Controll::Color color = data.front();
    data.pop();
    return color;
}
