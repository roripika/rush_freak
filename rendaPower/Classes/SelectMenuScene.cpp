#include "SelectMenuScene.h"

#include "ShuttleScene.h"

using namespace ax;

Scene* SelectMenuScene::scene()
{
    auto* scene = Scene::create();
    scene->addChild(SelectMenuScene::create());
    return scene;
}

bool SelectMenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto* background = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    background->setPosition(origin);
    addChild(background);

    auto* menuTitle = Label::createWithSystemFont("Game Menu", "Arial", 40);
    menuTitle->setTextColor(Color4B::RED);
    menuTitle->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                origin.y + visibleSize.height * 0.85F));
    addChild(menuTitle);

    auto* normalSprite = Sprite::create("base/menu_space_shuttle.png");
    auto* selectedSprite = Sprite::create("base/menu_space_shuttle.png");
    selectedSprite->setColor(Color3B(0x7F, 0x7F, 0x7F));

    auto* shuttleButton = MenuItemSprite::create(
        normalSprite,
        selectedSprite,
        AX_CALLBACK_1(SelectMenuScene::openShuttleScene, this));
    shuttleButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                    origin.y + visibleSize.height * 0.65F));

    auto* menu = Menu::create(shuttleButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);

    return true;
}

void SelectMenuScene::openShuttleScene(Object* /*sender*/)
{
    Director::getInstance()->replaceScene(ShuttleScene::scene());
}

void SelectMenuScene::menuCloseCallback(Object* /*sender*/)
{
    Director::getInstance()->end();
}
