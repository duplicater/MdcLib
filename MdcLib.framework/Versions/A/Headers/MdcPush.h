//
//  MdcPush.h
//  MdcLib
//
//  Created by Nguyen Hoa on 8/31/16.
//  Copyright © 2016 MdcLib. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//---------------------------------------------------------------------------------------
// SHPushNotificationDelegate Protocol
//---------------------------------------------------------------------------------------

/**
 * Protocol to be implemented by push notification clients. All methods are optional.
 */
@protocol SHPushNotificationDelegate<NSObject>

@optional

/**
 * Called when an alert notification is received in the foreground.
 * @param alertMessage a simple string to be displayed as an alert
 */
- (void)displayNotificationAlert:(NSString *)alertMessage;

/**
 * Called when an alert notification is received in the foreground with additional localization info.
 * @param alertDict a dictionary containing the alert and localization info
 */
- (void)displayLocalizedNotificationAlert:(NSDictionary *)alertDict;

/**
 * Called when a push notification is received in the foreground with a sound associated
 * @param soundFilename The sound file to play or `default` for the standard notification sound.
 *        This file must be included in the application bundle.
 */
- (void)playNotificationSound:(NSString *)soundFilename;

/**
 * Called when a push notification is received in the foreground with a badge number.
 * @param badgeNumber The badge number to display
 */
- (void)handleBadgeUpdate:(NSInteger)badgeNumber;

/**
 * Called when a push notification is received while the app is running in the foreground.
 * Overridden by receivedForegroundNotification:fetchCompletionHandler.
 *
 * @param notification The notification dictionary.
 */
- (void)receivedForegroundNotification:(NSDictionary *)notification;

/**
 * Called when a push notification is received while the app is running in the foreground
 * for applications with the "remote-notification" background mode.
 *
 * @param notification The notification dictionary.
 * @param completionHandler Should be called with a UIBackgroundFetchResult as soon as possible, so the system can accurately estimate its power and data cost.
 */
- (void)receivedForegroundNotification:(NSDictionary *)notification
                fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 * Called when a push notification is received while the app is running in the background
 * for applications with the "remote-notification" background mode.
 * Overridden by receivedBackgroundNotification:fetchCompletionHandler.
 *
 * @param notification The notification dictionary.
 */
- (void)receivedBackgroundNotification:(NSDictionary *)notification;

/**
 * Called when a push notification is received while the app is running in the background
 * for applications with the "remote-notification" background mode.
 *
 * @param notification The notification dictionary.
 * @param completionHandler Should be called with a UIBackgroundFetchResult as soon as possible, so the system can accurately estimate its power and data cost.
 */
- (void)receivedBackgroundNotification:(NSDictionary *)notification
                fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 * Called when the app is started or resumed because a user opened a notification.
 * Overridden by launchedFromNotification:fetchCompletionHandler.
 *
 * @param notification The notification dictionary.
 */
- (void)launchedFromNotification:(NSDictionary *)notification;

/**
 * Called when the app is started or resumed because a user opened a notification
 * for applications with the "remote-notification" background mode.
 *
 * @param notification The notification dictionary.
 * @param completionHandler Should be called with a UIBackgroundFetchResult as soon as possible, so the system can accurately estimate its power and data cost.
 */
- (void)launchedFromNotification:(NSDictionary *)notification
          fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 * Called when the app is started from a user notification action button with foreground activation mode.
 *
 * @param notification The notification dictionary.
 * @param identifier The user notification action identifier.
 * @param completionHandler Should be called as soon as possible.
 */
- (void)launchedFromNotification:(NSDictionary *)notification
                actionIdentifier:(NSString *)identifier
               completionHandler:(void (^)())completionHandler;


/**
 * Called when the app is started from a user notification action button with background activation mode.
 *
 * @param notification The notification dictionary.
 * @param identifier The user notification action identifier.
 * @param completionHandler Should be called as soon as possible.
 */
- (void)receivedBackgroundNotification:(NSDictionary *)notification
                      actionIdentifier:(NSString *)identifier
                     completionHandler:(void (^)())completionHandler;


- (void)onRegisterNotificationToken:(NSString *)deviceToken;

