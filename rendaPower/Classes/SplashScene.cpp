#include "SplashScene.h"

#include "TitleScene.h"

using namespace ax;

Scene* SplashScene::scene()
{
    auto* scene = Scene::create();
    scene->addChild(SplashScene::create());
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto* splashSprite = Sprite::create("logo/Default-568h@2x.png");
    splashSprite->setPosition(Vec2(origin.x + visibleSize.width / 2.0F,
                                   origin.y + visibleSize.height / 2.0F));
    addChild(splashSprite, 0);

    runAction(Sequence::create(
        DelayTime::create(1.0F),
        CallFunc::create(AX_CALLBACK_0(SplashScene::nextScene, this)),
        nullptr));

    return true;
}

void SplashScene::nextScene()
{
    Director::getInstance()->replaceScene(TitleScene::scene());
}

void SplashScene::menuCloseCallback(Object* /*sender*/)
{
    Director::getInstance()->end();
}
