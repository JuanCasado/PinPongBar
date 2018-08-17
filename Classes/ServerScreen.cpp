//
//  ServerScreen.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/1/18.
//

#include "ServerScreen.hpp"

USING_NS_CC;

ServerScreen::ServerScreen(){
    succesOcurred.store(false,std::memory_order_seq_cst);
    failOcurred.store(false,std::memory_order_seq_cst);
    newPlayer.store(false, std::memory_order_seq_cst);
    joinAtempFail.store(false, std::memory_order_seq_cst);
    playerSet = false;
    server = nullptr;
}

Scene* ServerScreen::createScene(){
    return ServerScreen::create();
}
bool ServerScreen::init(){
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
    stillColor = Color3B(230, 250, 230);
    clickedColor = Color3B(240, 240, 30);
    auto labelColor = Color3B(5, 5, 5);
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    background->setPosition(Vec2(screen.width*0.5, screen.height*0.4));
    background->setContentSize(Size(screen.width*0.6, screen.height*0.6));
    background->setColor(Color3B(193, 242, 185));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.87));
    title->setColor(Color3B(10, 30, 10));
    Vector<MenuItem*> menuItems;
    auto fieldSize = Size(background->getContentSize().width*0.8, background->getContentSize().height*0.1);
    
    auto buttonSize = Size(screen.width*0.1, screen.width*0.1);
    auto backStill = Sprite::createWithTexture(background->getTexture());
    backStill->setContentSize(buttonSize);
    backStill->setColor(Color3B(120, 200, 100));
    auto backClicked = Sprite::createWithTexture(background->getTexture());
    backClicked->setContentSize(buttonSize);
    backClicked->setColor(Color3B(20, 50, 0));
    auto back = MenuItemSprite::create(backStill, backClicked, CC_CALLBACK_0(ServerScreen::back, this));
    auto backLabel = Label::createWithTTF("X", "markf.ttf", 10);
    backLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    back->addChild(backLabel);
    
    auto backHolder = Menu::createWithItem(back);
    backHolder->setAnchorPoint(Vec2(0.5, 0));
    backHolder->setPosition(Vec2(screen.width*0.5, screen.width*0.08));
    
    state = Label::createWithTTF("Creating Server...", "markf.ttf", 25);
    state->setColor(Color3B(20, 40, 20));
    state->setAnchorPoint(Vec2(0.5, 0));
    state->setPosition(Vec2(background->getContentSize().width*0.5, background->getContentSize().height*0.85));
    
    ipLabel = Label::createWithTTF("IP", "markf.ttf", 16);
    ipLabel->setColor(Color3B(20, 40, 20));
    ipLabel->setAnchorPoint(Vec2(0, 0));
    ipLabel->setPosition(Vec2(state->getPosition().x-state->getContentSize().width/2
                              , state->getPosition().y-state->getContentSize().height));
    
    portLabel = Label::createWithTTF("PORT", "markf.ttf", 16);
    portLabel->setColor(Color3B(20, 40, 20));
    portLabel->setAnchorPoint(Vec2(0, 0));
    portLabel->setPosition(Vec2(state->getPosition().x-state->getContentSize().width/2
                                , state->getPosition().y-state->getContentSize().height*2));

    nameBackgroudStill = Sprite::createWithTexture(background->getTexture());
    nameBackgroudStill->setContentSize(fieldSize);
    nameBackgroudStill->setColor(stillColor);
    auto nameBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    nameBackgroundClicked->setContentSize(fieldSize);
    nameBackgroundClicked->setColor(clickedColor);
    auto nameBackground = MenuItemSprite::create(nameBackgroudStill, nameBackgroundClicked, NULL);
    nameBackground->setEnabled(false);
    auto nameLabel = Label::createWithTTF("name:", "markf.ttf", 13);
    nameLabel->setAnchorPoint(Vec2(0, 0));
    nameLabel->setPosition(fieldSize.width*0.01, fieldSize.height*1.1);
    nameLabel->setColor(labelColor);
    nameBackground->addChild(nameLabel);
    nameField = ui::TextField::create("Your Name","markf.ttf",16);
    nameField->setCursorEnabled(true);
    nameField->setTextColor(Color4B(20, 40, 20, 255));
    nameField->setMaxLength(15);
    nameField->setPosition(Vec2(fieldSize.width*0.5, fieldSize.height*0.5));
    nameField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    nameField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                nameBackgroudStill->setColor(clickedColor);
                break;
            case ui::Widget::TouchEventType::ENDED:
                nameBackgroudStill->setColor(stillColor);
                break;
            case ui::Widget::TouchEventType::CANCELED:
                nameBackgroudStill->setColor(stillColor);
                break;
            default:
                break;
        }
    });
    nameBackground->addChild(nameField);
    
    passBackgroudStill = Sprite::createWithTexture(background->getTexture());
    passBackgroudStill->setContentSize(fieldSize);
    passBackgroudStill->setColor(stillColor);
    auto passBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    passBackgroundClicked->setContentSize(fieldSize);
    passBackgroundClicked->setColor(clickedColor);
    auto passBackground = MenuItemSprite::create(passBackgroudStill, passBackgroundClicked, NULL);
    passBackground->setEnabled(false);
    auto passLabel = Label::createWithTTF("password:", "markf.ttf", 13);
    passLabel->setAnchorPoint(Vec2(0, 0));
    passLabel->setPosition(fieldSize.width*0.01, fieldSize.height*1.1);
    passLabel->setColor(labelColor);
    passBackground->addChild(passLabel);
    passField = ui::TextField::create("**********","markf.ttf",16);
    passField->setPasswordEnabled(true);
    passField->setPasswordStyleText("*");
    passField->setCursorEnabled(true);
    passField->setTextColor(Color4B(20, 40, 20, 255));
    passField->setMaxLength(15);
    passField->setPosition(Vec2(fieldSize.width*0.5, fieldSize.height*0.5));
    passField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    passField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                passBackgroudStill->setColor(clickedColor);
                break;
            case ui::Widget::TouchEventType::ENDED:
                passBackgroudStill->setColor(stillColor);
                break;
            case ui::Widget::TouchEventType::CANCELED:
                passBackgroudStill->setColor(stillColor);
                break;
            default:
                break;
        }
    });
    passBackground->addChild(passField);
    
    auto playerBackgroudStill = Sprite::createWithTexture(background->getTexture());
    playerBackgroudStill->setContentSize(fieldSize);
    playerBackgroudStill->setColor(Color3B(120, 200, 100));
    auto playerBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    playerBackgroundClicked->setContentSize(fieldSize);
    playerBackgroundClicked->setColor(Color3B(20, 50, 0));
    auto playerBackground = MenuItemSprite::create(playerBackgroudStill, playerBackgroundClicked, CC_CALLBACK_0(ServerScreen::playerClicked, this));
    playerLabel = Label::createWithTTF("", "markf.ttf", 20);
    playerLabel->setPosition(fieldSize.width*0.5, fieldSize.height*0.5);
    playerLabel->setColor(labelColor);
    playerBackground->addChild(playerLabel);
    
    menuItems.pushBack(nameBackground);
    menuItems.pushBack(passBackground);
    menuItems.pushBack(playerBackground);
    
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsVerticallyWithPadding(30);
    buttonHolder->setPosition(Vec2(background->getContentSize().width*0.5, background->getContentSize().height*0.4));
    
    background->addChild(ipLabel);
    background->addChild(portLabel);
    background->addChild(buttonHolder);
    background->addChild(state);
    this->addChild(title);
    this->addChild(background);
    this->addChild(backHolder);
    
    scheduleUpdate();
    server = new IpServer(this);
    server->run();
    
    return true;
}

