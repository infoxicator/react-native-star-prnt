//
//  StarIoExtManagerDelegate.h
//  StarIO_Extension
//
//  Copyright (c) 2018 Star Micronics. All rights reserved.
//

#import "StarIoExtManagerBaseDelegate.h"


@protocol StarIoExtManagerDelegate<StarIoExtManagerBaseDelegate>

@optional

- (void)  manager:(nonnull StarIoExtManager *)manager
   didConnectPort:(nonnull NSString *)portName;

- (void)     manager:(nonnull StarIoExtManager *)manager
didFailToConnectPort:(nonnull NSString *)portName
               error:(nullable NSError *)error;

@end
