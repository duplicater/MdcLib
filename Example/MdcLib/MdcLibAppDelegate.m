//
//  MdcLibAppDelegate.m
//  MdcLib
//
//  Created by Nguyen Hoa on 11/07/2016.
//  Copyright (c) 2016 Nguyen Hoa. All rights reserved.
//

#import "MdcLibAppDelegate.h"
#import "PushHandler.h"

// IMPORTANT!!! replace with your api token from https://mdclib.com/account/
#define MDCLIB_TOKEN @"aff0466c0b9626ba3bc0deac36b01cf8"
#define MDCLIB_APPKEY @"53c213ccca20bce2d7d65c6167d0b1a6"

@interface MdcLibAppDelegate () <MdcLibDelegate>

@property(nonatomic, strong) PushHandler *pushHandler;

@end

@implementation MdcLibAppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //lecuong add.

    [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"mdclibToken": MDCLIB_TOKEN}];
    NSString *mdclibToken = [[NSUserDefaults standardUserDefaults] stringForKey:@"mdclibToken"];
    
    [self.window makeKeyAndVisible];
    
    if (mdclibToken == nil || [mdclibToken isEqualToString:@""] || [mdclibToken isEqualToString:@"YOUR_MDCLIB_PROJECT_TOKEN"]) {
#ifndef DEBUG
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
        if ([[[UIDevice currentDevice] systemVersion] compare:@"8.0" options:NSNumericSearch] != NSOrderedAscending) {
            UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"MdcLib Token Required" message:@"Go to Settings > MdcLib and add your project's token" preferredStyle:UIAlertControllerStyleAlert];
            [alertController addAction:[UIAlertAction actionWithTitle:@"Okay" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
            }]];
            [self.window.rootViewController presentViewController:alertController animated:YES completion:nil];
        } else {
            [[[UIAlertView alloc] initWithTitle:@"MdcLib Token Required"
                                        message:@"Go to Settings > MdcLib and add your project's token"
                                       delegate:nil
                              cancelButtonTitle:@"OK"
                              otherButtonTitles:nil] show];
        }
#else
        [[[UIAlertView alloc] initWithTitle:@"MdcLib Token Required"
                                    message:@"Go to Settings > MdcLib and add your project's token"
                                   delegate:nil
                          cancelButtonTitle:@"OK"
                          otherButtonTitles:nil] show];
#endif
#endif
    } else {
        // Initialize the MdcLibAPI object
        self.mdcLib = [MdcLib sharedInstanceWithToken:mdclibToken appKey:MDCLIB_APPKEY launchOptions:launchOptions];
        self.mdcLib.delegate = self;
    }
    
    // Override point for customization after application launch.
    self.mdcLib.enableRealtime = YES;
    self.mdcLib.checkForSurveysOnActive = YES;
    self.mdcLib.showSurveyOnActive = YES; //Change this to NO to show your surveys manually.
    
    self.mdcLib.checkForNotificationsOnActive = YES;
    self.mdcLib.showNotificationOnActive = YES; //Change this to NO to show your notifs manually.
    
    // Set the upload interval to 15 seconds for demonstration purposes. This would be overkill for most applications.
    self.mdcLib.flushInterval = 15; // defaults to 15 seconds
    
    self.pushHandler = [[PushHandler alloc] init];
    [MdcLib push].pushNotificationDelegate = self.pushHandler;
    
    // Set the icon badge to zero on startup (optional)
    [[MdcLib push] resetBadge];
    return YES;
}


#pragma mark - Session timing example

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    self.startTime = [NSDate date];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    NSLog(@"%@ will resign active", self);
    NSNumber *seconds = @([[NSDate date] timeIntervalSinceDate:self.startTime]);
    [[MdcLib sharedInstance] track:@"Session" properties:@{@"Length": seconds}];
}

#pragma mark - Background task tracking test

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

#pragma mark - MdcLibDelegate
- (void)updateListMesg:(NSArray *)mesg {
    NSLog(@"%@", mesg);
}

- (void)onConnected{
    NSLog(@"on Connected %@", @"ok");
}


@end
