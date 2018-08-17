//
//  ServerScreen.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/1/18.
//

#ifndef ServerScreen_hpp
#define ServerScreen_hpp
#include "MainMenu.hpp"
#include "Displayer.hpp"
#include "Hilo.hpp"
#include "ui/CocosGUI.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <queue>
#include <vector>
#include "cocos2d.h"

#define PORT 5001
#define MAXDATASIZE 200

class ServerScreen : public cocos2d::Scene{
public:
    class IpServer : public Hilo{
    protected:
        virtual void to_do();
        virtual void to_beguin();
        virtual void to_end();
    public:
        
    private:
        IpServer(ServerScreen * screen);
        ~IpServer();
        ServerScreen * screen;
        friend class ServerScreen;
        int fd, sock, temp;
        struct sockaddr_in server;
        struct sockaddr_in client;
        struct hostent *he;
        char buf[MAXDATASIZE];
        long numbytes;
        bool ok;
        friend class TcpClientScreen;
        std::mutex lock;
        std::queue <std::string> data;
        socklen_t socksize;
        std::string getIp(void);
    };
    static cocos2d::Scene* createScene();
private:
    ServerScreen();
    virtual bool init() override;
    CREATE_FUNC(ServerScreen);
    void back (void);
    void update (float t) override;
    std::atomic_bool succesOcurred;
    std::atomic_bool failOcurred;
    cocos2d::Label * state;
    cocos2d::Label * ipLabel;
    cocos2d::Label * portLabel;
    IpServer * server;
    std::string pass;
    cocos2d::ui::TextField * passField;
    cocos2d::Sprite * passBackgroudStill;
    cocos2d::ui::TextField * nameField;
    cocos2d::Sprite * nameBackgroudStill;
    cocos2d::Color3B stillColor;
    cocos2d::Color3B clickedColor;
    void connectionFailed();
    void connectionSucceded(std::string add, std::string port);
    std::string getPass(void);
    std::string getName(void);
    std::string add;
    std::string port;
    std::mutex lock;
    void closeConnection(void);
    void addPlayer(std::string name, int socket);
    std::atomic_bool newPlayer;
    std::string name;
    void playerClicked();
    cocos2d::Label *playerLabel;
    bool playerSet;
    std::atomic_bool joinAtempFail;
    void joinAtemtFailed(int err);
    std::atomic_int err;
    int sock;
};

#endif /* ServerScreen_hpp */
