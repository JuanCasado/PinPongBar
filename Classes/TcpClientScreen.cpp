//
//  TcpClientScreen.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/2/18.
//

#include "TcpClientScreen.hpp"
#include <iostream>

USING_NS_CC;

TcpClientScreen::TcpClientScreen(){
    this->failOcurred.store(false,std::memory_order_seq_cst);
    this->succesOcurred.store(false,std::memory_order_seq_cst);
    connection = nullptr;
}

Scene* TcpClientScreen::createScene(){
    return TcpClientScreen::create();
}
bool TcpClientScreen::init(){
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
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    background->setPosition(Vec2(screen.width*0.5, screen.height*0.4));
    background->setContentSize(Size(screen.width*0.6, screen.height*0.6));
    background->setColor(Color3B(193, 242, 185));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.87));
    title->setColor(Color3B(10, 30, 10));
    
    Vector<MenuItem*> menuItems;
    auto fieldSize = Size(background->getContentSize().width*0.8, background->getContentSize().height*0.1);
    stillColor = Color3B(230, 250, 230);
    clickedColor = Color3B(240, 240, 30);
    auto labelColor = Color3B(5, 5, 5);
    
    auto buttonSize = Size(screen.width*0.1, screen.width*0.1);
    auto backStill = Sprite::createWithTexture(background->getTexture());
    backStill->setContentSize(buttonSize);
    backStill->setColor(Color3B(120, 200, 100));
    auto backClicked = Sprite::createWithTexture(background->getTexture());
    backClicked->setContentSize(buttonSize);
    backClicked->setColor(Color3B(20, 50, 0));
    auto back = MenuItemSprite::create(backStill, backClicked, CC_CALLBACK_0(TcpClientScreen::back, this));
    auto backLabel = Label::createWithTTF("X", "markf.ttf", 10);
    backLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    back->addChild(backLabel);
    
    auto backHolder = Menu::createWithItem(back);
    backHolder->setAnchorPoint(Vec2(0.5, 0));
    backHolder->setPosition(Vec2(screen.width*0.5, screen.width*0.08));

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
    
    ipBackgroudStill = Sprite::createWithTexture(background->getTexture());
    ipBackgroudStill->setContentSize(fieldSize);
    ipBackgroudStill->setColor(stillColor);
    auto ipBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    ipBackgroundClicked->setContentSize(fieldSize);
    ipBackgroundClicked->setColor(clickedColor);
    auto ipBackground = MenuItemSprite::create(ipBackgroudStill, ipBackgroundClicked, NULL);
    ipBackground->setEnabled(false);
    auto ipLabel = Label::createWithTTF("ip:", "markf.ttf", 13);
    ipLabel->setAnchorPoint(Vec2(0, 0));
    ipLabel->setPosition(fieldSize.width*0.01, fieldSize.height*1.1);
    ipLabel->setColor(labelColor);
    ipBackground->addChild(ipLabel);
    ipField = ui::TextField::create("XXXX.XXXX.XXXX.XXXX","markf.ttf",16);
    ipField->setCursorEnabled(true);
    ipField->setTextColor(Color4B(20, 40, 20, 255));
    ipField->setMaxLength(15);
    ipField->setPosition(Vec2(fieldSize.width*0.5, fieldSize.height*0.5));
    ipField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    ipField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                ipBackgroudStill->setColor(clickedColor);
                break;
            case ui::Widget::TouchEventType::ENDED:
                ipBackgroudStill->setColor(stillColor);
                break;
            case ui::Widget::TouchEventType::CANCELED:
                ipBackgroudStill->setColor(stillColor);
                break;
            default:
                break;
        }
    });
    ipBackground->addChild(ipField);
    
    portBackgroudStill = Sprite::createWithTexture(background->getTexture());
    portBackgroudStill->setContentSize(fieldSize);
    portBackgroudStill->setColor(stillColor);
    auto portBackgroundClicked = Sprite::createWithTexture(background->getTexture());
    portBackgroundClicked->setContentSize(fieldSize);
    portBackgroundClicked->setColor(clickedColor);
    auto portBackground = MenuItemSprite::create(portBackgroudStill, portBackgroundClicked, NULL);
    portBackground->setEnabled(false);
    auto portLabel = Label::createWithTTF("port:", "markf.ttf", 13);
    portLabel->setAnchorPoint(Vec2(0, 0));
    portLabel->setPosition(fieldSize.width*0.01, fieldSize.height*1.1);
    portLabel->setColor(labelColor);
    portBackground->addChild(portLabel);
    portField = ui::TextField::create("XXXX","markf.ttf",16);
    portField->setCursorEnabled(true);
    portField->setTextColor(Color4B(20, 40, 20, 255));
    portField->setMaxLength(15);
    portField->setPosition(Vec2(fieldSize.width*0.5, fieldSize.height*0.5));
    portField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    portField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                portBackgroudStill->setColor(clickedColor);
                break;
            case ui::Widget::TouchEventType::ENDED:
                portBackgroudStill->setColor(stillColor);
                break;
            case ui::Widget::TouchEventType::CANCELED:
                portBackgroudStill->setColor(stillColor);
                break;
            default:
                break;
        }
    });
    portBackground->addChild(portField);
    
    auto bttSize = Size(background->getContentSize().width*0.8, background->getContentSize().height*0.13);
    auto bttStill = Sprite::createWithTexture(background->getTexture());
    bttStill->setContentSize(bttSize);
    bttStill->setColor(Color3B(120, 200, 100));
    auto bttClicked = Sprite::createWithTexture(background->getTexture());
    bttClicked->setContentSize(bttSize);
    bttClicked->setColor(Color3B(20, 50, 0));
    auto btt = MenuItemSprite::create(bttStill, bttClicked, CC_CALLBACK_0(TcpClientScreen::createConnection, this));
    auto bttLabel = Label::createWithTTF("Connect", "markf.ttf", 19);
    bttLabel->setPosition(bttSize.width/2, bttSize.height/2);
    btt->addChild(bttLabel);
    
    banner = Label::createWithTTF("Try to Connect", "markf.ttf", 16);
    banner->setAnchorPoint(Vec2(0.5, 0));
    banner->setPosition(Vec2(background->getContentSize().width*0.5, background->getContentSize().width*1.65));
    banner->setColor(Color3B(20, 40, 20));
    auto fade = FadeTo::create(2, 0);
    banner->runAction(fade);
    
    menuItems.pushBack(nameBackground);
    menuItems.pushBack(passBackground);
    menuItems.pushBack(ipBackground);
    menuItems.pushBack(portBackground);
    menuItems.pushBack(btt);
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsVerticallyWithPadding(30);
    buttonHolder->setPosition(Vec2(background->getContentSize().width*0.5, background->getContentSize().height*0.5));
    
    background->addChild(banner);
    background->addChild(buttonHolder);
    this->addChild(title);
    this->addChild(background);
    this->addChild(backHolder);
    
    scheduleUpdate();
    
    return true;
}

