#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MdcLibPeople.h"
#import "BaseMessage.h"
#import "MdcPush.h"


#if TARGET_OS_TV
    #define MDCLIB_TVOS_EXTENSION 1
#endif

#define MDCLIB_LIMITED_SUPPORT (defined(MDCLIB_APP_EXTENSION) || defined(MDCLIB_TVOS_EXTENSION))

@class    MdcPush, MdcLibPeople, MPSurvey;
@protocol MdcLibDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class
 MdcLib API.

 @abstract
 The primary interface for integrating MdcLib with your app.

 @discussion
 Use the MdcLib class to set up your project and track events in MdcLib
 Engagement. It now also includes a <code>people</code> property for accessing
 the MdcLib People API.

 <pre>
 // Initialize the API
 MdcLib *mdclib = [MdcLib sharedInstanceWithToken:@"YOUR TOKEN" appKey:@"YOUR APP KEY"];

 // Track an event in MdcLib Engagement
 [mdclib track:@"Button Clicked"];

 // Set properties on a user in MdcLib People
 [mdclib identify:@"CURRENT USER DISTINCT ID"];
 [mdclib.people set:@"Plan" to:@"Premium"];
 </pre>

 For more advanced usage, please see the <a
 href="https://mdclib.com/docs/integration-libraries/iphone">MdcLib iPhone
 Library Guide</a>.
 */
@interface MdcLib : NSObject

#pragma mark Properties

@property (nonatomic, assign) BOOL remoteNotificationBackgroundModeEnabled;

/*!
 @property
 
 @abstract
 Setting use/not use realtime for receiving message.
 
 @discussion
 Defaults to NO.
 */
@property (nonatomic, assign) BOOL enableRealtime;

/*!
 @property

 @abstract
 Accessor to the MdcLib People API object.

 @discussion
 See the documentation for MdcLibDelegate below for more information.
 */
@property (atomic, readonly, strong) MdcLibPeople *people;

/*!
 @property

 @abstract
 The distinct ID of the current user.

 @discussion
 A distinct ID is a string that uniquely identifies one of your users.
 Typically, this is the user ID from your database. By default, we'll use a
 hash of the MAC address of the device. To change the current distinct ID,
 use the <code>identify:</code> method.
 */
@property (atomic, readonly, copy) NSString *distinctId;

/*!
 @property

 @abstract
 Current user's name in MdcLib Streams.
 */
@property (nullable, atomic, copy) NSString *nameTag;

/*!
 @property

 @abstract
 The base URL used for MdcLib API requests.

 @discussion
 Useful if you need to proxy MdcLib requests. Defaults to
 https://mdc.vietid.net.
 */
@property (nonatomic, copy) NSString *serverURL;

/*!
 @property

 @abstract
 Flush timer's interval.

 @discussion
 Setting a flush interval of 0 will turn off the flush timer.
 */
@property (atomic) NSUInteger flushInterval;

/*!
 @property

 @abstract
 Control whether the library should flush data to MdcLib when the app
 enters the background.

 @discussion
 Defaults to YES. Only affects apps targeted at iOS 4.0, when background
 task support was introduced, and later.
 */
@property (atomic) BOOL flushOnBackground;

/*!
 @property

 @abstract
 Controls whether to show spinning network activity indicator when flushing
 data to the MdcLib servers.

 @discussion
 Defaults to YES.
 */
@property (atomic) BOOL showNetworkActivityIndicator;

/*!
 @property

 @abstract
 Controls whether to automatically check for surveys for the
 currently identified user when the application becomes active.

 @discussion
 Defaults to YES. Will fire a network request on
 <code>applicationDidBecomeActive</code> to retrieve a list of valid surveys
 for the currently identified user.
 */
@property (atomic) BOOL checkForSurveysOnActive;

