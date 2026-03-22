#include "SmorkManager.h"

using namespace ax;

bool SmorkManager::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}
