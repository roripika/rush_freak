#include "TitleScene.h"
#include "SelectMenuScene.h"
#include "axmol.h"
#include "audio/AudioEngine.h"
#include "common/SoundDef.h"

// Note: NativeCodeAst might need to be ported or removed if not available in Axmol
// For now, I'll keep it if it's in the project, but use ax namespace if applicable.
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "common/NativeCodeAst.h"
#endif

using namespace ax;

Scene* TitleScene::scene()
{
    auto *scene = Scene::create();
    auto *layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    // AstExt::NativeCodeAst::showAst(); // Depending on porting status
#endif
    
    auto size = Director::getInstance()->getWinSize();

    auto* pSprite = Sprite::create("base/Title_Rush_Freak.png");
    pSprite->setTag(5000);
    
    pSprite->setPosition(Vec2(size.width/2, size.height*0.75f));
    auto *Scroll = Sequence::create(
        EaseInOut::create(MoveBy::create(1.0, Vec2(0,30)), 1.0f),
        EaseInOut::create(MoveBy::create(1.0, Vec2(0,-30)), 1.0f),
        nullptr
    );
    pSprite->runAction(RepeatForever::create(Scroll));
    
    auto* tapLabel = Label::createWithSystemFont("タッチしてスタート", "Helvetica", 32);
    auto* labelButton = MenuItemLabel::create(tapLabel, AX_CALLBACK_1(TitleScene::NextScene, this));
    auto* startMenu = Menu::create(labelButton, nullptr);
    this->addChild(startMenu);

    startMenu->setPosition(Vec2::ZERO);
    
    labelButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelButton->setPosition(Vec2(size.width/2, size.height * 0.25f));
    
    this->addChild(pSprite, 0);

    AudioEngine::preload(DEF_SE_SELECT);
    
    return true;
}

void TitleScene::NextScene(Object* obj)
{
    auto *sprite = static_cast<Sprite*>(this->getChildByTag(5000));
    if (sprite) {
        sprite->stopAllActions();
    }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    // AstExt::NativeCodeAst::hideAst();
#endif
    
    AudioEngine::play2d(DEF_SE_SELECT);
    Director::getInstance()->replaceScene(SelectMenuScene::scene());
}

void TitleScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();
    
#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    exit(0);
#endif
}
