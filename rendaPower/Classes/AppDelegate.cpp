#include "AppDelegate.h"

#include <algorithm>

#include "TitleScene.h"
#include "audio/AudioEngine.h"

using namespace ax;

namespace {
constexpr int kShortEdge = 640;
constexpr int kStandardLongEdge = 960;
constexpr int kExtendedLongEdge = 1136;

int registerAllPackages()
{
    return 0;
}
} // namespace

AppDelegate::AppDelegate() = default;
AppDelegate::~AppDelegate() = default;

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    glContextAttrs.vsync = true;
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto* director = Director::getInstance();
    auto* glView = director->getOpenGLView();
    if (glView == nullptr)
    {
        glView = GLViewImpl::create("Rush Freak");
        director->setOpenGLView(glView);
    }

    const auto frameSize = glView->getFrameSize();
    const bool isPortrait = frameSize.width < frameSize.height;
    const bool isLong = isLongScreen(frameSize.width, frameSize.height);

    if (isPortrait)
    {
        glView->setDesignResolutionSize(
            kShortEdge,
            isLong ? kExtendedLongEdge : kStandardLongEdge,
            ResolutionPolicy::SHOW_ALL);
    }
    else
    {
        glView->setDesignResolutionSize(
            isLong ? kExtendedLongEdge : kStandardLongEdge,
            kShortEdge,
            ResolutionPolicy::SHOW_ALL);
    }

    registerAllPackages();

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0F / 60.0F);
    director->runWithScene(TitleScene::scene());

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    auto* director = Director::getInstance();
    director->stopAnimation();
    audio::AudioEngine::pauseAll();
}

void AppDelegate::applicationWillEnterForeground()
{
    auto* director = Director::getInstance();
    director->startAnimation();
    audio::AudioEngine::resumeAll();
}

bool AppDelegate::isLongScreen(float width, float height) const
{
    const float longSize = std::max(width, height);
    const float shortSize = std::min(width, height);
    return shortSize > 0.0F && (longSize / shortSize) > 1.6F;
}