/*!
 @property

 @abstract
 Controls whether to automatically show a survey for the
 currently identified user when the application becomes active.

 @discussion
 Defaults to YES. This will only show a survey if
 <code>checkForSurveysOnActive</code> is also set to YES, and the
 survey check retrieves at least 1 valid survey for the currently
 identified user.
 */
@property (atomic) BOOL showSurveyOnActive;

/*!
 @property
 
 @abstract
 Determines whether a valid survey is available to show to the user.
 
 @discussion
 If we haven't fetched the surveys yet, this will return NO. Otherwise
 it will return yes if there is at least one survey available.
 */
@property (atomic, readonly) BOOL isSurveyAvailable;

/*!
 @property
 
 @abstract
 Returns a list of available surveys. You can then call <code>showSurveyWithID:</code>
 and pass in <code>survey.ID</code>
 
 @discussion
 If we haven't fetched the surveys yet, this will return nil.
 */
@property (atomic, readonly) NSArray<MPSurvey *> *availableSurveys;

/*!
 @property

 @abstract
 Controls whether to automatically check for notifications for the
 currently identified user when the application becomes active.

 @discussion
 Defaults to YES. Will fire a network request on
 <code>applicationDidBecomeActive</code> to retrieve a list of valid notifications
 for the currently identified user.
 */
@property (atomic) BOOL checkForNotificationsOnActive;

/*!
 @property

 @abstract
 Controls whether to automatically check for A/B test variants for the
 currently identified user when the application becomes active.

 @discussion
 Defaults to YES. Will fire a network request on
 <code>applicationDidBecomeActive</code> to retrieve a list of valid variants
 for the currently identified user.
 */
@property (atomic) BOOL checkForVariantsOnActive;

/*!
 @property

 @abstract
 Controls whether to automatically check for and show in-app notifications
 for the currently identified user when the application becomes active.

 @discussion
 Defaults to YES.
 */
@property (atomic) BOOL showNotificationOnActive;

/*!
 @property
 
 @abstract
 Controls whether to automatically send the client IP Address as part of 
 event tracking. With an IP address, geo-location is possible down to neighborhoods
 within a city, although the MdcLib Dashboard will just show you city level location
 specificity. For privacy reasons, you may be in a situation where you need to forego
 effectively having access to such granular location information via the IP Address.
 
 @discussion
 Defaults to YES.
 */
@property (atomic) BOOL useIPAddressForGeoLocation;

/*!
 @property
 
 @abstract
 Controls whether to enable the visual A/B test designer on mdclib.com, you will 
 be unable to edit A/B tests with this disabled, however previously created A/B 
 tests and their variants will still be delivered.
 
 @discussion
 Defaults to NO.
 */
@property (atomic) BOOL enableABTestDesigner;

/*!
 @property

 @abstract
 Determines the time, in seconds, that a mini notification will remain on
 the screen before automatically hiding itself.

 @discussion
 Defaults to 6.0.
 */
@property (atomic) CGFloat miniNotificationPresentationTime;

/*!
 @property
 
 @abstract
 If set, determines the background color of mini notifications.

 @discussion
 If this isn't set, we default to either the color of the UINavigationBar of the top 
 UINavigationController that is showing when the notification is presented, the 
 UINavigationBar default color for the app or the UITabBar default color.
 */
@property (atomic, strong, nullable) UIColor *miniNotificationBackgroundColor;

/*!
 @property

 @abstract
 The a MdcLibDelegate object that can be used to assert fine-grain control
 over MdcLib network activity.

 @discussion
 Using a delegate is optional. See the documentation for MdcLibDelegate
 below for more information.
 */
@property (atomic, weak) id<MdcLibDelegate> delegate; // allows fine grain control over uploading (optional)

#pragma mark Tracking

