//
//  ISCPParser.h
//  StarIO_Extension
//
//  Created by Yuji on 2017/**/**.
//  Copyright © 2017年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, StarIoExtParserCompletionResult) {
    StarIoExtParserCompletionResultInvalid = 0,
    StarIoExtParserCompletionResultSuccess,
    StarIoExtParserCompletionResultFailure
};

typedef StarIoExtParserCompletionResult (^StarIoExtParserCompletionHandler)(uint8_t *buffer, int *length);

@interface ISCPParser : NSObject

@property (nonatomic, copy) StarIoExtParserCompletionHandler completionHandler;

- (NSData *)createSendCommands;

- (NSData *)createReceiveCommands;

@end
