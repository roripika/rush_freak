#include "axmol.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "NativeCodeAstJni.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

using namespace ax;

// CLASS_NAMEの部分はJavaのクラス名となりますので、
// <スラッシュ区切りのpkgname>/NativeCodeAst のようにします
#define  CLASS_NAME "dev/axmol/app/NativeCodeAst"

void NativeCodeAstJni::showAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeCodeAstJni::hideAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeCodeAstJni::initAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "initAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
#endif
