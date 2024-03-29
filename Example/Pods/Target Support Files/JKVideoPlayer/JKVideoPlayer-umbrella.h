#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "SJBaseVideoPlayerDefines.h"
#import "SJBaseVideoPlayerStatisticsDefines.h"
#import "SJControlLayerAppearManagerDefines.h"
#import "SJDeviceVolumeAndBrightnessManagerDefines.h"
#import "SJFitOnScreenManagerDefines.h"
#import "SJFlipTransitionManagerDefines.h"
#import "SJFloatSmallViewControllerDefines.h"
#import "SJMediaPlaybackControllerDefines.h"
#import "SJModalViewControlllerManagerDefines.h"
#import "SJPlayerBufferStatus.h"
#import "SJPlayerGestureControlDefines.h"
#import "SJReachabilityDefines.h"
#import "SJRotationManagerDefines.h"
#import "SJVideoPlayerControlLayerProtocol.h"
#import "SJVideoPlayerMacro.h"
#import "SJVideoPlayerPlayStatusDefines.h"
#import "SJPlayerAutoplayConfig.h"
#import "SJPlayModel.h"
#import "SJVideoPlayerURLAsset.h"
#import "AVAsset+SJAVMediaExport.h"
#import "SJAVMediaDefinitionLoader.h"
#import "SJAVMediaMainPresenter.h"
#import "SJAVMediaPlaybackDefines.h"
#import "SJAVMediaPlayer.h"
#import "SJAVMediaPlayerLoader.h"
#import "SJAVMediaPlaybackController.h"
#import "SJBaseVideoPlayer+PlayStatus.h"
#import "SJBaseVideoPlayer.h"
#import "SJBorderLineView.h"
#import "SJDeviceBrightnessView.h"
#import "SJDeviceVolumeAndBrightnessManagerResourceLoader.h"
#import "SJDeviceVolumeAndBrightnessManager.h"
#import "SJPrompt.h"
#import "SJPromptConfig.h"
#import "SJRotationManager.h"
#import "SJVCRotationManager.h"
#import "NSTimer+SJAssetAdd.h"
#import "SJBaseVideoPlayerAutoRefreshController.h"
#import "SJBaseVideoPlayerStatistics.h"
#import "SJControlLayerAppearStateManager.h"
#import "SJFitOnScreenManager.h"
#import "SJFlipTransitionManager.h"
#import "SJFloatSmallViewController.h"
#import "SJIsAppeared.h"
#import "SJModalViewControlllerManager.h"
#import "SJPlayerGestureControl.h"
#import "SJPlayerView.h"
#import "SJPlayModelPropertiesObserver.h"
#import "SJPlayStatusObserver.h"
#import "SJReachability.h"
#import "SJTimerControl.h"
#import "SJVideoPlayerPresentView.h"
#import "SJVideoPlayerRegistrar.h"
#import "UIView+SJVideoPlayerAdd.h"
#import "UIScrollView+ListViewAutoplaySJAdd.h"

FOUNDATION_EXPORT double JKVideoPlayerVersionNumber;
FOUNDATION_EXPORT const unsigned char JKVideoPlayerVersionString[];