/*!
 @method

 @abstract
 Initializes and returns a singleton instance of the API.

 @discussion
 If you are only going to send data to a single MdcLib project from your app,
 as is the common case, then this is the easiest way to use the API. This
 method will set up a singleton instance of the <code>MdcLib</code> class for
 you using the given project token. When you want to make calls to MdcLib
 elsewhere in your code, you can use <code>sharedInstance</code>.

 <pre>
 [MdcLib sharedInstance] track:@"Something Happened"]];
 </pre>

 If you are going to use this singleton approach,
 <code>sharedInstanceWithToken:</code> <b>must be the first call</b> to the
 <code>MdcLib</code> class, since it performs important initializations to
 the API.

 @param token        your token
 @param appKey       your project key
 */
+ (MdcLib *)sharedInstanceWithToken:(NSString *)token appKey:(NSString *)appKey;

/*!
 @method

 @abstract
 Initializes a singleton instance of the API, uses it to track launchOptions information,
 and then returns it.

 @discussion
 This is the preferred method for creating a sharedInstance with a mdclib
 like above. With the launchOptions parameter, MdcLib can track referral
 information created by push notifications.

 @param token           your token
 @param appKey          your project key
 @param launchOptions   your application delegate's launchOptions

 */
+ (MdcLib *)sharedInstanceWithToken:(NSString *)token appKey:(NSString *)appKey launchOptions:(nullable NSDictionary *)launchOptions;

/*!
 @method

 @abstract
 Returns the previously instantiated singleton instance of the API.

 @discussion
 The API must be initialized with <code>sharedInstanceWithToken:</code> before
 calling this class method.
 */
+ (MdcLib *)sharedInstance;

/*!
 @method

 @abstract
 Initializes an instance of the API with the given project token.

 @discussion
 Returns the a new API object. This allows you to create more than one instance
 of the API object, which is convenient if you'd like to send data to more than
 one MdcLib project from a single app. If you only need to send data to one
 project, consider using <code>sharedInstanceWithToken:</code>.

 @param apiToken        your project token
 @param appKey          your project key
 @param launchOptions   optional app delegate launchOptions
 @param flushInterval   interval to run background flushing
 */
- (instancetype)initWithToken:(NSString *)apiToken appKey:(NSString *)appKey launchOptions:(nullable NSDictionary *)launchOptions andFlushInterval:(NSUInteger)flushInterval;

/*!
 @method

 @abstract
 Initializes an instance of the API with the given project token.

 @discussion
 Supports for the old initWithToken method format but really just passes
 launchOptions to the above method as nil.

 @param apiToken        your project token
 @param appKey          your project key
 @param flushInterval   interval to run background flushing
 */
- (instancetype)initWithToken:(NSString *)apiToken appKey:(NSString *)appKey andFlushInterval:(NSUInteger)flushInterval;


/**
 * Returns the `MdcPush` instance. Used for configuring and managing push
 * notifications.
 *
 * @return The `MdcPush` instance.
 */
+ (null_unspecified MdcPush *)push;

/*!
 @property

 @abstract
 Sets the distinct ID of the current user.

 @discussion
 As of version 2.3.1, MdcLib will choose a default distinct ID based on
 whether you are using the AdSupport.framework or not.

 If you are not using the AdSupport Framework (iAds), then we use the
 <code>[UIDevice currentDevice].identifierForVendor</code> (IFV) string as the
 default distinct ID.  This ID will identify a user across all apps by the same
 vendor, but cannot be used to link the same user across apps from different
 vendors.

 If you are showing iAds in your application, you are allowed use the iOS ID
 for Advertising (IFA) to identify users. If you have this framework in your
 app, MdcLib will use the IFA as the default distinct ID. If you have
 AdSupport installed but still don't want to use the IFA, you can define the
 <code>MDCLIB_NO_IFA</code> preprocessor flag in your build settings, and
 MdcLib will use the IFV as the default distinct ID.

 If we are unable to get an IFA or IFV, we will fall back to generating a
 random persistent UUID.

 For tracking events, you do not need to call <code>identify:</code> if you
 want to use the default.  However, <b>MdcLib People always requires an
 explicit call to <code>identify:</code></b>. If calls are made to
 <code>set:</code>, <code>increment</code> or other <code>MdcLibPeople</code>
 methods prior to calling <code>identify:</code>, then they are queued up and
 flushed once <code>identify:</code> is called.

 If you'd like to use the default distinct ID for MdcLib People as well
 (recommended), call <code>identify:</code> using the current distinct ID:
 <code>[mdclib identify:mdclib.distinctId]</code>.

 @param distinctId string that uniquely identifies the current user
 */
