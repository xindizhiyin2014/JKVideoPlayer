//
//  SJPlayerAutoplayConfig.h
//  Masonry
//
//  Created by BlueDancer on 2018/7/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@protocol SJPlayerAutoplayDelegate;

typedef NS_ENUM(NSUInteger, SJAutoplayScrollAnimationType) {
    SJAutoplayScrollAnimationTypeNone,
    SJAutoplayScrollAnimationTypeTop,
    SJAutoplayScrollAnimationTypeMiddle,
};

typedef NS_ENUM(NSUInteger,SJAutoplayPosition) {
    SJAutoplayPositionTop,
    SJAutoplayPositionMiddle,
};

@interface SJPlayerAutoplayConfig : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)configWithPlayerSuperviewTag:(NSInteger)playerSuperviewTag
                            autoplayDelegate:(id<SJPlayerAutoplayDelegate>)autoplayDelegate;

/// 滚动的动画类型
/// default is .Middle;
@property (nonatomic, assign) SJAutoplayScrollAnimationType animationType;
/// default is .Middle;
@property (nonatomic, assign) SJAutoplayPosition autoplayPosition;

@property (nonatomic, assign, readonly) NSInteger playerSuperviewTag;
@property (nonatomic, weak, nullable, readonly) id<SJPlayerAutoplayDelegate> autoplayDelegate;

@end

@protocol SJPlayerAutoplayDelegate <NSObject>

- (void)sj_playerNeedPlayNewAssetAtIndexPath:(NSIndexPath *)indexPath;

@end
NS_ASSUME_NONNULL_END