@end

//---------------------------------------------------------------------------------------
// MdcPush Class
//---------------------------------------------------------------------------------------
@interface MdcPush : NSObject

/**
 * Set a delegate that implements the SHPushNotificationDelegate protocol.
 */
@property (nonatomic, weak, nullable) id<SHPushNotificationDelegate> pushNotificationDelegate;

/**
 * User Notification types this app will request from APNS. Changes to this value
 * will not take effect the next time the app registers with
 * updateRegistration.
 *
 * Defaults to alert, sound and badge.
 */
@property (nonatomic, assign) UIUserNotificationType userNotificationTypes;

/**
 * Custom user notification categories. MdcLib default user notification
 * categories will be unaffected by this field.
 *
 * Changes to this value will not take effect the next time the app registers
 * with updateRegistration.
 */
@property (nonatomic, strong) NSSet *userNotificationCategories;

@property (nonatomic, strong) NSSet *allUserNotificationCategories;

/**
 * Factory method to create a push instance.
 * @return A new push instance.
 */
+ (instancetype)pushInstance;

///---------------------------------------------------------------------------------------
/// @name Autobadge
///---------------------------------------------------------------------------------------

/**
 * Sets the badge number on the device and on the Urban Airship server.
 *
 * @param badgeNumber The new badge number
 */
- (void)setBadgeNumber:(NSInteger)badgeNumber;

/**
 * Resets the badge to zero (0) on both the device and on Urban Airships servers. This is a
 * convenience method for `setBadgeNumber:0`.
 */
- (void)resetBadge;

///---------------------------------------------------------------------------------------
/// @name AppDelegate hooks
///---------------------------------------------------------------------------------------

/**
 * Handle incoming push notifications. This method will record push conversions, parse the notification
 * and call the appropriate methods on your delegate.
 *
 * @param notification The notification payload, as passed to your application delegate.
 * @param state The application state at the time the notification was received.
 */
- (void)appReceivedRemoteNotification:(NSDictionary *)notification
                     applicationState:(UIApplicationState)state;

/**
 * Handle incoming push notifications. This method will record push conversions, parse the notification
 * and call the appropriate methods on your delegate.
 *
 * @param notification The notification payload, as passed to your application delegate.
 * @param state The application state at the time the notification was received.
 * @param completionHandler Should be called with a UIBackgroundFetchResult as soon as possible, so the system can accurately estimate its power and data cost.
 */
- (void)appReceivedRemoteNotification:(NSDictionary *)notification
                     applicationState:(UIApplicationState)state
               fetchCompletionHandler:(nullable void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 * Handle device token registration. Associates the
 * token with the channel and update the channel registration.
 *
 * Add a `SHRegistrationDelegate` to received success and failure callbacks.
 *
 * @param token The device token to register.
 */
- (void)appRegisteredForRemoteNotificationsWithDeviceToken:(NSData *)token;

/**
 * Handles user notification settings registration.
 */
- (void)appRegisteredUserNotificationSettings;

/**
 * Handle interactive notification actions.
 *
 * @param identifier The identifier of the button that was triggered.
 * @param notification The notification payload, as passed to your application delegate.
 * @param state The application state at the time the notification was received.
 * @param completionHandler The completion handler.
 */
- (void)appReceivedActionWithIdentifier:(NSString *)identifier
                           notification:(NSDictionary *)notification
                       applicationState:(UIApplicationState)state
                      completionHandler:(void (^)())completionHandler;

/**
 * Handle interactive notification actions with response info.
 *
 * @param identifier The identifier of the button that was triggered.
 * @param notification The notification payload, as passed to your application delegate.
 * @param responseInfo The response info, as passed to your application delegate.
 * @param state The application state at the time the notification was received.
 * @param completionHandler The completion handler.
 */
- (void)appReceivedActionWithIdentifier:(NSString *)identifier
                           notification:(NSDictionary *)notification
                           responseInfo:(nullable NSDictionary *)responseInfo
                       applicationState:(UIApplicationState)state
                      completionHandler:(void (^)())completionHandler;
@end

NS_ASSUME_NONNULL_END
