#include "SelectMenuScene.h"
#include "axmol.h"
#include "audio/AudioEngine.h"
#include "common/SoundDef.h"
#include "ShuttleScene.h"

using namespace ax;

Scene* SelectMenuScene::scene()
{
    auto *scene = Scene::create();
    auto *layer = SelectMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool SelectMenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    /* 背景 */
    auto *backGround = LayerColor::create(Color4B::WHITE, size.width, size.height);
    backGround->setPosition(Vec2::ZERO);
    this->addChild(backGround);

    //タイトル
    auto * menuTitle = Label::createWithSystemFont("Game Menu", "Helvetica", 40);
    menuTitle->setColor(Color3B::RED);
    menuTitle->setPosition(Vec2(size.width/2, size.height * 0.85f));
    this->addChild(menuTitle);

    //スペースシャトルボタン
    auto *normalSprite = Sprite::create("base/menu_space_shuttle.png");
    auto *selectSprite = Sprite::createWithTexture(normalSprite->getTexture());
    selectSprite->setColor(Color3B(0x7F, 0x7F, 0x7F));
    
    auto *menu_space_shuttle = MenuItemSprite::create(normalSprite, selectSprite, AX_CALLBACK_1(SelectMenuScene::moveShuttleScene, this));
    
    auto * startMenu = Menu::create(menu_space_shuttle, nullptr);
    this->addChild(startMenu);
    
    startMenu->setPosition(Vec2::ZERO);
    menu_space_shuttle->setAnchorPoint(Vec2(0.5f, 0.5f));
    menu_space_shuttle->setPosition(Vec2(size.width/2, size.height * 0.65f));
        
    return true;
}

void SelectMenuScene::moveShuttleScene(Object* obj)
{
    AudioEngine::play2d(DEF_SE_SELECT);
    Director::getInstance()->replaceScene(ShuttleScene::scene());
}

void SelectMenuScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();
    
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    exit(0);
#endif
}
