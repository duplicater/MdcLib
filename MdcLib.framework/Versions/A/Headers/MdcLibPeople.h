//
//  MdcLibPeople.h
//  MdcLib
//
//  Created by Nguyen Hoa on 6/16/16.
//  Copyright © 2016 MdcLib. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class
 MdcLib People API.
 
 @abstract
 Access to the MdcLib People API, available as a property on the main
 MdcLib API.
 
 @discussion
 <b>You should not instantiate this object yourself.</b> An instance of it will
 be available as a property of the main MdcLib object. Calls to MdcLib
 People methods will look like this:
 
 <pre>
 [mdclib.people increment:@"App Opens" by:[NSNumber numberWithInt:1]];
 </pre>
 
 Please note that the core <code>MdcLib</code> and
 <code>MdcLibPeople</code> classes share the <code>identify:</code> method.
 The <code>MdcLib</code> <code>identify:</code> affects the
 <code>distinct_id</code> property of events sent by <code>track:</code> and
 <code>track:properties:</code> and determines which MdcLib People user
 record will be updated by <code>set:</code>, <code>increment:</code> and other
 <code>MdcLibPeople</code> methods.
 
 <b>If you are going to set your own distinct IDs for core MdcLib event
 tracking, make sure to use the same distinct IDs when using MdcLib
 People</b>.
 */
@interface MdcLibPeople : NSObject
/*!
 @property
 
 @abstract
 controls the $ignore_time property in any subsequent MdcLibPeople operation.
 
 If the $ignore_time property is present and true in your request,
 MdcLib will not automatically update the "Last Seen" property of the profile.
 Otherwise, MdcLib will add a "Last Seen" property associated with the
 current time for all $set, $append, and $add operations
 
 @discussion
 Defaults to NO.
 */
@property (atomic) BOOL ignoreTime;

//lecuong add device token


/**
 @property
 devicetoke dung de push notification
 */
@property (nonatomic, strong) NSString *deviceToken;

/*!
 @method
 
 @abstract
 Register the given device to receive push notifications.
 
 @discussion
 This will associate the device token with the current user in MdcLib People,
 which will allow you to send push notifications to the user from the MdcLib
 People web interface. You should call this method with the <code>NSData</code>
 token passed to
 <code>application:didRegisterForRemoteNotificationsWithDeviceToken:</code>.
 
 @param deviceToken     device token as returned <code>application:didRegisterForRemoteNotificationsWithDeviceToken:</code>
 */
- (void)addPushDeviceToken:(NSData *)deviceToken;

/*!
 @method
 
 @abstract
 Unregister the given device to receive push notifications.
 
 @discussion
 This will unset all of the push tokens saved to this people profile. This is useful
 in conjunction with a call to `reset`, or when a user is logging out.
 */
- (void)removePushDeviceToken;

/*!
 @method
 
 @abstract
 Set properties on the current user in MdcLib People.
 
 @discussion
 The properties will be set on the current user. The keys must be NSString
 objects and the values should be NSString, NSNumber, NSArray, NSDate, or
 NSNull objects. We use an NSAssert to enforce this type requirement. In
 release mode, the assert is stripped out and we will silently convert
 incorrect types to strings using [NSString stringWithFormat:@"%@", value]. You
 can override the default the current project token and distinct ID by
 including the special properties: $token and $distinct_id. If the existing
 user record on the server already has a value for a given property, the old
 value is overwritten. Other existing properties will not be affected.
 
 <pre>
 // applies to both MdcLib Engagement track: AND MdcLib People set: and
 // increment: calls
 [mdclib identify:distinctId];
 </pre>
 
 @param properties       properties dictionary
 
 */
- (void)set:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Convenience method for setting a single property in MdcLib People.
 
 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code>NSArray</code>, <code>NSDictionary</code>, <code>NSDate</code> or
 <code>NSURL</code> objects.
 
 @param property        property name
 @param object          property value
 */
- (void)set:(NSString *)property to:(id)object;

/*!
 @method
 
 @abstract
 Set properties on the current user in MdcLib People, but don't overwrite if
 there is an existing value.
 
 @discussion
 This method is identical to <code>set:</code> except it will only set
 properties that are not already set. It is particularly useful for collecting
 data about the user's initial experience and source, as well as dates
 representing the first time something happened.
 
 @param properties       properties dictionary
 
 */
- (void)setOnce:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Remove a list of properties and their values from the current user's profile
 in MdcLib People.
 
 @discussion
 The properties array must ony contain NSString names of properties. For properties
 that don't exist there will be no effect.
 
 @param properties       properties array
 
 */
- (void)unset:(NSArray *)properties;

/*!
 @method
 
 @abstract
 Increment the given numeric properties by the given values.
 
 @discussion
 Property keys must be NSString names of numeric properties. A property is
 numeric if its current value is a number. If a property does not exist, it
 will be set to the increment amount. Property values must be NSNumber objects.
 
 @param properties      properties dictionary
 */
- (void)increment:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Convenience method for incrementing a single numeric property by the specified
 amount.
 
 @param property        property name
 @param amount          amount to increment by
 */
- (void)increment:(NSString *)property by:(NSNumber *)amount;

/*!
 @method
 
 @abstract
 Append values to list properties.
 
 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code>NSArray</code>, <code>NSDictionary</code>, <code>NSDate</code> or
 <code>NSURL</code> objects.
 
 @param properties      mapping of list property names to values to append
 */
- (void)append:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Union list properties.
 
 @discussion
 Property keys must be <code>NSArray</code> objects.
 
 @param properties      mapping of list property names to lists to union
 */
- (void)union:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Track money spent by the current user for revenue analytics.
 
 @param amount          amount of revenue received
 */
- (void)trackCharge:(NSNumber *)amount;

/*!
 @method
 
 @abstract
 Track money spent by the current user for revenue analytics and associate
 properties with the charge.
 
 @discussion
 Charge properties allow you segment on types of revenue. For instance, you
 could record a product ID with each charge so that you could segment on it in
 revenue analytics to see which products are generating the most revenue.
 */
- (void)trackCharge:(NSNumber *)amount withProperties:(nullable NSDictionary *)properties;


/*!
 @method
 
 @abstract
 Delete current user's revenue history.
 */
- (void)clearCharges;

/*!
 @method
 
 @abstract
 Delete current user's record from MdcLib People.
 */
- (void)deleteUser;

@end

NS_ASSUME_NONNULL_END