void TcpClientScreen::back(void){
    closeConnection();
    auto scene = MainMenu::createScene();
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}

void TcpClientScreen::closeConnection(void){
    if (connection!=nullptr){
        connection->end();
        delete connection;
        connection = nullptr;
    }
}

void TcpClientScreen::createConnection(void){
    name = nameField->getString();
    pass = passField->getString();
    ip = ipField->getString();
    port = portField->getString();
    connection = new TcpClient(name, pass, ip, port, this);
    connection->run();
}

void TcpClientScreen::update(float t){
    if (succesOcurred.load(std::memory_order_seq_cst)){
        banner->setString("Connected");
        banner->setOpacity(255);
        auto fade = FadeTo::create(2, 0);
        banner->runAction(fade);
        nameField->setString("");
        passField->setString("");
        ipField->setString("");
        portField->setString("");
        succesOcurred.store(false, std::memory_order_seq_cst);
        lock.lock();
        auto scene = Displayer::createScene(player, sock);
        lock.unlock();
        closeConnection();
        if (scene != nullptr){
            Director::getInstance()->replaceScene(scene);
        }
    }
    if (failOcurred.load(std::memory_order_seq_cst)){
        banner->setString("Unable to connect");
        banner->setOpacity(255);
        auto fade = FadeTo::create(2, 0);
        banner->runAction(fade);
        nameField->setString("");
        passField->setString("");
        ipField->setString("");
        portField->setString("");
        closeConnection();
        failOcurred.store(false, std::memory_order_seq_cst);
    }
}

void TcpClientScreen::connectionSucceded(std::string player, int sock){
    this->succesOcurred.store(true,std::memory_order_seq_cst);
    lock.lock();
    this->player = player;
    this->sock = sock;
    lock.unlock();
}
void TcpClientScreen::connectionFailed(void){
    this->failOcurred.store(true,std::memory_order_seq_cst);
}

TcpClientScreen::TcpClient::TcpClient(std::string name, std::string pass, std::string ip, std::string port, TcpClientScreen * screen){
    if(name == ""){
        name = "anonymous";
    }
    if(pass == ""){
        pass = "none";
    }
    this->log.clear();
    this->log.append("L ");
    this->log.append(pass);
    this->log.append(" ");
    this->log.append(name);
    this->ip = ip;
    this->port = port;
    this->screen = screen;
}
TcpClientScreen::TcpClient::~TcpClient(){}

void TcpClientScreen::TcpClient::to_beguin(){
    try {
        server.sin_port = htons(std::stoi(port));
        if(ip.find(":")!=std::string::npos){
            server.sin_family = AF_INET6;
        }else{
            server.sin_family = AF_INET;
        }
        server.sin_addr.s_addr =  inet_addr(ip.c_str());
        bzero(&(server.sin_zero),8);
        if ((fd=socket(AF_INET, SOCK_STREAM, 0))>=0){
            if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))>=0){
                char buff [log.size()];
                strcpy(buff,log.c_str());
                write(fd, &buff, sizeof(buff));
                numbytes=recv(fd,buf,MAXDATASIZE,0);
                std::vector<std::string> data;
                char *tock = nullptr;
                tock = strtok(buf, " ");
                while (tock != NULL){
                    data.push_back(tock);
                    tock = strtok(NULL, " ");
                }
                if (data.size()>=2){
                    if (!data[0].compare("L")){
                        ok = true;
                        screen->connectionSucceded(data[1], fd);
                    }else{
                        screen->connectionFailed();
                        ok = false;
                    }
                }else{
                    screen->connectionFailed();
                    ok = false;
                }
            }else{
                screen->connectionFailed();
                ok = false;
            }
        }else{
            screen->connectionFailed();
            ok = false;
        }
    }catch(std::exception const & e){
        screen->connectionFailed();
        ok = false;
    }
}

void TcpClientScreen::TcpClient::to_do(){
}
void TcpClientScreen::TcpClient::to_end(){
    if (!ok){
        close(fd);
    }
}
