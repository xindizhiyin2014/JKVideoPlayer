//
//  SJBaseVideoPlayer.h
//  SJBaseVideoPlayerProject
//
//  Created by BlueDancer on 2018/2/2.
//  Copyright © 2018年 SanJiang. All rights reserved.
//
//  GitHub:     https://github.com/changsanjiang/SJBaseVideoPlayer
//
//  Contact:    changsanjiang@gmail.com
//
//  QQGroup:    719616775
//

/**
 ------------------------
 *  PlayControl
 *  Network
 *  Prompt
 *  Time
 *  GestureControl
 *  ControlLayer
 *  Rotation
 *  Screenshot
 *  Export
 *  ScrollView
 *  ControlLayerProtocol
 -------------------------
 */

#import <UIKit/UIKit.h>
#import "SJPrompt.h"
#import "SJFitOnScreenManagerDefines.h"
#import "SJRotationManagerDefines.h"
#import "SJVideoPlayerControlLayerProtocol.h"
#import "SJControlLayerAppearManagerDefines.h"
#import "SJFlipTransitionManagerDefines.h"
#import "SJMediaPlaybackControllerDefines.h"
#import "SJPlayerGestureControlDefines.h"
#import "SJVideoPlayerURLAsset.h"
#import "SJDeviceVolumeAndBrightnessManagerDefines.h"
#import "SJModalViewControlllerManagerDefines.h"
#import "SJBaseVideoPlayerStatisticsDefines.h"
#import "SJFloatSmallViewControllerDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface SJBaseVideoPlayer : NSObject
+ (NSString *)version;
+ (instancetype)player;
- (instancetype)init;


// - View -

@property (nonatomic, strong, readonly) UIView *view;
@property (nonatomic, strong, null_resettable) AVLayerVideoGravity videoGravity;

@property (nonatomic, copy, nullable) void(^playStatusDidChangeExeBlock)(__kindof SJBaseVideoPlayer *player);
- (nullable __kindof UIViewController *)atViewController;

// - Control Layer Delegate -

@property (nonatomic, weak, nullable) id <SJVideoPlayerControlLayerDataSource> controlLayerDataSource;
@property (nonatomic, weak, nullable) id <SJVideoPlayerControlLayerDelegate> controlLayerDelegate;
@end


@interface SJBaseVideoPlayer (Placeholder)

// - Placeholder -

/// 初始化资源时, 可能会短暂黑屏, 建议设置一下占位图
@property (nonatomic, strong, readonly) UIImageView *placeholderImageView;

/// 播放器准备好显示时, 是否隐藏占位图
///
/// - 默认为YES
@property (nonatomic, assign) BOOL hiddenPlaceholderImageViewWhenPlayerIsReadyForDisplay;

/// 将要隐藏 placeholderImageView 时, 延迟多少秒才去隐藏
///
/// - 默认为0.8s
@property (nonatomic, assign) NSTimeInterval delayInSecondsForHiddenPlaceholderImageView;
@end


#pragma mark - 镜像翻转

@interface SJBaseVideoPlayer (VideoFlipTransition)
@property (nonatomic, strong, null_resettable) id<SJFlipTransitionManager> flipTransitionManager;

@property (nonatomic, assign, readonly) BOOL isFlipTransitioning;
@property (nonatomic, assign) SJViewFlipTransition flipTransition; // Animated.
- (void)setFlipTransition:(SJViewFlipTransition)t animated:(BOOL)animated;
- (void)setFlipTransition:(SJViewFlipTransition)t animated:(BOOL)animated completionHandler:(void(^_Nullable)(__kindof SJBaseVideoPlayer *player))completionHandler;

@property (nonatomic, copy, nullable) void(^flipTransitionDidStartExeBlock)(__kindof SJBaseVideoPlayer *player);
@property (nonatomic, copy, nullable) void(^flipTransitionDidStopExeBlock)(__kindof SJBaseVideoPlayer *player);
@end


#pragma mark - 时间

@interface SJBaseVideoPlayer (Time)

// - Time -

@property (nonatomic, assign, readonly) NSTimeInterval currentTime;
@property (nonatomic, assign, readonly) NSTimeInterval totalTime;
@property (nonatomic, strong, readonly) NSString *currentTimeStr;
@property (nonatomic, strong, readonly) NSString *totalTimeStr;