- (void)identify:(NSString *)distinctId;


/*!
 @method
 
 @abstract
 Register User with Email or userID.
 
 @discussion
 Useful for identifying User
 
 @param email           Email of user
 @param userId          User ID of user
 */
- (void)registerUser:(NSString *)email userId:(NSString *)userId;


/*!
 @method
 
 @abstract
 Change Push notification settings.
 
 @discussion
 Useful for application to on/off notification

 */
- (void)changePushSettings;


/*!
 @method

 @abstract
 Tracks an event.

 @param event           event name
 */
- (void)track:(NSString *)event;


/*!
 @method

 @abstract
 Tracks an event with properties.

 @discussion
 Properties will allow you to segment your events in your MdcLib reports.
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code>NSArray</code>, <code>NSDictionary</code>, <code>NSDate</code> or
 <code>NSURL</code> objects. If the event is being timed, the timer will
 stop and be added as a property.

 @param event           event name
 @param properties      properties dictionary
 */
- (void)track:(NSString *)event properties:(nullable NSDictionary *)properties;


/*!
 @method
 
 @abstract
 Mask as read message.
 
 @discussion
 Useful for tracking message and sync state notification between multidevices
 
 @param mesg             BaseMessage return from callback data
 */
- (void)markAsRead:(BaseMessage *)mesg;


/*!
 @method

 @abstract
 Registers super properties, overwriting ones that have already been set.

 @discussion
 Super properties, once registered, are automatically sent as properties for
 all event tracking calls. They save you having to maintain and add a common
 set of properties to your events. Property keys must be <code>NSString</code>
 objects and values must be <code>NSString</code>, <code>NSNumber</code>,
 <code>NSNull</code>, <code>NSArray</code>, <code>NSDictionary</code>,
 <code>NSDate</code> or <code>NSURL</code> objects.

 @param properties      properties dictionary
 */
- (void)registerSuperProperties:(NSDictionary *)properties;

/*!
 @method

 @abstract
 Registers super properties without overwriting ones that have already been
 set.

 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code>NSArray</code>, <code>NSDictionary</code>, <code>NSDate</code> or
 <code>NSURL</code> objects.

 @param properties      properties dictionary
 */
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties;

/*!
 @method

 @abstract
 Registers super properties without overwriting ones that have already been set
 unless the existing value is equal to defaultValue.

 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code>NSArray</code>, <code>NSDictionary</code>, <code>NSDate</code> or
 <code>NSURL</code> objects.

 @param properties      properties dictionary
 @param defaultValue    overwrite existing properties that have this value
 */
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties defaultValue:(nullable id)defaultValue;

/*!
 @method

 @abstract
 Removes a previously registered super property.

 @discussion
 As an alternative to clearing all properties, unregistering specific super
 properties prevents them from being recorded on future events. This operation
 does not affect the value of other super properties. Any property name that is
 not registered is ignored.

 Note that after removing a super property, events will show the attribute as
 having the value <code>undefined</code> in MdcLib until a new value is
 registered.

 @param propertyName   array of property name strings to remove
 */
- (void)unregisterSuperProperty:(NSString *)propertyName;

/*!
 @method

 @abstract
 Clears all currently set super properties.
 */
- (void)clearSuperProperties;

/*!
 @method

 @abstract
 Returns the currently set super properties.
 */
- (NSDictionary *)currentSuperProperties;

