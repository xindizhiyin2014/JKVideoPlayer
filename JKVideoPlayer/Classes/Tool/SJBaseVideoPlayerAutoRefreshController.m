//
//  SJBaseVideoPlayerAutoRefreshController.m
//  Pods
//
//  Created by BlueDancer on 2019/3/4.
//

#import "SJBaseVideoPlayerAutoRefreshController.h"
#import "SJReachabilityDefines.h"
#import "SJVideoPlayerRegistrar.h"
#if __has_include(<SJUIKit/NSObject+SJObserverHelper.h>)
#import <SJUIKit/NSObject+SJObserverHelper.h>
#else
#import "NSObject+SJObserverHelper.h"
#endif

#import "SJVideoPlayerMacro.h"


NS_ASSUME_NONNULL_BEGIN
@interface SJBaseVideoPlayerAutoRefreshController ()
@property (nonatomic, weak, readonly, nullable) id<SJBaseVideoPlayer> player;
@property (nonatomic, strong, readonly) id<SJPlayStatusObserver> playStatusObserver;
@property (nonatomic, strong, readonly) id<SJReachabilityObserver> reachabilityObserver;
@property (nonatomic, strong, readonly) SJVideoPlayerRegistrar *registrar;
@end

@implementation SJBaseVideoPlayerAutoRefreshController
+ (instancetype)initWithPlayer:(__weak id<SJBaseVideoPlayer>)player {
    SJBaseVideoPlayerAutoRefreshController *refreshController = [[self alloc] init];
    if (refreshController) {
       refreshController->_player = player;
        refreshController->_playStatusObserver = [player getPlayStatusObserver];
        refreshController->_reachabilityObserver = [player.reachability getObserver];
        refreshController->_registrar = [SJVideoPlayerRegistrar new];
        
        @weakify(refreshController);
        refreshController->_playStatusObserver.playStatusDidChangeExeBlock = ^(__kindof SJBaseVideoPlayer * _Nonnull player) {
            @strongify(refreshController);
            [refreshController _startOrCancel];
        };
        
        refreshController->_reachabilityObserver.networkStatusDidChangeExeBlock = ^(id<SJReachability> r, SJNetworkStatus status) {
            @strongify(refreshController);
            [refreshController _startOrCancel];
        };
        
        refreshController->_registrar.willEnterForeground = ^(SJVideoPlayerRegistrar * _Nonnull registrar) {
           @strongify(refreshController);
            [refreshController _startOrCancel];
        };
        
        refreshController->_registrar.didEnterBackground = ^(SJVideoPlayerRegistrar * _Nonnull registrar) {
            @strongify(refreshController);
            [refreshController _startOrCancel];
        };
        
        [(id)player sj_addObserver:refreshController forKeyPath:@"URLAsset"];
    }
    return refreshController;
    
}

- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable id)object change:(nullable NSDictionary<NSKeyValueChangeKey,id> *)change context:(nullable void *)context {
    if ( [keyPath isEqualToString:@"URLAsset"] ) {
        [self _cancel];
    }
}

- (void)_startOrCancel {
    if ( 0 == _player.delayToAutoRefreshWhenPlayFailed ) {
        [self _cancel];
        return;
    }
    
    [self _cancel];
    BOOL playFailed = _player.error != nil;
    if ( !playFailed ||
         _player.reachability.networkStatus == SJNetworkStatus_NotReachable ||
         _registrar.state == SJVideoPlayerAppState_Background ) {
        return;
    }
    
    if ( playFailed ) {
        [self _start];
    }
}

- (void)_start {
    [self performSelector:@selector(_refresh) withObject:nil afterDelay:_player.delayToAutoRefreshWhenPlayFailed];
}

- (void)_cancel {
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
}

- (void)cancel {
    [self _cancel];
}

- (void)_refresh {
    if ( [self _needRefresh] ) {
#ifdef DEBUG
        puts("SJBaseVideoPlayer: 当前状态为播放失败, 正在尝试重新播放!");
#endif
        [_player refresh];
    }
}

- (BOOL)_needRefresh {
    switch ( _player.playStatus ) {
        case SJVideoPlayerPlayStatusUnknown: break;
        case SJVideoPlayerPlayStatusPrepare:
        case SJVideoPlayerPlayStatusReadyToPlay:
        case SJVideoPlayerPlayStatusPlaying:
        case SJVideoPlayerPlayStatusPaused:
            return NO;
        case SJVideoPlayerPlayStatusInactivity: {
            if ( _player.inactivityReason != SJVideoPlayerInactivityReasonPlayFailed &&
                 _player.inactivityReason != SJVideoPlayerInactivityReasonNotReachableAndPlaybackStalled )
                return NO;
        }
            break;
    }
    
    return
    _player.error != nil &&
    _player.reachability.networkStatus != SJNetworkStatus_NotReachable &&
    _registrar.state != SJVideoPlayerAppState_Background ;
}
@end
NS_ASSUME_NONNULL_END
