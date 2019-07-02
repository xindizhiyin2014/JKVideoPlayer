//
//  SJPlayStatusObserver.m
//  Pods
//
//  Created by BlueDancer on 2019/4/10.
//

#import "SJPlayStatusObserver.h"
#if __has_include(<SJUIKit/NSObject+SJObserverHelper.h>)
#import <SJUIKit/NSObject+SJObserverHelper.h>
#else
#import "NSObject+SJObserverHelper.h"
#endif

NS_ASSUME_NONNULL_BEGIN
@implementation SJPlayStatusObserver
@synthesize playStatusDidChangeExeBlock;// = _playStatusDidChangeExeBlock;
+ (instancetype)initWithPlayer:(id<SJBaseVideoPlayer>)player {
    SJPlayStatusObserver *observer = [[self alloc] init];
    if (observer) {
       [(id)player sj_addObserver:observer forKeyPath:@"playStatus"];
    }
    return observer;
    
}

- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable SJBaseVideoPlayer *)object change:(nullable NSDictionary<NSKeyValueChangeKey,id> *)change context:(nullable void *)context {
    if (self.playStatusDidChangeExeBlock ){
       self.playStatusDidChangeExeBlock(object);
    }
}
@end
NS_ASSUME_NONNULL_END
