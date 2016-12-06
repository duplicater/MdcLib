//
//  MdcLibViewController.m
//  MdcLib
//
//  Created by Nguyen Hoa on 11/07/2016.
//  Copyright (c) 2016 Nguyen Hoa. All rights reserved.
//

#import "MdcLibViewController.h"

#import <MdcLib/MdcLib.h>

@interface MdcLibViewController ()

@end

@implementation MdcLibViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)setPeopleProperties:(id)sender {
    MdcLib *mdclib = [MdcLib sharedInstance];
    
    [mdclib registerUser:@"sonlm@vccorp.vn" userId:@"sonlm"];
    //[mdclib identify:mdclib.distinctId];
}

- (IBAction)trackEvent:(id)sender {
    MdcLib *mdclib = [MdcLib sharedInstance];
    [mdclib track:@"Button Clicked" properties:@{@"btname": @"track"}];
}

@end
