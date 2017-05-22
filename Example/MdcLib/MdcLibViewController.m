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
@property (weak, nonatomic) IBOutlet UITextField *accfield;
@property (weak, nonatomic) IBOutlet UITextField *passfield;

@property (nonatomic, strong) UITapGestureRecognizer *tapHidenKeyboard;
@property (readwrite) BOOL shouldEnableTapgesture;

@end

@implementation MdcLibViewController
{
    BOOL isShowKeybroad;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self addNotificationKeybroad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)setPeopleProperties:(id)sender {
    MdcLib *mdclib = [MdcLib sharedInstance];
    [mdclib identify:mdclib.distinctId];
    //[mdclib registerUser:self.accfield.text userId:self.passfield.text];
    [mdclib registerUser:@"lecuongxxx@gmail.com" userId:@"ahihi"];
    [mdclib track:@"Button Clicked" properties:@{@"btname": @"track"}];
}

- (IBAction)trackEvent:(id)sender {
    //logout
    [[MdcLib sharedInstance] reset];
}

///--------------------------------------
#pragma mark - Keybroad
///--------------------------------------
- (void)addNotificationKeybroad{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:@"UIKeyboardWillShowNotification" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidHide:) name:@"UIKeyboardDidHideNotification" object:nil];
    self.tapHidenKeyboard = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapHidenKeyboard:)];
    self.tapHidenKeyboard.numberOfTapsRequired = 1;
}

- (void)keyboardWillShow:(NSNotification*)note{
    if (isShowKeybroad == NO){
        _shouldEnableTapgesture = NO;
        [self.view addGestureRecognizer:self.tapHidenKeyboard];
        isShowKeybroad = YES;
    } else {
        return;
    }
}
- (void)keyBoardDidHide:(NSNotification*)note{
    if (isShowKeybroad == YES){
        _shouldEnableTapgesture = YES;
        [self.view removeGestureRecognizer:self.tapHidenKeyboard];
        isShowKeybroad = NO;
    } else {
        return;
    }
}

- (void)tapHidenKeyboard:(id)sender{
    [self.view endEditing:YES];
}


@end
