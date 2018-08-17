//
//  Displayer.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 7/24/18.
//

#ifndef Displayer_hpp
#define Displayer_hpp

#include "Controller.hpp"
#include "ColorQueue.hpp"
#include "EndGame.hpp"
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "cocos2d.h"

class Displayer : public cocos2d::Scene{
public:
    static Displayer *createScene(std::string name, int sock);
private:
    Displayer(std::string name, int sock);
    ~Displayer();
    virtual bool init() override;
    static Displayer *create(std::string name, int sock);
    std::string name;
    int sock;
    Controll *control;
    ColorQueue *colorQueue;
    void update (float t) override;
    Controll::Color controlColor;
    Controll::Color queuelColor;
    char getChar(Controll::Color color);
    Controll::Color getColor(char color);
    char toSend;
    char recived;
    long numbytes;
};

#endif /* Displayer_hpp */
