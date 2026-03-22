//
//  NativeTweet.h
//  number_ten
//
//  Created by roripika on 2014/08/24.
//
//

#ifndef number_ten_NativeTweet_h
#define number_ten_NativeTweet_h

class NativeTweet
{
public:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void openTweetDialog(const char* tweet);
#endif
    
};

#endif
