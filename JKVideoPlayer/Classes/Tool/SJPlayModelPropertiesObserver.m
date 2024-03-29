//
//  SJPlayModelPropertiesObserver.m
//  SJVideoPlayerAssetCarrier
//
//  Created by 畅三江 on 2018/6/29.
//  Copyright © 2018年 SanJiang. All rights reserved.
//

#import "SJPlayModelPropertiesObserver.h"
#import <objc/message.h>
#import <UIKit/UIKit.h>
#import "SJIsAppeared.h"
#if __has_include(<SJUIKit/SJRunLoopTaskQueue.h>)
#import <SJUIKit/SJRunLoopTaskQueue.h>
#else
#import "SJRunLoopTaskQueue.h"
#endif

#if __has_include(<SJUIKit/NSObject+SJObserverHelper.h>)
#import <SJUIKit/NSObject+SJObserverHelper.h>
#else
#import "NSObject+SJObserverHelper.h"
#endif

NS_ASSUME_NONNULL_BEGIN
@interface SJPlayModelPropertiesObserver()
@property (nonatomic, strong) id<SJPlayModel> playModel;
@property (nonatomic, assign) CGPoint beforeOffset;
@property (nonatomic, assign) BOOL isAppeared;
@property (nonatomic, strong) SJRunLoopTaskQueue *taskQueue;
@property (nonatomic, assign) BOOL isScrolling;
@end

@implementation SJPlayModelPropertiesObserver

+ (instancetype)initWithPlayModel:(__kindof SJPlayModel *)playModel {
    NSParameterAssert(playModel);
    
    SJPlayModelPropertiesObserver *observer = [[self alloc] init];
    if (observer) {
        observer.playModel = playModel;
        observer.taskQueue = SJRunLoopTaskQueue.queue(@"SJPlayModelObserverRunLoopTaskQueue").delay(3);
        if ( [playModel isMemberOfClass:[SJPlayModel class]] ) {
            observer.isAppeared = YES;
        }
        else {
            [observer _observeProperties];
        }
        
        [observer refreshAppearState];
    }
    return observer;

}

- (void)_observeProperties {
    if ( [_playModel isKindOfClass:[SJUITableViewCellPlayModel class]] ) {
        SJUITableViewCellPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.tableView];
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewCellPlayModel class]] ) {
        SJUICollectionViewCellPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.collectionView];
    }
    else if ( [_playModel isKindOfClass:[SJUITableViewHeaderViewPlayModel class]] ) {
        SJUITableViewHeaderViewPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.tableView];
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUITableViewHeaderViewPlayModel class]] ) {
        SJUICollectionViewNestedInUITableViewHeaderViewPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.collectionView];
        [self _observeScrollView:playModel.tableView];
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUITableViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUITableViewCellPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.collectionView];
        [self _observeScrollView:playModel.tableView];
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUICollectionViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUICollectionViewCellPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.collectionView];
        [self _observeScrollView:playModel.rootCollectionView];
    }
    else if ( [_playModel isKindOfClass:[SJUITableViewHeaderFooterViewPlayModel class]] ) {
        SJUITableViewHeaderFooterViewPlayModel *playModel = _playModel;
        [self _observeScrollView:playModel.tableView];
    }
}

static NSString *kContentOffset = @"contentOffset";
static NSString *kState = @"state";
- (void)_observeScrollView:(UIScrollView *)scrollView {
    if ( !scrollView ) return;
    if ( ![scrollView isKindOfClass:[UIScrollView class]] ) return;
    [scrollView sj_addObserver:self forKeyPath:kContentOffset context:&kContentOffset];
    [scrollView.panGestureRecognizer sj_addObserver:self forKeyPath:kState context:&kState];
}

- (void)observeValueForKeyPath:(nullable NSString *)keyPath
                      ofObject:(nullable id)object
                        change:(nullable NSDictionary<NSKeyValueChangeKey,id> *)change
                       context:(nullable void *)context {
    if ( &kContentOffset == context ) {
        __weak typeof(self) _self = self;
        _taskQueue.empty().enqueue(^{
            [_self _scrollViewDidScroll:object];
        });
    }
    else if ( &kState == context ) {
        [self _panGestureStateDidChange:object];
    }
}

