//
//  SJVideoPlayerURLAsset.m
//  SJVideoPlayerProject
//
//  Created by 畅三江 on 2018/1/29.
//  Copyright © 2018年 SanJiang. All rights reserved.
//

#import "SJVideoPlayerURLAsset.h"
#import <objc/message.h>
#if __has_include(<SJUIKit/NSObject+SJObserverHelper.h>)
#import <SJUIKit/NSObject+SJObserverHelper.h>
#else
#import "NSObject+SJObserverHelper.h"
#endif

NS_ASSUME_NONNULL_BEGIN
@interface SJVideoPlayerURLAssetObserver : NSObject<SJVideoPlayerURLAssetObserver>
- (instancetype)initWithAsset:(SJVideoPlayerURLAsset *)asset;
@end
@implementation SJVideoPlayerURLAssetObserver
@synthesize playModelDidChangeExeBlock = _playModelDidChangeExeBlock;

- (instancetype)initWithAsset:(SJVideoPlayerURLAsset *)asset {
    self = [super init];
    if (self) {
        [asset sj_addObserver:self forKeyPath:@"playModel"];
    }
    return self;
}

- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable id)object change:(nullable NSDictionary<NSKeyValueChangeKey,id> *)change context:(nullable void *)context {
    if ( _playModelDidChangeExeBlock ) _playModelDidChangeExeBlock(object);
}
@end

@interface SJVideoPlayerURLAsset()

@property (nonatomic, strong, readwrite, nullable) SJVideoPlayerURLAsset *originAsset;
@end

@implementation SJVideoPlayerURLAsset

+ (instancetype)initWithURL:(NSURL *)url{
    return [self initWithURL:url specifyStartTime:0];
}

+ (instancetype)initWithURL:(NSURL *)url specifyStartTime:(NSTimeInterval)specifyStartTime{
    return [self initWithURL:url specifyStartTime:specifyStartTime playModel:[SJPlayModel new]];
}

+ (instancetype)initWithURL:(NSURL *)url playModel:(__kindof SJPlayModel *)playModel{
    return [self initWithURL:url specifyStartTime:0 playModel:playModel];
}

+ (instancetype)initWithURL:(NSURL *)url specifyStartTime:(NSTimeInterval)specifyStartTime playModel:(__kindof SJPlayModel *)playModel{
    SJVideoPlayerURLAsset *asset = [[self alloc] init];
    asset.mediaURL = url;
    asset.specifyStartTime = specifyStartTime;
    asset->_playModel = playModel?:[SJPlayModel new];
    return asset;
}

- (instancetype)initWithOtherAsset:(SJVideoPlayerURLAsset *)otherAsset playModel:(nullable __kindof SJPlayModel *)playModel {
    
    SJVideoPlayerURLAsset *curr = otherAsset;
    while ( curr.originAsset != nil && curr != curr.originAsset ) {
        curr = curr.originAsset;
    }
    self.originAsset = curr;
    self.mediaURL = curr.mediaURL;
    _playModel = playModel?:[SJPlayModel new];
    return self;
} 
- (BOOL)isM3u8 {
    return [self.mediaURL.pathExtension containsString:@"m3u8"];
} 

- (id<SJVideoPlayerURLAssetObserver>)getObserver {
    return [[SJVideoPlayerURLAssetObserver alloc] initWithAsset:self];
}

@end

NS_ASSUME_NONNULL_END
