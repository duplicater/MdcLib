//
//  ChatViewController.m
//  MdcLib
//
//  Created by Le Cuong on 12/2/16.
//  Copyright © 2016 lecuong. All rights reserved.
//

#import "ChatViewController.h"

#import <MdcLib/MdcLib.h>

@interface ChatViewController ()<MdcLibDelegate>
- (IBAction)backBtnClicked:(id)sender;
@property (weak, nonatomic) IBOutlet UITableView *chatTable;
@property (weak, nonatomic) IBOutlet UITextField *roomConnect;
@property (weak, nonatomic) IBOutlet UIButton *connectBtn;
- (IBAction)connectBtnClicked:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *chatField;
- (IBAction)sendBtnClicked:(id)sender;
@property (weak, nonatomic) IBOutlet UITextView *FBIwarningView;
@property (weak, nonatomic) IBOutlet UITextView *messageView;

@property (nonatomic, strong) NSMutableArray *dataMesg;

@end

@implementation ChatViewController
{
    NSString *currentRoomId;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.dataMesg = [NSMutableArray array];

    [MdcLib sharedInstance].delegate = self;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)backBtnClicked:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
    
}
- (IBAction)connectBtnClicked:(id)sender {
    NSString *roomid = self.roomConnect.text;
    currentRoomId = roomid;
    
    if ((roomid == nil) || ([roomid isEqualToString:@""])){
        self.FBIwarningView.text = @"Room ID invalid";
    }
    else {

        [[MdcLib sharedInstance] joinRoom:roomid callback:^(NSError * _Nullable error) {
            //
            dispatch_async(dispatch_get_main_queue(), ^{
                //
                if (error){
                    self.FBIwarningView.text = [NSString stringWithFormat:@"Error :%@",error.localizedDescription];
                    NSLog(@"connectBtnClicked %@", error.localizedDescription);
                } else {
                    self.FBIwarningView.text = [NSString stringWithFormat:@"joinRoom %@ success",roomid ];
                    NSLog(@"connectBtnClicked %@", @"ok");

                }
            });
            
        }];
    }
    
}
- (IBAction)sendBtnClicked:(id)sender {
    NSDictionary *chatDist = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:self.chatField.text, nil] forKeys:[NSArray arrayWithObjects:@"me", nil]];
    
    [[MdcLib sharedInstance] sendChatMessage:currentRoomId rootId:@"" content:chatDist callback:^(NSError * _Nullable error) {
        //
        dispatch_async(dispatch_get_main_queue(), ^{
            if (error){
                self.FBIwarningView.text = [NSString stringWithFormat:@"Send chat error :%@",error.localizedDescription];
                NSLog(@"sendBtnClicked %@", error.localizedDescription);
            } else {
                self.FBIwarningView.text = [NSString stringWithFormat:@"ok" ];
                NSLog(@"sendBtnClicked %@", @"ok");
            }
        });
    }];
    
    
}

#pragma mark- delegate

- (void)onCommentMesg:(NSDictionary *)mesg{
    // mesf from conversation
    
    NSLog(@"recive mesg %@", mesg);
    //?
    
    self.messageView.text = [NSString stringWithFormat:@"%@\n",mesg ];
}

- (void)updateListMesg:(NSArray *)mesg{
    // mesg from system
     NSLog(@"system mesg %@", mesg);
    
    self.messageView.text = [NSString stringWithFormat:@"%@\n",mesg ];
}





@end
