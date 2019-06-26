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
- (instancetype)initWithURL:(NSURL *)URL specifyStartTime:(NSTimeInterval)specifyStartTime playModel:(__kindof SJPlayModel *)playModel;
- (instancetype)initWithURL:(NSURL *)URL specifyStartTime:(NSTimeInterval)specifyStartTime;
- (instancetype)initWithURL:(NSURL *)URL playModel:(__kindof SJPlayModel *)playModel;
- (instancetype)initWithURL:(NSURL *)URL;

@property (nonatomic, strong, readonly, nullable) SJVideoPlayerURLAsset *originAsset;
- (instancetype)initWithOtherAsset:(SJVideoPlayerURLAsset *)otherAsset playModel:(nullable __kindof SJPlayModel *)playModel;

/// - v2.4.5 新增
/// 限制播放时间, `可用于试看`. 例如试看5分钟
/// 默认为0, 即不限制
/// default value is 0.0
@property (nonatomic) NSTimeInterval playableLimit;
@property (nonatomic) NSTimeInterval specifyStartTime;

@property (nonatomic, strong, null_resettable) SJPlayModel *playModel;
- (id<SJVideoPlayerURLAssetObserver>)getObserver;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@property (nonatomic, readonly) BOOL isM3u8;
@end


@protocol SJVideoPlayerURLAssetObserver <NSObject>
@property (nonatomic, copy, nullable) void(^playModelDidChangeExeBlock)(SJVideoPlayerURLAsset *asset);
@end

NS_ASSUME_NONNULL_END
