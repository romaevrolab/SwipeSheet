//
//  SwipeSheetViewController.h
//

#import <UIKit/UIKit.h>

/// SwipeSheetLimit is the limit that reached the SwipeSheetViewController.
typedef NS_ENUM(NSUInteger, SwipeSheetLimit) {
    SwipeSheetLimitTop,
    SwipeSheetLimitBottom
};

/// Orientation in which the view controller overturned. There are only portrait and landscape orientations.
typedef NS_ENUM(NSUInteger, SwipeSheetOrientation) {
    SwipeSheetOrientationLandscape,
    SwipeSheetOrientationPortrait
};

@class SwipeSheetViewController;

/**
 The delegate of a SwipeSheetViewController object must adopt the SwipeSheetViewControllerDelegate protocol. Optional methods of the protocol allow the delegate to manage gestures, animations, and events such as changing the orientation and reaching the limit.
 */
@protocol SwipeSheetViewControllerDelegate <NSObject>

@optional

/// Change top offset for view
- (CGFloat)needsVerticalTopLimitForSwipeSheetView:(SwipeSheetViewController *)swipeSheet;

/// Change bottom offset for view
- (CGFloat)needsVerticalBottomLimitForSwipeSheetView:(SwipeSheetViewController *)swipeSheet;


/**
 Tells the delegate when user drags the SwipeSheetViewController.
 The delegate typically implements this method to obtain the change in content offset from scrollView and draw the affected portion of the content view.
 @param swipeSheet The SwipeSheetViewController object.
 */
- (void)swipeSheetDragged:(SwipeSheetViewController *)swipeSheet;

/**
 Tells the delegate when the limits of the SwipeSheetViewController reached.
 
 @param swipeSheet The SwipeSheetViewController object.
 @param limit Parameter substantially object limit.
 */
- (void)swipeSheet:(SwipeSheetViewController *)swipeSheet
       hasReachedLimit:(SwipeSheetLimit)limit;

/**
 Tells the delegate when the SwipeSheet is going to play the animation. If you use this delegate method, you must return blocks of animation and completion.

 @param swipeSheet The SwipeSheetViewController object.
 @param animation A block object containing the changes to commit to the views. This parameter must not be NULL.
 @param completion A block object to be executed when the animation sequence ends. This parameter must not be NULL.
 */
- (void)swipeSheet:(SwipeSheetViewController *)swipeSheet
           willAnimate:(void (^)(void))animation
            completion:(void (^)(BOOL finished))completion;

/**
 Tells the delegate when the orientation of the SwipeSheetViewController changes.
 
 You can obtain the new orientation by getting the value of the orientation parameter.
 
 @param swipeSheet The SwipeSheetViewController object.
 @param orientation Substantially object orientation.
 */
- (void)swipeSheet:(SwipeSheetViewController *)swipeSheet
  didChangeOrientation:(SwipeSheetOrientation)orientation;

@end

/**
 SwipeSheet is a a simple, easy to integrate solution for presenting UIViewController or any view in bottom or top sheet. We handle all the hard work for you - transitions, gestures, taps and more are all automatically provided by the library. Styling, however, is intentionally left out, allowing you to integrate your own design language with ease.
 */
@interface SwipeSheetViewController: UIViewController

/**
 The delegate of the swipe sheet object.
 The delegate must adopt the SwipeSheetViewControllerDelegate protocol. The SwipeSheetViewController class, which does not retain the delegate, invokes each protocol method the delegate implements.
 */
@property (nonatomic, weak, nullable) id <SwipeSheetViewControllerDelegate> delegate;

/// You can call this block and get the height of the SwipeSheet
@property (nonatomic, copy) void (^swipeSheetChangesHeightBlock)(CGFloat height, SwipeSheetViewController *sheet);

/// The property that says that the view is expanded to the maximum size or at the minimaze. Setter animically expands or minimazes the SwipeSheet view.
@property (nonatomic, assign, getter=isFullSize) BOOL fullSize;

/// You can assign this control any scrolling view with your custom view for the correct work of dragging.
@property (nonatomic, strong) UIScrollView *observedScrollView;

/// You can turn gestures on or off.
- (void)setGestureEnabled:(BOOL)enabled;

/// It is animated to change the view to the maximum size if YES or the minimum if NO.
- (void)animateViewToFullSize:(BOOL)fullSize;

/// Add your custom view to the controller.
- (void)addCustomView:(UIView *)view;

/// You can show a SwipeSheet view on your view controller.
- (void)presentSwipeSheetOnViewController:(UIViewController *)viewController;

/// You can hide the SwipeSheet view animatively if YES or no animation if NO
- (void)dismissSwipeSheetAnimated:(BOOL)animated completion:(void (^)(void))completion;

@end