/*!
 @method

 @abstract
 Starts a timer that will be stopped and added as a property when a
 corresponding event is tracked.

 @discussion
 This method is intended to be used in advance of events that have
 a duration. For example, if a developer were to track an "Image Upload" event
 she might want to also know how long the upload took. Calling this method
 before the upload code would implicitly cause the <code>track</code>
 call to record its duration.

 <pre>
 // begin timing the image upload
 [mdclib timeEvent:@"Image Upload"];

 // upload the image
 [self uploadImageWithSuccessHandler:^{

    // track the event
    [mdclib track:@"Image Upload"];
 }];
 </pre>

 @param event   a string, identical to the name of the event that will be tracked

 */
- (void)timeEvent:(NSString *)event;

/*!
 @method

 @abstract
 Clears all current event timers.
 */
- (void)clearTimedEvents;

/*!
 @method

 @abstract
 Clears all stored properties and distinct IDs. Useful if your app's user logs out.
 */
- (void)reset;

/*!
 @methodre

 @abstract
 Uploads queued data to the MdcLib server.

 @discussion
 By default, queued data is flushed to the MdcLib servers every minute (the
 default for <code>flushInterval</code>), and on background (since
 <code>flushOnBackground</code> is on by default). You only need to call this
 method manually if you want to force a flush at a particular moment.
 */
- (void)flush;

/*!
 @method
 
 @abstract
 Calls flush, then optionally archives and calls a handler when finished.
 
 @discussion
 When calling <code>flush</code> manually, it is sometimes important to verify
 that the flush has finished before further action is taken. This is
 especially important when the app is in the background and could be suspended
 at any time if protocol is not followed. Delegate methods like
 <code>application:didReceiveRemoteNotification:fetchCompletionHandler:</code>
 are called when an app is brought to the background and require a handler to
 be called when it finishes.
 */
- (void)flushWithCompletion:(nullable void (^)())handler;

/*!
 @method

 @abstract
 Writes current project info, including distinct ID, super properties and pending event
 and People record queues to disk.

 @discussion
 This state will be recovered when the app is launched again if the MdcLib
 library is initialized with the same project token. <b>You do not need to call
 this method</b>. The library listens for app state changes and handles
 persisting data as needed. It can be useful in some special circumstances,
 though, for example, if you'd like to track app crashes from main.m.
 */
- (void)archive;

/*!
 @method

 @abstract
 Creates a distinct_id alias from alias to original id.

 @discussion
 This method is used to map an identifier called an alias to the existing MdcLib
 distinct id. This causes all events and people requests sent with the alias to be
 mapped back to the original distinct id. The recommended usage pattern is to call
 both createAlias: and identify: when the user signs up, and only identify: (with
 their new user ID) when they log in. This will keep your signup funnels working
 correctly.

 <pre>
 // This makes the current ID (an auto-generated GUID)
 // and 'Alias' interchangeable distinct ids.
 [mdclib createAlias:@"Alias"
    forDistinctID:mdclib.distinctId];

 // You must call identify if you haven't already
 // (e.g., when your app launches).
 [mdclib identify:mdclib.distinctId];
</pre>

@param alias 		the new distinct_id that should represent original
@param distinctID 	the old distinct_id that alias will be mapped to
 */
- (void)createAlias:(NSString *)alias forDistinctID:(NSString *)distinctID;

- (NSString *)libVersion;
+ (NSString *)libVersion;


#if !MDCLIB_LIMITED_SUPPORT
#pragma mark - MdcLib Surveys

/*!
 @method

 @abstract
 Shows the survey with the given name.

 @discussion
 This method allows you to explicitly show a named survey at the time of your choosing.

 */
- (void)showSurveyWithID:(NSString *)ID;

/*!
 @method

 @abstract
 Show a survey if one is available.

 @discussion
 This method allows you to display the first available survey targeted to the currently
 identified user at the time of your choosing. You would typically pair this with
 setting <code>showSurveyOnActive = NO;</code> so that the survey won't show automatically.

 */
