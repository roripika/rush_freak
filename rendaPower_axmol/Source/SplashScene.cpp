#include "SplashScene.h"
#include "TitleScene.h"
#include "axmol.h"

using namespace ax;

Scene* SplashScene::scene()
{
    auto *scene = Scene::create();
    auto *layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    //ロゴ
    auto* pSprite = Sprite::create("Default-568h@2x.png");
    if (pSprite) {
        pSprite->setPosition(Vec2(size.width/2, size.height/2));
        this->addChild(pSprite, 0);
    }
    
    //１秒間表示
    this->runAction(
        Sequence::create(
            DelayTime::create(1.0f),
            CallFunc::create(AX_CALLBACK_0(SplashScene::nextScene, this)),
            nullptr
        )
    );
    
    return true;
}

void SplashScene::nextScene()
{
    Director::getInstance()->replaceScene(TitleScene::scene());
}

