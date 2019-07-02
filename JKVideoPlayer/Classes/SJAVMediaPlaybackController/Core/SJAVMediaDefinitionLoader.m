//
//  SJAVMediaDefinitionLoader.m
//  Pods
//
//  Created by BlueDancer on 2019/4/10.
//

#import "SJAVMediaDefinitionLoader.h"
#if __has_include(<SJUIKit/NSObject+SJObserverHelper.h>)
#import <SJUIKit/NSObject+SJObserverHelper.h>
#else
#import "NSObject+SJObserverHelper.h"
#endif
#import "SJVideoPlayerMacro.h"

NS_ASSUME_NONNULL_BEGIN
@interface SJAVMediaDefinitionLoader ()
@property (nonatomic, strong) id<SJMediaModelProtocol> media;
@property (nonatomic, strong, nullable) id<SJAVMediaPlayerProtocol> player;
@property (nonatomic, copy, nullable) void(^handler)(SJAVMediaDefinitionLoader *loader, AVPlayerItemStatus status);
@end

@implementation SJAVMediaDefinitionLoader
- (void)dealloc {
#ifdef DEBUG
    NSLog(@"%d - %s", (int)__LINE__, __func__);
#endif
}

+ (instancetype)initWithMedia:(id<SJMediaModelProtocol>)media handler:(void (^)(SJAVMediaDefinitionLoader * _Nonnull, AVPlayerItemStatus))handler {
    SJAVMediaDefinitionLoader *loader = [[self alloc] init];
    if (loader) {
        
       loader->_media = media;
        loader->_handler = handler;
        [loader sj_observeWithNotification:SJAVMediaItemStatusDidChangeNotification target:nil usingBlock:^(SJAVMediaDefinitionLoader *self, NSNotification * _Nonnull note) {
            id<SJAVMediaPlayerProtocol> player = note.object;
            if ( player == loader.player ) {
                [loader _playerItemStatusDidChange];
            }
        }];
        
        [SJAVMediaPlayerLoader loadPlayerForMedia:media completionHandler:^(id<SJMediaModelProtocol>  _Nonnull media, id<SJAVMediaPlayerProtocol>  _Nonnull player) {
            if ( !loader ) return;
            loader.player = player;
            [loader _playerItemStatusDidChange];
        }];
    }
    return loader;
}

- (void)_playerItemStatusDidChange {
    AVPlayerItemStatus status = [_player sj_getAVPlayerItemStatus];
    if (self.handler ){
        self.handler(self, status);
    }
}

@end
NS_ASSUME_NONNULL_END