void ServerScreen::update(float t){
    if (succesOcurred.load(std::memory_order_seq_cst)){
        state->setString("Server joinable");
        state->setColor(Color3B(20, 150, 20));
        lock.lock();
        ipLabel->setString("IP: "+add);
        portLabel->setString("PORT: "+port);
        lock.unlock();
        succesOcurred.store(false, std::memory_order_seq_cst);
    }
    if (failOcurred.load(std::memory_order_seq_cst)){
        state->setString("Unable to create server");
        state->setColor(Color3B(150, 20, 20));
        closeConnection();
        failOcurred.store(false, std::memory_order_seq_cst);
    }
    if (newPlayer.load(std::memory_order_seq_cst)){
        lock.lock();
        playerLabel->setString(name);
        lock.unlock();
        playerSet = true;
        newPlayer.store(false, std::memory_order_seq_cst);
    }
    if(joinAtempFail.load(std::memory_order_seq_cst)){
        lock.lock();
        playerLabel->setString("join atempt failed " +std::to_string(err.load(std::memory_order_seq_cst)));
        lock.unlock();
        joinAtempFail.store(false, std::memory_order_seq_cst);
    }
}

void ServerScreen::back(void){
    closeConnection();
    auto scene = MainMenu::createScene();
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}

std::string ServerScreen::getPass(){
    return passField->getString();
}

std::string ServerScreen::getName(){
    return nameField->getString();
}