@property (nonatomic, copy, nullable) void(^playTimeDidChangeExeBlok)(__kindof SJBaseVideoPlayer *videoPlayer);
@property (nonatomic, copy, nullable) void(^playDidToEndExeBlock)(__kindof SJBaseVideoPlayer *player);

// - Progress -

@property (nonatomic, assign ,readonly) float progress;
@property (nonatomic, assign ,readonly) float bufferProgress;

- (NSString *)timeStringWithSeconds:(NSInteger)secs; // format: 00:00:00
@end




#pragma mark - 播放控制

@interface SJBaseVideoPlayer (PlayControl)<SJMediaPlaybackControllerDelegate>

@property (nonatomic, strong, null_resettable) id<SJMediaPlaybackController> playbackController;


// - Asset -

/// 资源
///
/// - 播放一个资源
/// - 使用URL及相关的视图信息进行初始化
@property (nonatomic, strong, nullable) SJVideoPlayerURLAsset *URLAsset;
/// asset`dealloc`时的回调
/// - 可以在这里做一些记录的工作. 如播放记录.
@property (nonatomic, copy, nullable) void(^assetDeallocExeBlock)(__kindof SJBaseVideoPlayer *videoPlayer);

// - Playback Type -

@property (nonatomic, assign ,readonly) SJMediaPlaybackType playbackType;

// - Playback Status -

/// 播放状态观察者
- (id<SJPlayStatusObserver>)getPlayStatusObserver; ///< 需要对它强引用, 否则观察者会被释放
@property (nonatomic, strong, readonly, nullable) NSError *error; ///< 播放失败时的错误

@property (nonatomic, assign, readonly) SJVideoPlayerPlayStatus playStatus; ///< 播放状态

@property (nonatomic, assign, readonly) SJVideoPlayerPausedReason pausedReason; ///< 暂停原因

@property (nonatomic, assign, readonly) SJVideoPlayerInactivityReason inactivityReason; ///< 不活跃原因


// - Play -

/// 刷新
- (void)refresh;

@property (nonatomic, assign) BOOL autoPlayWhenPlayStatusIsReadyToPlay; ///< 初始化完成后, 是否自动播放
/// 播放器是否可以执行`play`
///
/// - 当调用`play`时, 会回调该block, 如果返回YES, 则执行`play`方法, 否之.
/// - 如果该block == nil, 则调用`play`时, 默认为执行.
@property (nonatomic, copy, nullable) BOOL(^canPlayAnAsset)(__kindof SJBaseVideoPlayer *player);
/// 自动刷新, 播放失败时每隔多少秒刷新一次.
///
/// - 默认是0, 即不自动刷新
/// - 单位是秒
@property (nonatomic, assign) NSTimeInterval delayToAutoRefreshWhenPlayFailed;
/// 播放
- (void)play;
/// 切换`清晰度` (v1.6.5 新增)
/// - 切换当前播放的视频清晰度
- (void)switchVideoDefinition:(SJVideoPlayerURLAsset *)URLAsset;

/// 是否恢复播放, 进入前台时.
///
/// 正常情况下, 进入后台时, 播放器将会暂停. 此属性表示App进入前台后, 播放器是否恢复播放. 默认为NO.
@property (nonatomic, assign) BOOL resumePlaybackWhenAppDidEnterForeground;


// - Pause -

/// 关于后台播放视频, 引用自: https://juejin.im/post/5a38e1a0f265da4327185a26
///
/// 当您想在后台播放视频时:
/// 1. 需要设置 videoPlayer.pauseWhenAppDidEnterBackground = NO; (该值默认为YES, 即App进入后台默认暂停).
/// 2. 前往 `TARGETS` -> `Capability` -> enable `Background Modes` -> select this mode `Audio, AirPlay, and Picture in Picture`
@property (nonatomic,assign) BOOL pauseWhenAppDidEnterBackground;
/// 使暂停
- (void)pause;


// - Stop -

/// 使停止
- (void)stop;

/// 使停止, 并淡出
- (void)stopAndFadeOut;


// - Replay -

