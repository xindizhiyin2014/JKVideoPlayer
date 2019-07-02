//
//  SJFlipTransitionManagerDefines.h
//  Pods
//
//  Created by BlueDancer on 2018/12/31.
//

#ifndef SJFlipTransitionManagerProtocol_h
#define SJFlipTransitionManagerProtocol_h
#import <UIKit/UIKit.h>
@protocol SJFlipTransitionManagerObserver;

typedef NS_ENUM(NSUInteger,SJViewFlipTransition) {
    SJViewFlipTransition_Identity,
    SJViewFlipTransition_Horizontally, // 水平翻转
};

typedef NS_ENUM(NSUInteger,SJFlipTransitionState) {
    SJFlipTransitionStateStart,
    SJFlipTransitionStateEnd,
};


NS_ASSUME_NONNULL_BEGIN
@protocol SJFlipTransitionManager <NSObject>
- (instancetype)initWithTarget:(__strong UIView *)target;
- (id<SJFlipTransitionManagerObserver>)getObserver;

@property (nonatomic, assign,readonly) SJFlipTransitionState state;
@property (nonatomic, assign) NSTimeInterval duration;

@property (nonatomic) SJViewFlipTransition flipTransition;
- (void)setFlipTransition:(SJViewFlipTransition)t animated:(BOOL)animated;
- (void)setFlipTransition:(SJViewFlipTransition)t animated:(BOOL)animated completionHandler:(void(^_Nullable)(id<SJFlipTransitionManager> mgr))completionHandler;

+ (instancetype)new  NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end


@protocol SJFlipTransitionManagerObserver <NSObject>
@property (nonatomic, copy, nullable) void(^flipTransitionDidStartExeBlock)(id<SJFlipTransitionManager> mgr);
@property (nonatomic, copy, nullable) void(^flipTransitionDidStopExeBlock)(id<SJFlipTransitionManager> mgr);
@end
NS_ASSUME_NONNULL_END
#endif /* SJFlipTransitionManagerProtocol_h */
