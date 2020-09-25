//
//  StarIoExtManager.h
//  StarIO_Extension
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StarIO/SMPort.h>
#import <StarIO/ExternalAccessoryPort.h>

#import "StarIoExtManagerDelegate.h"

typedef NS_ENUM(NSInteger, StarIoExtManagerType) {
    StarIoExtManagerTypeStandard = 0,
    StarIoExtManagerTypeWithBarcodeReader,
    StarIoExtManagerTypeOnlyBarcodeReader,
};

typedef NS_ENUM(NSInteger, StarIoExtManagerPrinterStatus) {
    StarIoExtManagerPrinterStatusInvalid = 0,
    StarIoExtManagerPrinterStatusImpossible,
    StarIoExtManagerPrinterStatusOnline,
    StarIoExtManagerPrinterStatusOffline
};

typedef NS_ENUM(NSInteger, StarIoExtManagerPrinterPaperStatus) {
    StarIoExtManagerPrinterPaperStatusInvalid = 0,
    StarIoExtManagerPrinterPaperStatusImpossible,
    StarIoExtManagerPrinterPaperStatusReady,
    StarIoExtManagerPrinterPaperStatusNearEmpty,
    StarIoExtManagerPrinterPaperStatusEmpty
};

typedef NS_ENUM(NSInteger, StarIoExtManagerPrinterCoverStatus) {
    StarIoExtManagerPrinterCoverStatusInvalid = 0,
    StarIoExtManagerPrinterCoverStatusImpossible,
    StarIoExtManagerPrinterCoverStatusOpen,
    StarIoExtManagerPrinterCoverStatusClose
};

typedef NS_ENUM(NSInteger, StarIoExtManagerCashDrawerStatus) {
    StarIoExtManagerCashDrawerStatusInvalid = 0,
    StarIoExtManagerCashDrawerStatusImpossible,
    StarIoExtManagerCashDrawerStatusOpen,
    StarIoExtManagerCashDrawerStatusClose
};

typedef NS_ENUM(NSInteger, StarIoExtManagerBarcodeReaderStatus) {
    StarIoExtManagerBarcodeReaderStatusInvalid = 0,
    StarIoExtManagerBarcodeReaderStatusImpossible,
    StarIoExtManagerBarcodeReaderStatusConnect,
    StarIoExtManagerBarcodeReaderStatusDisconnect
};

//static const NSErrorDomain SMResultCodeErrorDomain = @"jp.star-m.stario_extension";

//NS_ERROR_ENUM(SMResultCodeErrorDomain) {
//    SMResultCodeFailedError = -1,
//    SMResultCodeInProcessError = -2,
//    SMResultCodeInUseError = -100,
//};


@interface StarIoExtManager : NSObject

@property (readonly, nonatomic) SMPort *port;

@property (readonly, nonatomic) StarIoExtManagerPrinterStatus       printerStatus;

@property (readonly, nonatomic) StarIoExtManagerPrinterPaperStatus  printerPaperStatus;

@property (readonly, nonatomic) StarIoExtManagerPrinterCoverStatus  printerCoverStatus;

@property (readonly, nonatomic) StarIoExtManagerCashDrawerStatus    cashDrawerStatus;

@property (readonly, nonatomic) StarIoExtManagerBarcodeReaderStatus barcodeReaderStatus;

@property (nonatomic) BOOL cashDrawerOpenActiveHigh;

@property (weak, nonatomic) id<StarIoExtManagerDelegate> delegate;

@property (readonly, nonatomic) NSRecursiveLock *lock;

- (id)initWithType:(StarIoExtManagerType)type
          portName:(NSString *)portName
      portSettings:(NSString *)portSettings
   ioTimeoutMillis:(NSUInteger)ioTimeoutMillis;

- (BOOL)connect;

- (BOOL)disconnect;

@end