/// 是否重播过 - 当前的资源.
@property (nonatomic, assign, readonly, getter=isReplayed) BOOL replayed;
/// 重播
- (void)replay;


// - Seek To Time -

/// 是否可以调用 seekToTime:
@property (nonatomic, copy, nullable) BOOL(^canSeekToTime)(__kindof SJBaseVideoPlayer *player);
/// 跳转到指定位置播放
- (void)seekToTime:(NSTimeInterval)secs completionHandler:(void (^ __nullable)(BOOL finished))completionHandler;
- (void)seekToTime:(CMTime)time toleranceBefore:(CMTime)toleranceBefore toleranceAfter:(CMTime)toleranceAfter completionHandler:(void (^ __nullable)(BOOL finished))completionHandler;

// - Rate -

/// 调速
@property (nonatomic,assign) float rate;
/// 速率改变的回调
@property (nonatomic, copy, nullable) void(^rateDidChangeExeBlock)(__kindof SJBaseVideoPlayer *player);


// - Volume -


@property (nonatomic, getter=isMute) BOOL mute; ///< 是否静音🔇
@property (nonatomic, assign) float playerVolume;


/// 是否锁屏
@property (nonatomic, assign, getter=isLockedScreen) BOOL lockedScreen;
@end


#pragma mark - 设备 音量和亮度

@interface SJBaseVideoPlayer (DeviceVolumeAndBrightness)
@property (nonatomic, strong, null_resettable) id<SJDeviceVolumeAndBrightnessManager> deviceVolumeAndBrightnessManager;

@property (nonatomic, assign) float deviceVolume;
@property (nonatomic, assign) float deviceBrightness;

@property (nonatomic, assign) BOOL disableBrightnessSetting;
@property (nonatomic, assign) BOOL disableVolumeSetting;
@end


#pragma mark - 关于视图控制器

/// v1.3.0 新增
/// 请在适当的时候调用这些方法
@interface SJBaseVideoPlayer (ViewController)

/// You should call it when view did appear
- (void)vc_viewDidAppear; 
/// You should call it when view will disappear
- (void)vc_viewWillDisappear;
- (void)vc_viewDidDisappear;
- (BOOL)vc_prefersStatusBarHidden;
- (UIStatusBarStyle)vc_preferredStatusBarStyle;

/// The code is fixed, you can copy it directly to the view controller
/// 以下的代码都是固定的, 可以直接copy到视图控制器中
//
//- (void)viewDidAppear:(BOOL)animated {
//    [super viewDidAppear:animated];
//    [self.player vc_viewDidAppear];
//}
//
//- (void)viewWillDisappear:(BOOL)animated {
//    [super viewWillDisappear:animated];
//    [self.player vc_viewWillDisappear];
//}
//
//- (void)viewDidDisappear:(BOOL)animated {
//    [super viewDidDisappear:animated];
//    [self.player vc_viewDidDisappear];
//}
//
//- (BOOL)prefersStatusBarHidden {
//    return [self.player vc_prefersStatusBarHidden];
//}
//
//- (UIStatusBarStyle)preferredStatusBarStyle {
//    return [self.player vc_preferredStatusBarStyle];
//}
//
//- (BOOL)prefersHomeIndicatorAutoHidden {
//    return YES;
//}

/// 当调用`vc_viewWillDisappear`时, 将设置为YES
/// 当调用`vc_viewDidAppear`时, 将设置为NO
@property (nonatomic, assign) BOOL vc_isDisappeared;


/// v1.6.0 新增
/// 临时显示状态栏
/// Animatable. 可动画的
- (void)needShowStatusBar;

/// 临时隐藏状态栏
/// Animatable. 可动画的
- (void)needHiddenStatusBar;
@end




#pragma mark - Network

@interface SJBaseVideoPlayer (Network)
@property (nonatomic, strong, null_resettable) id<SJReachability> reachability;

/// 当前网速
@property (nonatomic, strong, readonly) NSString *networkSpeedStr;
@property (nonatomic, assign, readonly) SJNetworkStatus networkStatus;
@property (nonatomic, copy, nullable) void(^networkStatusDidChangeExeBlock)(__kindof SJBaseVideoPlayer *player);
@end





#pragma mark - 提示

