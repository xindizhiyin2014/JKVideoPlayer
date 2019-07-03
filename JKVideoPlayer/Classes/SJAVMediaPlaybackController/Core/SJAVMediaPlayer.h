//
//  SJAVMediaPlayer.h
//  Pods
//
//  Created by BlueDancer on 2019/4/9.
//

#import "SJAVMediaPlaybackDefines.h"

NS_ASSUME_NONNULL_BEGIN
@interface SJAVMediaPlayer : AVPlayer<SJAVMediaPlayerProtocol>

- (void)replaceCurrentURL:(NSURL *)url;

- (void)replaceCurrentURL:(NSURL *)url specifyStartTime:(NSTimeInterval)specifyStartTime;
- (void)replaceCurrentAsset:(AVAsset *)asset;

- (void)replaceCurrentAsset:(AVAsset *)asset specifyStartTime:(NSTimeInterval)specifyStartTime;

@end
NS_ASSUME_NONNULL_END
