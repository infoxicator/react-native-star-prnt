//
//  ISSCBBuilder.h
//  StarIO_Extension
//
//  Created by Yuji on 2017/**/**.
//  Copyright © 2017年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ISSCBBuilder : NSObject

@property (nonatomic, readonly) NSMutableData *commands;
@property (nonatomic, readonly) NSMutableData *passThroughCommands;

- (void)appendByte:(unsigned char)data;

- (void)appendData:(NSData *)otherData;

- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;

- (void)appendZeroClear;

- (void)appendUnitChange;

@end
