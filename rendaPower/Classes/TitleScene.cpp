#include "TitleScene.h"

#include "SelectMenuScene.h"

using namespace ax;

Scene* TitleScene::scene()
{
    auto* scene = Scene::create();
    scene->addChild(TitleScene::create());
    return scene;
}

bool TitleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto* titleSprite = Sprite::create("base/Title_Rush_Freak.png");
    titleSprite->setTag(5000);
    titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                  origin.y + visibleSize.height * 0.75F));

    auto* scroll = Sequence::create(
        EaseInOut::create(MoveBy::create(1.0F, Vec2(0.0F, 30.0F)), 1.0F),
        EaseInOut::create(MoveBy::create(1.0F, Vec2(0.0F, -30.0F)), 1.0F),
        nullptr);
    titleSprite->runAction(RepeatForever::create(scroll));
    addChild(titleSprite, 0);

    auto* tapLabel = Label::createWithSystemFont("タッチしてスタート", "Arial", 32);
    auto* startButton = MenuItemLabel::create(
        tapLabel,
        AX_CALLBACK_1(TitleScene::nextScene, this));
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                  origin.y + visibleSize.height * 0.25F));

    auto* startMenu = Menu::create(startButton, nullptr);
    startMenu->setPosition(Vec2::ZERO);
    addChild(startMenu);

    return true;
}

void TitleScene::nextScene(Object* /*sender*/)
{
    if (auto* sprite = dynamic_cast<Sprite*>(getChildByTag(5000)))
    {
        sprite->stopAllActions();
    }

    Director::getInstance()->replaceScene(SelectMenuScene::scene());
}

void TitleScene::menuCloseCallback(Object* /*sender*/)
{
    Director::getInstance()->end();
}