void ServerScreen::connectionFailed(){
    failOcurred.store(true,std::memory_order_seq_cst);
}
void ServerScreen::connectionSucceded(std::string add, std::string port){
    lock.lock();
    this->add = add;
    this->port = port;
    lock.unlock();
    succesOcurred.store(true,std::memory_order_seq_cst);
}

void ServerScreen::IpServer::to_beguin(){
    ok = false;
    socksize = sizeof(struct sockaddr_in);
    try {
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = htons(INADDR_ANY);
        
        if ((fd=socket(AF_INET, SOCK_STREAM, 0)) > 0){
            server.sin_family = AF_INET;
            bzero(&(server.sin_zero),8);
            if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))<=0) {
                if(listen(fd,1) <=0) {
                    std::string IpScreen = getIp();
                    if(IpScreen==""){
                        screen->connectionFailed();
                    }else{
                    screen->connectionSucceded(getIp(), std::to_string(PORT));
                    }
                }else{
                    screen->connectionFailed();
                }
            }else{
                screen->connectionFailed();
            }
        }else{
            screen->connectionFailed();
        }
    }catch(std::exception const & e){
        screen->connectionFailed();
    }
}

void ServerScreen::addPlayer(std::string name, int sock){
    newPlayer.store(true,std::memory_order_seq_cst);
    lock.lock();
    this->name = name;
    this->sock = sock;
    lock.unlock();
}

void ServerScreen::IpServer::to_do(){
    if ((temp = accept(fd, (struct sockaddr *)&server, &socksize))>=0){
        if ((numbytes=recv(temp,&buf,sizeof(buf),0))>0){
            buf[numbytes]='\0';
            std::vector<std::string> data;
            char *tock = nullptr;
            tock = strtok(buf, " ");
            while (tock != NULL){
                data.push_back(tock);
                tock = strtok(NULL, " ");
            }
            if (data.size()>=3){
                if(!data[0].compare("L")){
                    std::string pass = screen->getPass();
                    if (pass == ""){
                        pass = "none";
                    }
                    if(!data[1].compare(pass)){
                        ok = true;
                        sock = temp;
                        screen->addPlayer(data[2], sock);
                    }else{
                        close(temp);
                        screen->joinAtemtFailed(-5);
                    }
                }else{
                    close(temp);
                    screen->joinAtemtFailed(-4);
                }
            }else{
                close(temp);
                screen->joinAtemtFailed(-3);
            }
        }else{
            close(temp);
            screen->joinAtemtFailed(-2);
        }
    }else{
        screen->joinAtemtFailed(-1);
    }
}
void ServerScreen::IpServer::to_end(){
    close(fd);
    if (!ok){
        close(temp);
        close(sock);
    }
}
ServerScreen::IpServer::IpServer(ServerScreen * screen){
    this->screen = screen;
}
ServerScreen::IpServer::~IpServer(){
}

void ServerScreen::closeConnection(void){
    if (server!=nullptr){
        server->end();
        delete server;
        server = nullptr;
    }
}

std::string ServerScreen::IpServer::getIp(){
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) >= 0){
        const char* kGoogleDnsIp = "8.8.8.8";
        uint16_t kDnsPort = 53;
        struct sockaddr_in serv;
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
        serv.sin_port = htons(kDnsPort);
        int err;
        if((err = connect(sock, (const sockaddr*) &serv, sizeof(serv)))>=0){
            sockaddr_in name;
            socklen_t namelen = sizeof(name);
            if((err = getsockname(sock, (sockaddr*) &name, &namelen))>=0)
            {
                if(name.sin_family==AF_INET){
                    char buffer[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &name.sin_addr, buffer, namelen);
                    return buffer;
                }else if(name.sin_family==AF_INET6){
                    char buffer[INET6_ADDRSTRLEN];
                    inet_ntop(AF_INET, &name.sin_addr, buffer, namelen);
                    return buffer;
                }
            }
        }
    }
    close(sock);
    return "";
}

void ServerScreen::playerClicked(){
    if (playerSet){
        std::string name = getName();
        if (name == ""){
            name = "anonymous";
        }
        name = "L "+name;
        char toSend[name.size()];
        strcpy(toSend,name.c_str());
        send(sock, &toSend, sizeof(name), 0);
        lock.lock();
        auto scene = Displayer::createScene(name, sock);
        lock.unlock();
        if (scene != nullptr){
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void ServerScreen::joinAtemtFailed(int err){
    this->err.store(err, std::memory_order_seq_cst);
    joinAtempFail.store(true,std::memory_order_seq_cst);
}