@interface SJBaseVideoPlayer (Prompt)

/**
 prompt.update(^(SJPromptConfig * _Nonnull config) {
    config.cornerRadius = 4;                    // default cornerRadius.
    config.font = [UIFont systemFontOfSize:12]; // default font.
 });
 
 readonly.
 */
@property (nonatomic, strong, readonly) SJPrompt *prompt;

/**
 The middle of the player view shows the specified title. duration default is 1.0.

 @param title       prompt.
 */
- (void)showTitle:(NSString *)title;

/**
 The middle of the view shows the specified title.

 @param title       prompt.
 @param duration    prompt duration. duration if value set -1, prompt will always show.
 */
- (void)showTitle:(NSString *)title duration:(NSTimeInterval)duration;

- (void)showTitle:(NSString *)title duration:(NSTimeInterval)duration hiddenExeBlock:(void(^__nullable)(__kindof SJBaseVideoPlayer *player))hiddenExeBlock;

- (void)showAttributedString:(NSAttributedString *)attributedString duration:(NSTimeInterval)duration;

- (void)showAttributedString:(NSAttributedString *)attributedString duration:(NSTimeInterval)duration hiddenExeBlock:(void(^__nullable)(__kindof SJBaseVideoPlayer *player))hiddenExeBlock;

/**
 Hidden Prompt.
 */
- (void)hiddenTitle;

@end





#pragma mark - 手势
/**
 播放器的手势介绍:
 base video player 默认会存在四种手势, Single Tap, double Tap, Pan, Pinch.
 
 SingleTap
 单击手势
 当用户单击播放器时, 播放器会调用显示或隐藏控制层的相关代理方法. 见 `controlLayerDelegate`
 
 DoubleTap
 双击手势
 双击会触发暂停或播放的操作
 
 Pan
 移动手势
 当用户水平滑动时, 会触发控制层相应的代理方法. 见 `controlLayerDelegate`
 当用户垂直滑动时, 如果在屏幕左边, 则会触发调整亮度的操作, 并显示亮度提示视图. 如果在屏幕右边, 则会触发调整声音的操作, 并显示系统音量提示视图
 
 Pinch
 捏合手势
 当用户做放大或收缩触发该手势时, 会设置播放器显示模式`Aspect`或`AspectFill`.
 */
@interface SJBaseVideoPlayer (GestureControl)

@property (nonatomic, strong, null_resettable) id<SJPlayerGestureControl> gestureControl;

@property (nonatomic,assign) SJPlayerDisabledGestures disabledGestures;

@property (nonatomic, copy, nullable) BOOL(^gestureRecognizerShouldTrigger)(__kindof SJBaseVideoPlayer *player, SJPlayerGestureType type, CGPoint location);
@end





#pragma mark - 播放器控制层 显示/隐藏 控制

@interface SJBaseVideoPlayer (ControlLayer)

@property (nonatomic, strong, null_resettable) id<SJControlLayerAppearManager> controlLayerAppearManager;

@property (nonatomic, copy, nullable) BOOL(^canAutomaticallyDisappear)(__kindof SJBaseVideoPlayer *player);

/**
 When you want to appear the control layer, you should call this method to appear.
 This method will call the control layer delegate method.
 
 - (void)controlLayerNeedAppear:(__kindof SJBaseVideoPlayer *)videoPlayer;
 */
- (void)controlLayerNeedAppear;

/**
 When you want to disappear the control layer, you should call this method to disappear.
 This method will call the control layer delegate method.
 
 - (void)controlLayerNeedDisappear:(__kindof SJBaseVideoPlayer *)videoPlayer;
 */
- (void)controlLayerNeedDisappear;

@property (nonatomic, assign) BOOL disabledControlLayerAppearManager; // default value is NO.
@property (nonatomic, assign) BOOL controlLayerIsAppeared;
@property (nonatomic, assign) BOOL pausedToKeepAppearState;
@property (nonatomic, assign) BOOL controlLayerAutoAppearWhenAssetInitialized; // default value is NO.
@property (nonatomic, copy, nullable) void(^controlLayerAppearStateDidChangeExeBlock)(__kindof SJBaseVideoPlayer *player, BOOL state);
@end


