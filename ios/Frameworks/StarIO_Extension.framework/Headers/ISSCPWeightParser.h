//
//  ISSCPWeightParser.h
//  StarIO_Extension
//
//  Created by Yuji on 2017/**/**.
//  Copyright © 2017年 Star Micronics. All rights reserved.
//

#import "ISCPParser.h"

typedef NS_ENUM(NSInteger, StarIoExtDisplayedWeightStatus) {
    StarIoExtDisplayedWeightStatusInvalid = 0,
    StarIoExtDisplayedWeightStatusZero,
    StarIoExtDisplayedWeightStatusNotInMotion,
    StarIoExtDisplayedWeightStatusMotion
};

@interface ISSCPWeightParser : ISCPParser

- (StarIoExtDisplayedWeightStatus)status;

- (NSString *)weight;

- (NSData *)createSendCommands;

- (NSData *)createReceiveCommands;

@end
