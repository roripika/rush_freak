#include "ShuttleScene.h"

using namespace ax;

Scene* ShuttleScene::scene()
{
    auto* scene = Scene::create();
    scene->addChild(ShuttleScene::create());
    return scene;
}

bool ShuttleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto* background = LayerColor::create(Color4B(8, 12, 32, 255), visibleSize.width, visibleSize.height);
    background->setPosition(origin);
    addChild(background);

    m_planetSprite = Sprite::create("base/planet.png");
    m_planetSprite->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                     origin.y + visibleSize.height * 0.72F));
    addChild(m_planetSprite, 0);

    m_rocketSprite = Sprite::create("base/rocket.png");
    m_rocketSprite->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                     origin.y + visibleSize.height * 0.28F));
    addChild(m_rocketSprite, 1);

    auto* flyAction = Sequence::create(
        EaseSineInOut::create(MoveBy::create(1.2F, Vec2(0.0F, 28.0F))),
        EaseSineInOut::create(MoveBy::create(1.2F, Vec2(0.0F, -28.0F))),
        nullptr);
    m_rocketSprite->runAction(RepeatForever::create(flyAction));

    auto* caption = Label::createWithSystemFont("Axmol移植中: Space Shuttle", "Arial", 28);
    caption->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                              origin.y + visibleSize.height * 0.9F));
    addChild(caption, 2);

    return true;
}
