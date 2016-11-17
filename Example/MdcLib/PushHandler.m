/*
 Copyright 2009-2016 Urban Airship Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE URBAN AIRSHIP INC ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL URBAN AIRSHIP INC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "PushHandler.h"

@implementation PushHandler

- (void)receivedForegroundNotification:(NSDictionary*)notification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    NSLog(@"Received a notification while the app was already in the foreground");

    // Only display an alert dialog if the push does not contain a rich push message id.
    // If it does, allow the InboxDelegate's richPushMessageAvailable: to handle it.
    id alertData = notification[@"aps"][@"alert"];
    NSString* alertMessage = @"";
    NSString* alertTitle = @"";
    if ([alertData isKindOfClass:[NSDictionary class]]) {
        alertMessage = alertData[@"body"];
        alertTitle = alertData[@"title"];
    }
    if ((alertMessage) && (alertTitle)){

        // Show alert for push notifications recevied while the app is running
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
        if ([[[UIDevice currentDevice] systemVersion] compare:@"8.0" options:NSNumericSearch] != NSOrderedAscending) {
            UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle message:alertMessage preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            UIViewController* topController = [UIApplication sharedApplication].keyWindow.rootViewController;

            [topController presentViewController:alert animated:YES completion:nil];
        }
        else {
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                            message:alertMessage
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil];
            [alert show];
        }
#else
        UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
#endif
    }
    else {
        NSLog(@"Unable to parse message body");
    }

    // Call the completion handler with the fetch results
    completionHandler(UIBackgroundFetchResultNoData);
}

- (void)launchedFromNotification:(NSDictionary*)notification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    NSLog(@"The application was launched or resumed from a notification");

    // Do something when launched via a notification
    id alertData = notification[@"aps"][@"alert"];
    NSString* alertMessage = @"";
    NSString* alertTitle = @"";
    if ([alertData isKindOfClass:[NSDictionary class]]) {
        alertMessage = alertData[@"body"];
        alertTitle = alertData[@"title"];
    }
    if ((alertMessage) && (alertTitle)){
        
        // Show alert for push notifications recevied while the app is running
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
        if ([[[UIDevice currentDevice] systemVersion] compare:@"8.0" options:NSNumericSearch] != NSOrderedAscending) {
            UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle message:alertMessage preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            UIViewController* topController = [UIApplication sharedApplication].keyWindow.rootViewController;
            
            [topController presentViewController:alert animated:YES completion:nil];
        }
        else {
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                            message:alertMessage
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil];
            [alert show];
        }
#else
        UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
#endif
    }
    
    // Call the completion handler with the fetch results
    completionHandler(UIBackgroundFetchResultNoData);
}

- (void)launchedFromNotification:(NSDictionary*)notification actionIdentifier:(NSString*)identifier completionHandler:(void (^)())completionHandler
{
    NSLog(@"The application was launched or resumed from a foreground user notification button");

    // Do something when launched via a user notification button
    id alertData = notification[@"aps"][@"alert"];
    NSString* alertMessage = @"";
    NSString* alertTitle = @"";
    if ([alertData isKindOfClass:[NSDictionary class]]) {
        alertMessage = alertData[@"body"];
        alertTitle = alertData[@"title"];
    }
    if ((alertMessage) && (alertTitle)){
        
        // Show alert for push notifications recevied while the app is running
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
        if ([[[UIDevice currentDevice] systemVersion] compare:@"8.0" options:NSNumericSearch] != NSOrderedAscending) {
            UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle message:alertMessage preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            UIViewController* topController = [UIApplication sharedApplication].keyWindow.rootViewController;
            
            [topController presentViewController:alert animated:YES completion:nil];
        }
        else {
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                            message:alertMessage
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil];
            [alert show];
        }
#else
        UIAlertView* alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
#endif
    }
    
    // Call the completion handler
    completionHandler();
}

- (void)receivedBackgroundNotification:(NSDictionary*)notification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    NSLog(@"The application was started in the background from a user notification");

    // Call the completion handler
    completionHandler(UIBackgroundFetchResultNoData);
}

- (void)receivedBackgroundNotification:(NSDictionary*)notification actionIdentifier:(NSString*)identifier completionHandler:(void (^)())completionHandler
{
    NSLog(@"The application was started in the background from a user notification button");
    // Do any background tasks via a user notification button

    // Call the completion handler
    completionHandler();
}

@end
