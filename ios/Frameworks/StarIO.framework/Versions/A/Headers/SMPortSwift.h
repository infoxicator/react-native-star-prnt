//
//  SMPortSwift.h
//  StarIOPort
//
//  Caution: The methods in this file MUST NOT be called from Objective-C.
//

#pragma once

#import "SMPort.h"

@interface SMPort (ThrowError)

//
// API for Swift
//

+ (NSArray *)searchPrinterThrowsError:(NSString *)target
                                     :(NSError **)error
NS_SWIFT_NAME(searchPrinter(target:));

+ (SMPort *)getPortThrowsError:(NSString *)portName
                              :(NSString *)portSettings
                              :(u_int32_t)ioTimeoutMillis
                              :(NSError **)error
NS_SWIFT_NAME(getPort(portName:portSettings:ioTimeoutMillis:));

- (BOOL)beginCheckedBlockThrowsError:(void *)starPrinterStatus
                                    :(u_int32_t)level
                                    :(NSError **)error
NS_SWIFT_NAME(beginCheckedBlock(starPrinterStatus:level:));

- (BOOL)endCheckedBlockThrowsError:(void *)starPrinterStatus
                                  :(u_int32_t)level
                                  :(NSError **)error
NS_SWIFT_NAME(endCheckedBlock(starPrinterStatus:level:));

- (BOOL)writePort:(u_int8_t const *)writeBuffer
                 :(u_int32_t)offset
                 :(u_int32_t)size
                 :(u_int32_t *)numberOfBytesWritten
                 :(NSError **)error
NS_SWIFT_NAME(write(writeBuffer:offset:size:numberOfBytesWritten:));

- (BOOL)readPort:(u_int8_t *)readBuffer
                :(u_int32_t)offset
                :(u_int32_t)size
                :(u_int32_t *)numberOfBytesRead
                :(NSError **)error
NS_SWIFT_NAME(read(readBuffer:offset:size:numberOfBytesRead:));

- (BOOL)getParsedStatusThrowsError:(void *)starPrinterStatus
                                  :(u_int32_t)level
                                  :(NSError **)error
NS_SWIFT_NAME(getParsedStatus(starPrinterStatus:level:));

- (NSDictionary *)getFirmwareInformationThrowsError:(NSError **)error
NS_SWIFT_NAME(getFirmwareInformation());

- (BOOL)disconnectAccessory:(NSError **)error;

@end
