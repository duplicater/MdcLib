//
//  ChatViewController.m
//  MdcLib
//
//  Created by Le Cuong on 12/2/16.
//  Copyright © 2016 lecuong. All rights reserved.
//

#import "ChatViewController.h"
#import <MdcLib/MdcLib.h>
#import "AFNetworking.h"

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
- (IBAction)leaveRoom:(id)sender;

@end

@implementation ChatViewController
{
    NSString *currentRoomId;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.dataMesg = [NSMutableArray array];

    /*
    [[MdcLib sharedInstance] getHistoryConversation:@"100645" limited:20 timestamp:@"1481272710000" callback:^(NSDictionary * _Nullable data) {
        //
        NSLog(@"history %@",data);
    }];*/
    
    NSDictionary* parameters = [[NSDictionary alloc]initWithObjects:[NSArray arrayWithObjects:@"", @"5825780b465d544b1488171071925", @"a8a33cf4a4a6f1985d5ed8c09becee43", @"711", nil] forKeys:[NSArray arrayWithObjects:@"token", @"checksum", @"app_id", @"post_id", nil]];
    
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
    [manager POST:@"http://comment.vietidv2.net/apiv1/getDataComment" parameters:parameters progress:^(NSProgress * _Nonnull uploadProgress) {
        //
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        //
        NSLog(@"respose: %@",responseObject);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        //
        NSLog(@"error: %@",error.description);
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [MdcLib sharedInstance].delegate = self;
    [self connectBtnClicked:self.connectBtn];
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
    /*NSString *roomid = self.roomConnect.text;
    currentRoomId = roomid;
    
    if ((roomid == nil) || ([roomid isEqualToString:@""])){
        self.FBIwarningView.text = @"Room ID invalid";
    }
    else {*/

        [[MdcLib sharedInstance] joinRoom:@"192967" callback:^(NSError * _Nullable error) {
            //
            dispatch_async(dispatch_get_main_queue(), ^{
                //
                if (error){
                    self.FBIwarningView.text = [NSString stringWithFormat:@"Error :%@",error.localizedDescription];
                    NSLog(@"connectBtnClicked %@", error.localizedDescription);
                } else {
                    self.FBIwarningView.text = [NSString stringWithFormat:@"joinRoom %@ success",@"192967" ];
                    NSLog(@"connectBtnClicked %@", @"ok");
                }
            });
            
        }];
    //}
    
    [self.view endEditing:YES];
    
}
- (IBAction)sendBtnClicked:(id)sender {
    NSDictionary *chatDist = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:self.chatField.text, @"sdfsa123123", @"sdffsdv", @"vxc  54t5", nil] forKeys:[NSArray arrayWithObjects:@"typeComment", @"userAvatar", @"userName", @"valueComment", nil]];
    
    [[MdcLib sharedInstance] sendChatMessage:@"192967" type:@"message" mesg_root_id:@"" content:chatDist callback:^(NSError * _Nullable error) {
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
    
    [self.view endEditing:YES];
}

#pragma mark- delegate

- (void)onCommentMesg:(NSDictionary *)mesg{
    // mesf from conversation
    
    NSLog(@"recive mesg %@", mesg);
    //?
    
    self.messageView.text = [NSString stringWithFormat:@"%@\n",mesg ];
    /*∂∂
    NSDictionary *messContent = [mesg objectForKey:@"message"];
    
    NSString *conten = [messContent objectForKey:@"content"];
    NSData* jsonData = [conten dataUsingEncoding:NSUTF8StringEncoding];
    NSError *jsonError = nil;
    NSDictionary* contentJSON = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:&jsonError];
    if (jsonError) {
        return;
    }
    NSString *userAvatar = [contentJSON objectForKey:@"userAvatar"];
    
    NSLog(@"%@", userAvatar);*/
}

- (void)updateListMesg:(NSArray *)mesg{
    // mesg from system
     NSLog(@"system mesg %@", mesg);
    
    self.messageView.text = [NSString stringWithFormat:@"%@\n",mesg ];
}

- (IBAction)leaveRoom:(id)sender {
    /*
    [[MdcLib sharedInstance] leaveRoom:@"100645" callback:^(NSError * _Nullable error) {
        //
        dispatch_async(dispatch_get_main_queue(), ^{
            //
            if (error){
                self.FBIwarningView.text = [NSString stringWithFormat:@"Error :%@",error.localizedDescription];
                NSLog(@"connectBtnClicked %@", error.localizedDescription);
            } else {
                self.FBIwarningView.text = [NSString stringWithFormat:@"leave Room %@ success",@"100645" ];
                NSLog(@"connectBtnClicked %@", @"ok");
                
            }
        });
        
    }];*/
    
    
    NSDictionary* parameters = [[NSDictionary alloc]initWithObjects:[NSArray arrayWithObjects:@"elXbmvZuEH", @"5825780b465d544b1488171071925", @"a8a33cf4a4a6f1985d5ed8c09becee43", @"711", nil] forKeys:[NSArray arrayWithObjects:@"token", @"checksum", @"app_id", @"post_id", nil]];
    
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Accept"];
    [manager POST:@"http://comment.vietidv2.net/apiv1/getDataComment" parameters:parameters progress:^(NSProgress * _Nonnull uploadProgress) {
        //
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        //
        NSLog(@"respose: %@",responseObject);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        //
        NSLog(@"error: %@",error.description);
    }];
}

- (void)onConnected{
     NSLog(@"on Connected %@", @"ok");
}

- (void)disConnected{
     NSLog(@"on disConnected");
}


@end