/// v2.1.1 新增
@interface SJBaseVideoPlayer (ModalViewControlller)
@property (nonatomic, strong, null_resettable) id<SJModalViewControlllerManagerProtocol> modalViewControllerManager;
@property (nonatomic, assign) BOOL needPresentModalViewControlller;

- (void)presentModalViewControlller;
- (void)dismissModalViewControlller;
@end


// - Auto Manage Player View to Fit On Screen Or Rotation -

@interface SJBaseVideoPlayer (AutoManageViewToFitOnScreenOrRotation)
@property (nonatomic, assign) BOOL autoManageViewToFitOnScreenOrRotation; // default value is YES.
@end


// - Fit On Screen

/// 全屏或小屏, 但不触发旋转
/// v1.3.1 新增
@interface SJBaseVideoPlayer (FitOnScreen)
@property (nonatomic, strong, null_resettable) id<SJFitOnScreenManager> fitOnScreenManager;

/// Whether fullscreen or smallscreen, this method does not trigger rotation.
/// 全屏或小屏, 此方法不触发旋转
/// Animated
@property (nonatomic, assign, getter=isFitOnScreen) BOOL fitOnScreen;

/// Whether fullscreen or smallscreen, this method does not trigger rotation.
/// 全屏或小屏, 此方法不触发旋转
/// - animated : 是否动画
- (void)setFitOnScreen:(BOOL)fitOnScreen animated:(BOOL)animated;

/// Whether fullscreen or smallscreen, this method does not trigger rotation.
/// 全屏或小屏, 此方法不触发旋转
/// - animated : 是否动画
/// - completionHandler : 操作完成的回调
- (void)setFitOnScreen:(BOOL)fitOnScreen animated:(BOOL)animated completionHandler:(nullable void(^)(__kindof SJBaseVideoPlayer *player))completionHandler;

@property (nonatomic, assign) BOOL useFitOnScreenAndDisableRotation;
@property (nonatomic, copy, nullable) void(^fitOnScreenWillBeginExeBlock)(__kindof SJBaseVideoPlayer *player);
@property (nonatomic, copy, nullable) void(^fitOnScreenDidEndExeBlock)(__kindof SJBaseVideoPlayer *player);;
@end


// - Rotation -

@interface SJBaseVideoPlayer (Rotation)
/// Default is SJRotationManager. It only rotates the player view.
/// When you want to rotate the view controller, You can use the SJVCRotationManager.
/// 默认情况下, 播放器将只旋转播放界面, ViewController并不会旋转.
/// 当您想要旋转ViewController时, 可以采用此管理类进行旋转.
/// - 使用示例请看`SJVCRotationManager`第36行注释。
@property (nonatomic, strong, null_resettable) id<SJRotationManagerProtocol> rotationManager;

@property (nonatomic, copy, nullable) BOOL(^shouldTriggerRotation)(__kindof SJBaseVideoPlayer *player);

/**
 Autorotation. Animated.
 */
- (void)rotate;

/**
 Rotate to the specified orientation.
 
 @param orientation     Any value of SJOrientation.
 @param animated        Whether or not animation.
 */
- (void)rotate:(SJOrientation)orientation animated:(BOOL)animated;

/**
 Rotate to the specified orientation.
 
 @param orientation     Any value of SJOrientation.
 @param animated        Whether or not animation.
 @param block           The block invoked when player rotated.
 */
- (void)rotate:(SJOrientation)orientation animated:(BOOL)animated completion:(void (^ _Nullable)(__kindof SJBaseVideoPlayer *player))block;

@property (nonatomic, readonly) BOOL isFullScreen;
@property (nonatomic, readonly) BOOL isTransitioning;

@property (nonatomic) BOOL disableAutoRotation;
@property (nonatomic) NSTimeInterval rotationTime;
@property (nonatomic) SJOrientation orientation;
@property (nonatomic) SJAutoRotateSupportedOrientation supportedOrientation;
@property (nonatomic, copy, nullable) void(^viewWillRotateExeBlock)(__kindof SJBaseVideoPlayer *player, BOOL isFullScreen);
@property (nonatomic, copy, nullable) void(^viewDidRotateExeBlock)(__kindof SJBaseVideoPlayer *player, BOOL isFullScreen);
@property (nonatomic, readonly) UIInterfaceOrientation currentOrientation;
@end





