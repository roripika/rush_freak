#include "AppDelegate.h"

#include "TitleScene.h"
#include "audio/AudioEngine.h"

using namespace ax;

namespace {
constexpr int kPortraitWidth = 640;
constexpr int kPortraitHeight = 960;
constexpr int kLongPortraitHeight = 1136;
} // namespace

AppDelegate::AppDelegate() = default;
AppDelegate::~AppDelegate() = default;

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
            kPortraitWidth,
            isLong ? kLongPortraitHeight : kPortraitHeight,
            ResolutionPolicy::SHOW_ALL);
    }
    else
    {
        glView->setDesignResolutionSize(
            isLong ? kLongPortraitHeight : kPortraitHeight,
            kPortraitWidth,
            ResolutionPolicy::SHOW_ALL);
    }

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
