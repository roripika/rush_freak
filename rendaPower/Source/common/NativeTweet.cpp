#include "axmol.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID)
#include "NativeTweet.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#define JNICLASSNAME "jp/nagohiyo/number_ten/number_ten"
#define TWEET "tweet"
 
using namespace ax;
void NativeTweet::openTweetDialog(const char* $tweet){
    JniMethodInfo methodInfo;
    if(JniHelper::getStaticMethodInfo(methodInfo , JNICLASSNAME , TWEET , "(Ljava/lang/String;)V")){
        jstring str = methodInfo.env->NewStringUTF($tweet);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID , methodInfo.methodID , str);
        methodInfo.env->DeleteLocalRef(str);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
#endif
