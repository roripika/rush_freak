#include "AppDelegate.h"
#include "axmol.h"
#include "audio/AudioEngine.h"
#include "TitleScene.h"

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "NativeCodeAst.h"
#endif

using namespace ax;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto *director = Director::getInstance();
    auto *glView = director->getGLView();
    if(!glView) {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect("rendaPower", Rect(0,0,640,1136));
#else
        glView = GLViewImpl::create("rendaPower");
#endif
        director->setGLView(glView);
    }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
    // NativeCodeAst::initAst();
#endif
    
    auto frameSize = glView->getFrameSize();
    
    // Set design resolution
    // Original logic was quite complex, simplifying slightly for Axmol's modern multi-resolution support
    if (frameSize.width < frameSize.height) {
        // Portrait
        if (isLongScreen(frameSize.width, frameSize.height)) {
            glView->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
        } else {
            glView->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
        }
    } else {
        // Landscape
        if (isLongScreen(frameSize.width, frameSize.height)) {
            glView->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
        } else {
            glView->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
        }
    }

#if AX_DEBUG
    director->setDisplayStats(true);
#endif

    director->setAnimationInterval(1.0 / 60);

    auto *scene = TitleScene::scene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    AudioEngine::pauseAll();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    AudioEngine::resumeAll();
}

bool AppDelegate::isLongScreen(float w, float h)
{
    float longSize = std::max(w, h);
    float shortSize = std::min(w, h);
    return (longSize / shortSize) > 1.6f;
}