#pragma mark - 截图

@interface SJBaseVideoPlayer (Screenshot)

// - Presentation Size -

@property (nonatomic, copy, nullable) void(^presentationSizeDidChangeExeBlock)(__kindof SJBaseVideoPlayer *videoPlayer);

@property (nonatomic, readonly) CGSize videoPresentationSize;


// - Screenshot -

- (UIImage * __nullable)screenshot;

- (void)screenshotWithTime:(NSTimeInterval)time
                completion:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, UIImage * __nullable image, NSError *__nullable error))block;

- (void)screenshotWithTime:(NSTimeInterval)time
                      size:(CGSize)size
                completion:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, UIImage * __nullable image, NSError *__nullable error))block;
@end





#pragma mark - 输出

@interface SJBaseVideoPlayer (Export)

/**
 export session.
 
 @param beginTime           unit is sec.
 @param endTime             unit is sec.
 @param presetName 	        default is `AVAssetExportPresetMediumQuality`.
 @param progressBlock       progressBlock
 @param completion 	        completion
 @param failure 	        failure
 */
- (void)exportWithBeginTime:(NSTimeInterval)beginTime
                    endTime:(NSTimeInterval)endTime
                 presetName:(nullable NSString *)presetName
                   progress:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, float progress))progressBlock
                 completion:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, NSURL *fileURL, UIImage *thumbnailImage))completion
                    failure:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, NSError *error))failure;

- (void)cancelExportOperation;

- (void)generateGIFWithBeginTime:(NSTimeInterval)beginTime
                        duration:(NSTimeInterval)duration
                        progress:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, float progress))progressBlock
                      completion:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, UIImage *imageGIF, UIImage *thumbnailImage, NSURL *filePath))completion
                         failure:(void(^)(__kindof SJBaseVideoPlayer *videoPlayer, NSError *error))failure;

- (void)cancelGenerateGIFOperation;

@end



#pragma mark - 在`tableView`或`collectionView`上播放

@interface SJBaseVideoPlayer (ScrollView)

/// 小浮窗控制
///
/// 默认不启用, 当需要开启时, 请设置`player.floatSmallViewController.enabled = YES;`
@property (nonatomic, strong, null_resettable) id<SJFloatSmallViewControllerProtocol> floatSmallViewController;

/// 当开启小浮窗控制时, 播放结束后, 会默认隐藏小浮窗
///
/// - default value is YES.
@property (nonatomic) BOOL autoDisappearFloatSmallView;

/// 滚动出去后, 是否暂停. 默认为YES
///
/// - default value is YES.
@property (nonatomic) BOOL pauseWhenScrollDisappeared;

/// 滚动进入时, 是否恢复播放. 默认为YES
///
/// - default values is YES.
@property (nonatomic) BOOL resumePlaybackWhenScrollAppeared;

/// 滚动出去后, 是否隐藏播放器视图. 默认为YES
///
/// - default value is YES.
@property (nonatomic) BOOL hiddenViewWhenScrollDisappeared;

/// 是否在 scrollView 中播放
///
/// Whether to play on scrollView.
@property (nonatomic, readonly) BOOL isPlayOnScrollView;

/// 播放器视图是否显示
///
/// Whether the player is appeared when playing on scrollView. Because scrollview may be scrolled.
@property (nonatomic, readonly) BOOL isScrollAppeared;

@property (nonatomic, copy, nullable) void(^playerViewWillAppearExeBlock)(__kindof SJBaseVideoPlayer *videoPlayer);
@property (nonatomic, copy, nullable) void(^playerViewWillDisappearExeBlock)(__kindof SJBaseVideoPlayer *videoPlayer);
@end



#pragma mark - 播放时长统计
@interface SJBaseVideoPlayer (Statistics)
// default value is NO.
@property (class, nonatomic, getter=isEnabledStatistics) BOOL enabledStatistics;
@property (class, nonatomic, strong, null_resettable) id<SJBaseVideoPlayerStatistics> statistics;
@property (nonatomic, strong, null_resettable) id<SJBaseVideoPlayerStatistics> statistics;
@end

NS_ASSUME_NONNULL_END
