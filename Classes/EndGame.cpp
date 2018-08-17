//
//  EndGame.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/9/18.
//

#include "EndGame.hpp"
USING_NS_CC;

EndGame::EndGame(EndGame::State state){
    this->state = state;
}

EndGame *EndGame::createScene(EndGame::State state){
    return EndGame::create(state);
}

EndGame *EndGame::create(EndGame::State state){
    EndGame *pRet = new(std::nothrow) EndGame(state);
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

bool EndGame::init(){
    if ( !Scene::init() ){
        return false;
    }
    std::string titleStr;
    switch(state){
        case EndGame::State::WIN:
            titleStr = "You Won!!!";
            break;
        case EndGame::State::LOOSE:
            titleStr = "You Loose!!!";
            break;
        case EndGame::State::DISCONNECTED:
            titleStr = "Player disconnected";
            break;
    }
    auto background = Sprite::create("WhiteRect.png");
    if (background==nullptr){
        return false;
    }
    auto title = Label::createWithTTF(titleStr,"markf.ttf" ,70);
    if (title ==  nullptr){
        return false;
    }
    
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    background->setPosition(Vec2(screen.width*0.5, screen.height*0.4));
    background->setContentSize(Size(screen.width*0.6, screen.height*0.6));
    background->setColor(Color3B(193, 242, 185));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.87));
    title->setColor(Color3B(10, 30, 10));
    
    auto buttonSize = Size(screen.width*0.1, screen.width*0.1);
    auto backStill = Sprite::createWithTexture(background->getTexture());
    backStill->setContentSize(buttonSize);
    backStill->setColor(Color3B(120, 200, 100));
    auto backClicked = Sprite::createWithTexture(background->getTexture());
    backClicked->setContentSize(buttonSize);
    backClicked->setColor(Color3B(20, 50, 0));
    auto back = MenuItemSprite::create(backStill, backClicked, CC_CALLBACK_0(EndGame::back, this));
    auto backLabel = Label::createWithTTF("X", "markf.ttf", 10);
    backLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    back->addChild(backLabel);
    auto backHolder = Menu::createWithItem(back);
    backHolder->setAnchorPoint(Vec2(0.5, 0));
    backHolder->setPosition(Vec2(background->getContentSize().width*0.5, background->getContentSize().height*0.5));
    
    background->addChild(backHolder);
    this->addChild(background);
    this->addChild(title);
    return true;
}

void EndGame::back(){
    auto scene = MainMenu::createScene();
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}
