//
//  SJPlayerGestureControlDefines.h
//  Pods
//
//  Created by 畅三江 on 2019/1/3.
//

#ifndef SJPlayerGestureControlProtocol_h
#define SJPlayerGestureControlProtocol_h
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger,SJPlayerGestureType) {
    SJPlayerGestureType_SingleTap,
    SJPlayerGestureType_DoubleTap,
    SJPlayerGestureType_Pan,
    SJPlayerGestureType_Pinch,
};

typedef NS_ENUM(NSUInteger,SJPlayerDisabledGestures) {
    SJPlayerDisabledGestures_None,
    SJPlayerDisabledGestures_SingleTap = 1 << 0,
    SJPlayerDisabledGestures_DoubleTap = 1 << 1,
    SJPlayerDisabledGestures_Pan = 1 << 2,
    SJPlayerDisabledGestures_Pinch = 1 << 3,
    SJPlayerDisabledGestures_All = SJPlayerDisabledGestures_SingleTap |
    SJPlayerDisabledGestures_DoubleTap |
    SJPlayerDisabledGestures_Pan |
    SJPlayerDisabledGestures_Pinch,
    
    SJPlayerDisabledGestures_Pan_H = 1 << 4, // 水平方向
    SJPlayerDisabledGestures_Pan_V = 1 << 5, // 垂直方向
};

typedef NS_ENUM(NSUInteger,SJPanGestureMovingDirection) {
    SJPanGestureMovingDirection_H,
    SJPanGestureMovingDirection_V,
};

typedef NS_ENUM(NSUInteger,SJPanGestureTriggeredPosition) {
    SJPanGestureTriggeredPosition_Left,
    SJPanGestureTriggeredPosition_Right,
};

typedef NS_ENUM(NSUInteger,SJPanGestureRecognizerState) {
    SJPanGestureRecognizerStateBegan,
    SJPanGestureRecognizerStateChanged,
    SJPanGestureRecognizerStateEnded,
};


@protocol SJPlayerGestureControl <NSObject>
- (instancetype)initWithTargetView:(__weak UIView *)view;

@property (nonatomic, weak, readonly, nullable) UIView *targetView;
@property (nonatomic, copy, nullable) BOOL(^gestureRecognizerShouldTrigger)(id<SJPlayerGestureControl> control, SJPlayerGestureType type, CGPoint location);
@property (nonatomic, copy, nullable) void(^singleTapHandler)(id<SJPlayerGestureControl> control, CGPoint location);
@property (nonatomic, copy, nullable) void(^doubleTapHandler)(id<SJPlayerGestureControl> control, CGPoint location);
@property (nonatomic, copy, nullable) void(^panHandler)(id<SJPlayerGestureControl> control, SJPanGestureTriggeredPosition position, SJPanGestureMovingDirection direction, SJPanGestureRecognizerState state, CGPoint translate);
@property (nonatomic, copy, nullable) void(^pinchHandler)(id<SJPlayerGestureControl> control, CGFloat scale);

@property (nonatomic, assign) SJPlayerDisabledGestures disabledGestures;
- (void)cancelGesture:(SJPlayerGestureType)type;
- (UIGestureRecognizerState)stateOfGesture:(SJPlayerGestureType)type;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, assign, readonly) SJPanGestureMovingDirection movingDirection;
@property (nonatomic, assign, readonly) SJPanGestureTriggeredPosition triggeredPosition;
@end

NS_ASSUME_NONNULL_END

#endif /* SJPlayerGestureControlProtocol_h */
