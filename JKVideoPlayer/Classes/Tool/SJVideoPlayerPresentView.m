//
//  SJVideoPlayerPresentView.m
//  SJVideoPlayerProject
//
//  Created by BlueDancer on 2017/11/29.
//  Copyright © 2017年 SanJiang. All rights reserved.
//

#import "SJVideoPlayerPresentView.h"
#import <JKUIHelper/JKViewProtocol.h>
NS_ASSUME_NONNULL_BEGIN
@interface SJVideoPlayerPresentView ()<JKViewProtocol>
{
    BOOL _isHidden;
    BOOL _isDelayed;
}
@end

@implementation SJVideoPlayerPresentView

@synthesize placeholderImageView = _placeholderImageView;

#ifdef SJ_MAC
- (void)dealloc {
    NSLog(@"%d - %s", (int)__LINE__, __func__);
}
#endif

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self initSubViews];
    }
    return self;
}

- (void)initSubViews{
    self.backgroundColor = [UIColor blackColor];
    self.placeholderImageView.frame = self.bounds;
    [self hiddenPlaceholderAnimated:NO delay:0];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    if (self.layoutSubviewsExeBlock) {
        self.layoutSubviewsExeBlock(self);
    }
}

- (BOOL)placeholderImageViewIsHidden {
    return _isHidden;
}

- (void)showPlaceholderAnimated:(BOOL)animated {
    if ( _isDelayed )
        [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(_hiddenPlaceholderAnimated:) object:nil];
    if ( !_isHidden ) return; _isHidden = NO;
    if ( animated ) {
        [UIView animateWithDuration:0.4 animations:^{
            self->_placeholderImageView.alpha = 1;
        }];
    }
    else {
        _placeholderImageView.alpha = 1;
    }
}

- (void)hiddenPlaceholderAnimated:(BOOL)animated delay:(NSTimeInterval)secs {
    if ( _isDelayed )
        [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(_hiddenPlaceholderAnimated:) object:nil];
    if ( _isHidden ) return; _isHidden = YES;
    if ( secs == 0 ) {
        [self _hiddenPlaceholderAnimated:@(animated)];
    }
    else {
        [self performSelector:@selector(_hiddenPlaceholderAnimated:) withObject:@(animated) afterDelay:secs];
        _isDelayed = YES;
    }
}

- (void)_hiddenPlaceholderAnimated:(NSNumber *)animated {
    if ( [animated boolValue] ) {
        [UIView animateWithDuration:0.4 animations:^{
            self->_placeholderImageView.alpha = 0.001;
        }];
    }
    else {
        _placeholderImageView.alpha = 0.001;
    }
    _isDelayed = NO;
}


#pragma mark - - - - lazyLoad - - - -
- (UIImageView *)placeholderImageView {
    if (!_placeholderImageView) {
        _placeholderImageView = [UIImageView new];
        _placeholderImageView.contentMode = UIViewContentModeScaleAspectFill;
        _placeholderImageView.clipsToBounds = YES;
        _placeholderImageView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [self addSubview:_placeholderImageView];
    }
    return _placeholderImageView;
}

@end
NS_ASSUME_NONNULL_END
