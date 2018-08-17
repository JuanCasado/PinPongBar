//
//  Displayer.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#include "Displayer.hpp"
USING_NS_CC;

Displayer::Displayer(std::string name, int sock){
    this->name = name;
    this->sock = sock;
}

Displayer* Displayer::createScene(std::string name, int sock){
    return Displayer::create(name, sock);
}

Displayer *Displayer::create(std::string name, int sock){
    Displayer *pRet = new(std::nothrow) Displayer(name, sock);
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

bool Displayer::init(){
    if ( !Scene::init() ){
        return false;
    }
    
    auto title = Label::createWithTTF("Playing against: "+name, "markf.ttf", 15);
    if (title ==  nullptr){
        return false;
    }
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0){
        return false;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    
    auto colorSize = Size(screen.width*0.5, screen.height*0.6);
    auto colorPos = Vec2(screen.width*0.5,screen.height*0.66);
    auto controlSize = Size(screen.width*0.9, screen.height*0.23);
    auto controlPos = Vec2(screen.width*0.5,screen.height*0.17);
    auto titlePos = Vec2(screen.width*0.5,screen.height*0.32);
    control = Controll::createScene(controlSize, controlPos);
    colorQueue = ColorQueue::createScene(colorSize, colorPos);
    
    title->setPosition(titlePos);
    title->setColor(Color3B(20, 40, 20));
    
    this->addChild(title);
    this->addChild(control);
    this->addChild(colorQueue);
    
    scheduleUpdate();
    
    return true;
}

void Displayer::update(float t){
    if(colorQueue->isFull()){
        toSend = 5;
        send(sock, &toSend, sizeof(toSend), 0);
        close(sock);
        auto scene = EndGame::createScene(EndGame::State::LOOSE);
        if (scene != nullptr){
            Director::getInstance()->replaceScene(scene);
        }
    }else{
        if(!(rand()%99999)){
            colorQueue->addColor(Controll::Color(rand() % 4));
        }
        if ((numbytes = recv(sock, &recived, sizeof(recived), 0))>=0){
            if (recived>4){
                close(sock);
                auto scene = EndGame::createScene(EndGame::State::WIN);
                if (scene != nullptr){
                    Director::getInstance()->replaceScene(scene);
                }
            }else{
                colorQueue->addColor(getColor(recived));
            }
        }
        if(control->hasData()){
            queuelColor = colorQueue->getData();
            controlColor = control->getData();
            if (controlColor == queuelColor){
                colorQueue->removeColor();
                toSend = getChar(queuelColor);
                if(send(sock, &toSend, sizeof(toSend), 0)<0){
                    close(sock);
                    auto scene = EndGame::createScene(EndGame::State::DISCONNECTED);
                    if (scene != nullptr){
                        Director::getInstance()->replaceScene(scene);
                    }
                }
            }else{
                colorQueue->addColor(Controll::Color(rand() % 4));
            }
        }else{
            if(!colorQueue->hasData()){
                colorQueue->addColor(Controll::Color(rand() % 4));
            }
        }
    }
}

char Displayer::getChar(Controll::Color color){
    switch (color) {
        case Controll::Color::red:
            return 0;
        case Controll::Color::purple:
            return 1;
        case Controll::Color::blue:
            return 2;
        case Controll::Color::orange:
            return 3;
    }
}
Controll::Color Displayer::getColor(char color){
    switch (color) {
        case 0:
            return Controll::Color::red;
        case 1:
            return Controll::Color::purple;
        case 2:
            return Controll::Color::blue;
        default:
            return Controll::Color::orange;
    }
}

Displayer::~Displayer(){
    close(sock);
}
