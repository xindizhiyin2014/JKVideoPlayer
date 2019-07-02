//
//  SJBaseVideoPlayerAutoRefreshController.h
//  Pods
//
//  Created by BlueDancer on 2019/3/4.
//

#import <Foundation/Foundation.h>
#import "SJBaseVideoPlayerDefines.h"

NS_ASSUME_NONNULL_BEGIN
@interface SJBaseVideoPlayerAutoRefreshController : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)initWithPlayer:(__weak id<SJBaseVideoPlayer>)player;
- (void)cancel;
@end
NS_ASSUME_NONNULL_END