- (void)showSurvey;

#pragma mark - MdcLib Notifications

/*!
 @method

 @abstract
 Shows the notification of the given id.

 @discussion
 You do not need to call this method on the main thread.
 */
- (void)showNotificationWithID:(NSString *)ID;


/*!
 @method

 @abstract
 Shows a notification with the given type if one is available.

 @discussion
 You do not need to call this method on the main thread.

 @param type The type of notification to show, either @"mini", or @"takeover"
 */
- (void)showNotificationWithType:(NSString *)type;

/*!
 @method

 @abstract
 Shows a notification if one is available.

 @discussion
 You do not need to call this method on the main thread.
 */
- (void)showNotification;


#pragma mark - MdcLib A/B Testing

/*!
 @method

 @abstract
 Join any experiments (A/B tests) that are available for the current user.

 @discussion
 MdcLib will check for A/B tests automatically when your app enters
 the foreground. Call this method if you would like to to check for,
 and join, any experiments are newly available for the current user.

 You do not need to call this method on the main thread.
 */
- (void)joinExperiments;

/*!
 @method

 @abstract
 Join any experiments (A/B tests) that are available for the current user.

 @discussion
 Same as joinExperiments but will fire the given callback after all experiments
 have been loaded and applied.
 */
- (void)joinExperimentsWithCallback:(nullable void (^)())experimentsLoadedCallback;

/**
 * this method was added by lecuong.
 * December 2 2016
 */


/**
 Join to comment in room
 
 @param roomId RoomID
 @param response  if error = nil, join success.
 */
- (void) joinRoom:(NSString *_Nonnull)roomId callback:(void (^ _Nullable)(NSError *_Nullable error))response;


/**
 leave room, don'n listen mesg in room

 @param roomId Room id
 @param response if error = nil, leave success.
 */
- (void) leaveRoom:(NSString *_Nonnull)roomId callback:(void (^_Nullable)(NSError *_Nullable error))response;

/**
 Send message in room
 
 @param roomid  RoomId
 @param content Message content need deliver
 @param response   if error = nil, send success.
 */
- (void)sendChatMessage:(NSString *_Nonnull)roomid type:(NSString *_Nullable)type mesg_root_id:(NSString*)rootId content:(NSDictionary *_Nonnull)content callback:(void (^ _Nullable)(NSError *_Nullable error))response;

/**
 Get history in room

 @param roomId    RoomId
 @param limit     limit message
 @param timestamp time begin get
 @param response  Data response
 */
- (void)getHistoryConversation:(NSString *_Nonnull)roomId limited:(NSInteger)limit timestamp:(NSString*)timestamp callback:(void (^ _Nullable)(NSDictionary *_Nullable data))response;

- (void)connectRealTime;

#endif

@end

/*!
 @protocol

 @abstract
 Delegate protocol for controlling the MdcLib API's network behavior.

 @discussion
 Creating a delegate for the MdcLib object is entirely optional. It is only
 necessary when you want full control over when data is uploaded to the server,
 beyond simply calling stop: and start: before and after a particular block of
 your code.
 */

@protocol MdcLibDelegate <NSObject>

@optional
/*!
 @method

 @abstract
 Asks the delegate if data should be uploaded to the server.

 @discussion
 Return YES to upload now, NO to defer until later.

 @param mdclib        MdcLib API instance
 */
- (BOOL)mdclibWillFlush:(MdcLib *)mdclib;

/*!
 @method
 
 @abstract
 regsiter callback for receiving message.
 
 @param mesg          List unread message
 */
- (void)updateListMesg:(NSArray *)mesg;

- (void)onCommentMesg:(NSDictionary *)mesg;

- (void)onConnected;

- (void)disConnected;

@end

NS_ASSUME_NONNULL_END
