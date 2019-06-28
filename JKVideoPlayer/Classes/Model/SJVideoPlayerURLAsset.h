//
//  SJVideoPlayerURLAsset.h
//  SJVideoPlayerProject
//
//  Created by 畅三江 on 2018/1/29.
//  Copyright © 2018年 SanJiang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SJPlayModel.h"
#import "SJMediaPlaybackControllerDefines.h"

@protocol SJVideoPlayerURLAssetObserver;

NS_ASSUME_NONNULL_BEGIN

@interface SJVideoPlayerURLAsset : NSObject<SJMediaModelProtocol>

@property (nonatomic, strong, readonly, nullable) SJVideoPlayerURLAsset *originAsset;
@property (nonatomic, assign) NSTimeInterval playableLimit;///< 限制播放时间, `可用于试看`. 例如试看5分钟;默认为0, 即不限制
@property (nonatomic, assign) NSTimeInterval specifyStartTime;
@property (nonatomic, strong) SJPlayModel *playModel;
@property (nonatomic, assign, readonly) BOOL isM3u8;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)initWithURL:(NSURL *)url;

+ (instancetype)initWithURL:(NSURL *)url specifyStartTime:(NSTimeInterval)specifyStartTime;

+ (instancetype)initWithURL:(NSURL *)url playModel:(__kindof SJPlayModel *)playModel;

+ (instancetype)initWithURL:(NSURL *)url specifyStartTime:(NSTimeInterval)specifyStartTime playModel:(__kindof SJPlayModel *)playModel;

- (instancetype)initWithOtherAsset:(SJVideoPlayerURLAsset *)otherAsset playModel:(nullable __kindof SJPlayModel *)playModel;

- (id<SJVideoPlayerURLAssetObserver>)getObserver;

@end

@protocol SJVideoPlayerURLAssetObserver <NSObject>
@property (nonatomic, copy, nullable) void(^playModelDidChangeExeBlock)(SJVideoPlayerURLAsset *asset);
@end

NS_ASSUME_NONNULL_END
