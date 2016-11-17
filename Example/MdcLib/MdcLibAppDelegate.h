//
//  MdcLibAppDelegate.h
//  MdcLib
//
//  Created by Nguyen Hoa on 11/07/2016.
//  Copyright (c) 2016 Nguyen Hoa. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MdcLib/MdcLib.h>

@interface MdcLibAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) MdcLib *mdcLib;

@property (strong, nonatomic, retain) NSDate *startTime;

@property (nonatomic) UIBackgroundTaskIdentifier bgTask;

@end