- (void)_panGestureStateDidChange:(UIPanGestureRecognizer *)pan {
    if ( !pan ) return;
    UIGestureRecognizerState state = pan.state;
    BOOL isTouchedTableView = NO;
    BOOL isTouchedCollectionView = NO;
    switch ( state ) {
        case UIGestureRecognizerStateChanged: return;
        case UIGestureRecognizerStatePossible: return;
        case UIGestureRecognizerStateBegan: {
            if ( [pan.view isKindOfClass:[UITableView class]] ) {
                _isTouchedTablView = YES;
                isTouchedTableView = YES;
            }
            else if ( [pan.view isKindOfClass:[UICollectionView class]] ) {
                _isTouchedCollectionView = YES;
                isTouchedCollectionView = YES;
            }
        }
            break;
        case UIGestureRecognizerStateEnded:
        case UIGestureRecognizerStateFailed:
        case UIGestureRecognizerStateCancelled: {
            if ( [pan.view isKindOfClass:[UITableView class]] ) {
                _isTouchedTablView = NO;
                isTouchedTableView = YES;
            }
            else if ( [pan.view isKindOfClass:[UICollectionView class]] ) {
                _isTouchedCollectionView = NO;
                isTouchedCollectionView = YES;
            }
        }
            break;
    }
    
    if ( isTouchedTableView ) {
        if ( [self.delegate respondsToSelector:@selector(observer:userTouchedTableView:)] ) {
            [self.delegate observer:self userTouchedTableView:_isTouchedTablView];
        }
    }
    else if ( isTouchedCollectionView ) {
        if ( [self.delegate respondsToSelector:@selector(observer:userTouchedCollectionView:)] ) {
            [self.delegate observer:self userTouchedCollectionView:_isTouchedCollectionView];
        }
    }
}

- (BOOL)_isAppearedInTheScrollingView:(UIScrollView *)scrollView {
    return sj_isAppeared2(_playModel.playerSuperview, scrollView);
}

- (void)_scrollViewDidScroll:(UIScrollView *)scrollView {
    if ( !scrollView ) return;
    if ( CGPointEqualToPoint(_beforeOffset, scrollView.contentOffset) ) return;
    
    ///
    /// Thanks @loveuqian
    /// https://github.com/changsanjiang/SJVideoPlayer/issues/62
    ///
    if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUITableViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUITableViewCellPlayModel *playModel = _playModel;
        if ( scrollView == playModel.tableView ) {
            [self _observeScrollView:playModel.collectionView];
        }
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUICollectionViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUICollectionViewCellPlayModel *playModel = _playModel;
        if ( scrollView == playModel.rootCollectionView ) {
            [self _observeScrollView:playModel.collectionView];
        }
    }
    
    self.isAppeared = [self _isAppearedInTheScrollingView:scrollView];
    _beforeOffset = scrollView.contentOffset;
}

@synthesize isAppeared = _isAppeared;
- (void)setIsAppeared:(BOOL)isAppeared {
    if ( isAppeared == _isAppeared ) return;
    _isAppeared = isAppeared;
    if ( isAppeared ) {
        if ( [self.delegate respondsToSelector:@selector(playerWillAppearForObserver:superview:)] ) {
            [self.delegate playerWillAppearForObserver:self superview:_playModel.playerSuperview];
        }
    }
    else {
        if ( [self.delegate respondsToSelector:@selector(playerWillDisappearForObserver:)] ) {
            [self.delegate playerWillDisappearForObserver:self];
        }
    }
}

- (BOOL)isPlayInTableView {
    return _playModel.isPlayInTableView;
}

- (BOOL)isPlayInCollectionView {
    return _playModel.isPlayInCollectionView;
}

- (void)refreshAppearState {
    _isAppeared = NO;
    if ( [_playModel isMemberOfClass:[SJPlayModel class]] ) {
        self.isAppeared = YES;
        return;
    }
    
    UIScrollView *superview = sj_getScrollView(_playModel);
    if ( !superview ) {
        self.isAppeared = NO;
        return;
    }
    self.isAppeared = [self _isAppearedInTheScrollingView:superview];
}

- (BOOL)isScrolling {
    if ( [_playModel isKindOfClass:[SJUITableViewCellPlayModel class]] ) {
        SJUITableViewCellPlayModel *playModel = _playModel;
        return playModel.tableView.isDragging || playModel.tableView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewCellPlayModel class]] ) {
        SJUICollectionViewCellPlayModel *playModel = _playModel;
        return playModel.collectionView.isDragging || playModel.collectionView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUITableViewHeaderViewPlayModel class]] ) {
        SJUITableViewHeaderViewPlayModel *playModel = _playModel;
        return playModel.tableView.isDragging || playModel.tableView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUITableViewHeaderViewPlayModel class]] ) {
        SJUICollectionViewNestedInUITableViewHeaderViewPlayModel *playModel = _playModel;
        return playModel.collectionView.isDragging || playModel.collectionView.isDecelerating ||
        playModel.tableView.isDragging || playModel.tableView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUITableViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUITableViewCellPlayModel *playModel = _playModel;
        return playModel.collectionView.isDragging || playModel.collectionView.isDecelerating ||
        playModel.tableView.isDragging || playModel.tableView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUICollectionViewNestedInUICollectionViewCellPlayModel class]] ) {
        SJUICollectionViewNestedInUICollectionViewCellPlayModel *playModel = _playModel;
        return playModel.collectionView.isDragging || playModel.collectionView.isDecelerating ||
        playModel.rootCollectionView.isDragging || playModel.rootCollectionView.isDecelerating;
    }
    else if ( [_playModel isKindOfClass:[SJUITableViewHeaderFooterViewPlayModel class]] ) {
        SJUITableViewHeaderFooterViewPlayModel *playModel = _playModel;
        return playModel.tableView.isDragging || playModel.tableView.isDecelerating;
    }
    return NO;
}
@end
NS_ASSUME_NONNULL_END
