#include "HelloWorldScene.h"

using namespace ax;

Scene* HelloWorld::scene()
{
    auto* scene = Scene::create();
    scene->addChild(HelloWorld::create());
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto* closeItem = MenuItemImage::create(
        "base/CloseNormal.png",
        "base/CloseSelected.png",
        AX_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - 20.0F, origin.y + 20.0F));

    auto* menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    auto* label = Label::createWithSystemFont("Hello World", "Arial", 34);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2.0F, origin.y + visibleSize.height - 40.0F));
    addChild(label, 1);

    auto* sprite = Sprite::create("base/HelloWorld.png");
    sprite->setPosition(Vec2(origin.x + visibleSize.width / 2.0F, origin.y + visibleSize.height / 2.0F));
    addChild(sprite, 0);

    return true;
}

void HelloWorld::menuCloseCallback(Object* /*sender*/)
{
    Director::getInstance()->end();
}
