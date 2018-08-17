#include "MainMenu.hpp"

USING_NS_CC;

Scene* MainMenu::createScene(){
    return MainMenu::create();
}

bool MainMenu::init(){
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
    auto buttonSize = Size(background->getContentSize().width*0.8, background->getContentSize().height*0.13);
    auto stillColor = Color3B(120, 200, 100);
    auto clickedColor = Color3B(20, 50, 0);
    
    auto btt1Still = Sprite::createWithTexture(background->getTexture());
    btt1Still->setContentSize(buttonSize);
    btt1Still->setColor(stillColor);
    auto btt1Clicked = Sprite::createWithTexture(background->getTexture());
    btt1Clicked->setContentSize(buttonSize);
    btt1Clicked->setColor(clickedColor);
    auto btt1 = MenuItemSprite::create(btt1Still, btt1Clicked, CC_CALLBACK_0(MainMenu::btt1Touched, this));
    auto btt1Label = Label::createWithTTF("Join Local Game", "markf.ttf", 20);
    btt1Label->setPosition(buttonSize.width/2, buttonSize.height/2);
    btt1->addChild(btt1Label);
    
//    auto btt2Still = Sprite::createWithTexture(background->getTexture());
//    btt2Still->setContentSize(buttonSize);
//    btt2Still->setColor(stillColor);
//    auto btt2Clicked = Sprite::createWithTexture(background->getTexture());
//    btt2Clicked->setContentSize(buttonSize);
//    btt2Clicked->setColor(clickedColor);
//    auto btt2 = MenuItemSprite::create(btt2Still, btt2Clicked, CC_CALLBACK_0(MainMenu::btt2Touched, this));
//    auto btt2Label = Label::createWithTTF("UDP", "./fonts/Marker Felt.ttf", 20);
//    btt2Label->setPosition(buttonSize.width/2, buttonSize.height/2);
//    btt2->addChild(btt2Label);
//
//    auto btt3Still = Sprite::createWithTexture(background->getTexture());
//    btt3Still->setContentSize(buttonSize);
//    btt3Still->setColor(stillColor);
//    auto btt3Clicked = Sprite::createWithTexture(background->getTexture());
//    btt3Clicked->setContentSize(buttonSize);
//    btt3Clicked->setColor(clickedColor);
//    auto btt3 = MenuItemSprite::create(btt3Still, btt3Clicked, CC_CALLBACK_0(MainMenu::btt3Touched, this));
//    auto btt3Label = Label::createWithTTF("BTT", "./fonts/Marker Felt.ttf", 20);
//    btt3Label->setPosition(buttonSize.width/2, buttonSize.height/2);
//    btt3->addChild(btt3Label);
//
//    auto btt4Still = Sprite::createWithTexture(background->getTexture());
//    btt4Still->setContentSize(buttonSize);
//    btt4Still->setColor(stillColor);
//    auto btt4Clicked = Sprite::createWithTexture(background->getTexture());
//    btt4Clicked->setContentSize(buttonSize);
//    btt4Clicked->setColor(clickedColor);
//    auto btt4 = MenuItemSprite::create(btt4Still, btt4Clicked, CC_CALLBACK_0(MainMenu::btt4Touched, this));
//    auto btt4Label = Label::createWithTTF("BD", "./fonts/Marker Felt.ttf", 20);
//    btt4Label->setPosition(buttonSize.width/2, buttonSize.height/2);
//    btt4->addChild(btt4Label);
    
    auto btt5Still = Sprite::createWithTexture(background->getTexture());
    btt5Still->setContentSize(buttonSize);
    btt5Still->setColor(stillColor);
    auto btt5Clicked = Sprite::createWithTexture(background->getTexture());
    btt5Clicked->setContentSize(buttonSize);
    btt5Clicked->setColor(clickedColor);
    auto btt5 = MenuItemSprite::create(btt5Still, btt5Clicked, CC_CALLBACK_0(MainMenu::btt5Touched, this));
    auto btt5Label = Label::createWithTTF("Create Local Game", "markf.ttf", 20);
    btt5Label->setPosition(buttonSize.width/2, buttonSize.height/2);
    btt5->addChild(btt5Label);
    
//    auto btt6Still = Sprite::createWithTexture(background->getTexture());
//    btt6Still->setContentSize(buttonSize);
//    btt6Still->setColor(stillColor);
//    auto btt6Clicked = Sprite::createWithTexture(background->getTexture());
//    btt6Clicked->setContentSize(buttonSize);
//    btt6Clicked->setColor(clickedColor);
//    auto btt6 = MenuItemSprite::create(btt6Still, btt6Clicked, CC_CALLBACK_0(MainMenu::btt6Touched, this));
//    auto btt6Label = Label::createWithTTF("GAME VIEW", "./fonts/Marker Felt.ttf", 20);
//    btt6Label->setPosition(buttonSize.width/2, buttonSize.height/2);
//    btt6->addChild(btt6Label);
    
    menuItems.pushBack(btt1);
//    menuItems.pushBack(btt2);
//    menuItems.pushBack(btt3);
//    menuItems.pushBack(btt4);
    menuItems.pushBack(btt5);
//    menuItems.pushBack(btt6);
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsVerticallyWithPadding(10);
    buttonHolder->setPosition(background->getPosition());
    
    this->addChild(title);
    this->addChild(background);
    this->addChild(buttonHolder);
    return true;
}

void MainMenu::btt1Touched(){//TCP
    auto scene = TcpClientScreen::createScene();
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}
void MainMenu::btt2Touched(){//UDP
    
}
void MainMenu::btt3Touched(){//BTT
    
}
void MainMenu::btt4Touched(){//BD
    
}
void MainMenu::btt5Touched(){//IP SERV
    auto scene = ServerScreen::createScene();
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}
void MainMenu::btt6Touched(){//BTT SERV
    auto scene = Displayer::createScene("name", 5);
    if (scene != nullptr){
        Director::getInstance()->replaceScene(scene);
    }
}
