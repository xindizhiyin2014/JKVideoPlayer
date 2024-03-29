//
//  SJVideoPlayerPlayStatusDefines.h
//  SJVideoPlayerProject
//
//  Created by BlueDancer on 2017/11/29.
//  Copyright © 2017年 SanJiang. All rights reserved.
//

#ifndef SJVideoPlayerPlayStatusDefines_h
#define SJVideoPlayerPlayStatusDefines_h
@class SJBaseVideoPlayer;

NS_ASSUME_NONNULL_BEGIN
/**
 当前播放的状态

 - SJVideoPlayerPlayStatusUnknown:      未播放任何资源时的状态
 - SJVideoPlayerPlayStatusPrepare:      准备播放一个资源
 - SJVideoPlayerPlayStatusReadyToPlay:  准备就绪, 可以播放
 - SJVideoPlayerPlayStatusPlaying:      播放中
 - SJVideoPlayerPlayStatusPaused:       暂停状态, 请通过`SJVideoPlayerPausedReason`, 查看暂停原因
 - SJVideoPlayerPlayStatusInactivity:   不活跃状态, 请通过`SJVideoPlayerInactivityReason`, 查看暂停原因
 */
typedef NS_ENUM(NSUInteger, SJVideoPlayerPlayStatus) {
    SJVideoPlayerPlayStatusUnknown,
    SJVideoPlayerPlayStatusPrepare,
    SJVideoPlayerPlayStatusReadyToPlay,
    SJVideoPlayerPlayStatusPlaying,
    SJVideoPlayerPlayStatusPaused,
    SJVideoPlayerPlayStatusInactivity,
};

/**
 暂停的理由

 - SJVideoPlayerPausedReasonBuffering:   正在缓冲
 - SJVideoPlayerPausedReasonPause:       被暂停
 - SJVideoPlayerPausedReasonSeeking:     正在跳转(调用seekToTime:时)
 */
typedef NS_ENUM(NSUInteger, SJVideoPlayerPausedReason) {
    SJVideoPlayerPausedReasonUnknown,
    SJVideoPlayerPausedReasonBuffering,
    SJVideoPlayerPausedReasonPause,
    SJVideoPlayerPausedReasonSeeking,
};

/**
 不活跃的原因
 
 - SJVideoPlayerInactivityReasonPlayEnd:    播放完毕
 - SJVideoPlayerInactivityReasonPlayFailed: 播放失败
 - SJVideoPlayerInactivityReasonNotReachableAndPlaybackStalled: 无网并且缓冲为空, 无法继续播放
 */
typedef NS_ENUM(NSUInteger, SJVideoPlayerInactivityReason) {
    SJVideoPlayerInactivityReasonUnknown,
    SJVideoPlayerInactivityReasonPlayEnd,
    SJVideoPlayerInactivityReasonPlayFailed,
    SJVideoPlayerInactivityReasonNotReachableAndPlaybackStalled
};


//Playback type (LIVE, VOD, FILE).
typedef NS_ENUM(NSUInteger,SJMediaPlaybackType) {
    SJMediaPlaybackTypeUnknown,
    SJMediaPlaybackTypeLIVE,
    SJMediaPlaybackTypeVOD,
    SJMediaPlaybackTypeFILE
};


@protocol SJPlayStatusObserver <NSObject>
@property (nonatomic, copy, nullable) void(^playStatusDidChangeExeBlock)(__kindof SJBaseVideoPlayer *player);
@end

NS_ASSUME_NONNULL_END
#endif /* SJVideoPlayerPlayStatusDefines_h */
