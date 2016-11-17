//
//  BaseMessage.h
//  MdcLib
//
//  Created by Nguyen Hoa on 8/9/16.
//  Copyright © 2016 MdcLib. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BaseMessage : NSObject

@property (nonatomic, strong) NSString *senderID;
@property (nonatomic, strong) NSString *messageID;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSDictionary *data;

- (instancetype)initWithDictionary:(NSDictionary *)object;
- (instancetype)initWithID:(NSString *)sender_Id messageID:(NSString *)messageID type:(NSString *)type data:(NSDictionary *)data;

@end
