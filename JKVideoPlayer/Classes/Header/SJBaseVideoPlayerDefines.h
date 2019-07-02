//
//  SJBaseVideoPlayerDefines.h
//  Pods
//
//  Created by 畅三江 on 2019/1/5.
//

#ifndef SJBaseVideoPlayerDefines_h
#define SJBaseVideoPlayerDefines_h
#import "SJVideoPlayerPlayStatusDefines.h"

@protocol SJReachability, SJPlayStatusObserver;
@class SJVideoPlayerURLAsset;

NS_ASSUME_NONNULL_BEGIN
@protocol SJBaseVideoPlayer <NSObject>

- (id<SJPlayStatusObserver>)getPlayStatusObserver;

@property (nonatomic, strong, null_resettable) id<SJReachability> reachability;
@property (nonatomic, strong, nullable) SJVideoPlayerURLAsset *URLAsset;
@property (nonatomic, assign) NSTimeInterval delayToAutoRefreshWhenPlayFailed;

- (void)refresh;

@property (nonatomic, assign ,readonly) SJVideoPlayerPlayStatus playStatus;
@property (nonatomic, assign ,readonly) SJVideoPlayerPausedReason pausedReason;
@property (nonatomic, assign ,readonly) SJVideoPlayerInactivityReason inactivityReason;
@property (nonatomic, strong, readonly, nullable) NSError *error;

@end
NS_ASSUME_NONNULL_END
#endif /* SJBaseVideoPlayerDefines_h */
