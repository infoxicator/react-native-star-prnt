//
//  StarIoExtManager.h
//  StarIO_Extension
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StarIO/SMPort.h>

typedef NS_ENUM(NSInteger, StarIoExtManagerType) {
    StarIoExtManagerTypeStandard = 0,
    StarIoExtManagerTypeWithBarcodeReader,
    StarIoExtManagerTypeOnlyBarcodeReader,
};

typedef NS_ENUM(NSInteger, StarIoExtManagerStatus) {
    StarIoExtManagerStatusInvalid                 __attribute__((unavailable("Not available. Please change to StarIoExtManager...StatusInvalid."))) = 0,
    StarIoExtManagerStatusImpossible              __attribute__((unavailable("Not available. Please change to StarIoExtManager...StatusImpossible."))),
    StarIoExtManagerStatusPrinterOnline           __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterStatusOnline."))),
    StarIoExtManagerStatusPrinterOffline          __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterStatusOffline."))),
    StarIoExtManagerStatusPrinterPaperReady       __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterPaperStatusReady."))),
    StarIoExtManagerStatusPrinterPaperNearEmpty   __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterPaperStatusNearEmpty."))),
    StarIoExtManagerStatusPrinterPaperEmpty       __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterPaperStatusEmpty."))),
    StarIoExtManagerStatusPrinterCoverOpen        __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterCoverStatusOpen."))),
    StarIoExtManagerStatusPrinterCoverClose       __attribute__((unavailable("Not available. Please change to StarIoExtManagerPrinterCoverStatusClose."))),
    StarIoExtManagerStatusCashDrawerOpen          __attribute__((unavailable("Not available. Please change to StarIoExtManagerCashDrawerStatusOpen."))),
    StarIoExtManagerStatusCashDrawerClose         __attribute__((unavailable("Not available. Please change to StarIoExtManagerCashDrawerStatusClose."))),
    StarIoExtManagerStatusBarcodeReaderConnect    __attribute__((unavailable("Not available. Please change to StarIoExtManagerBarcodeReaderStatusConnect."))),
    StarIoExtManagerStatusBarcodeReaderDisconnect __attribute__((unavailable("Not available. Please change to StarIoExtManagerBarcodeReaderStatusDisconnect.")))
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

@class StarIoExtManager;

@protocol StarIoExtManagerDelegate <NSObject>

@optional

- (void)didPrinterImpossible;
- (void)didPrinterImpossible:(StarIoExtManager *)manager;

- (void)didPrinterOnline;
- (void)didPrinterOnline:(StarIoExtManager *)manager;
- (void)didPrinterOffline;
- (void)didPrinterOffline:(StarIoExtManager *)manager;

- (void)didPrinterPaperReady;
- (void)didPrinterPaperReady:(StarIoExtManager *)manager;
- (void)didPrinterPaperNearEmpty;
- (void)didPrinterPaperNearEmpty:(StarIoExtManager *)manager;
- (void)didPrinterPaperEmpty;
- (void)didPrinterPaperEmpty:(StarIoExtManager *)manager;

- (void)didPrinterCoverOpen;
- (void)didPrinterCoverOpen:(StarIoExtManager *)manager;
- (void)didPrinterCoverClose;
- (void)didPrinterCoverClose:(StarIoExtManager *)manager;

- (void)didCashDrawerOpen;
- (void)didCashDrawerOpen:(StarIoExtManager *)manager;
- (void)didCashDrawerClose;
- (void)didCashDrawerClose:(StarIoExtManager *)manager;

- (void)didBarcodeReaderImpossible;
- (void)didBarcodeReaderImpossible:(StarIoExtManager *)manager;

- (void)didBarcodeReaderConnect;
- (void)didBarcodeReaderConnect:(StarIoExtManager *)manager;
- (void)didBarcodeReaderDisconnect;
- (void)didBarcodeReaderDisconnect:(StarIoExtManager *)manager;

- (void)didBarcodeDataReceive:(NSData *)data;
- (void)didBarcodeDataReceive:(StarIoExtManager *)manager data:(NSData *)data;

- (void)didAccessoryConnectSuccess;
- (void)didAccessoryConnectSuccess:(StarIoExtManager *)manager;
- (void)didAccessoryConnectFailure;
- (void)didAccessoryConnectFailure:(StarIoExtManager *)manager;
- (void)didAccessoryDisconnect;
- (void)didAccessoryDisconnect:(StarIoExtManager *)manager;

- (void)didStatusUpdate:(NSString *)status;
- (void)didStatusUpdate:(StarIoExtManager *)manager status:(NSString *)status;

@end

@interface StarIoExtManager : NSObject

@property (readonly, nonatomic) SMPort *port;

@property (readonly, nonatomic) StarIoExtManagerStatus              printerOnlineStatus        __attribute__((unavailable("Not available. Please change to printerStatus.")));
@property (readonly, nonatomic) StarIoExtManagerPrinterStatus       printerStatus;
@property (readonly, nonatomic) StarIoExtManagerStatus              printerPaperReadyStatus    __attribute__((unavailable("Not available. Please change to printerPaperStatus")));
@property (readonly, nonatomic) StarIoExtManagerPrinterPaperStatus  printerPaperStatus;
@property (readonly, nonatomic) StarIoExtManagerStatus              printerCoverOpenStatus     __attribute__((unavailable("Not available. Please change to printerCoverStatus.")));
@property (readonly, nonatomic) StarIoExtManagerPrinterCoverStatus  printerCoverStatus;
@property (readonly, nonatomic) StarIoExtManagerStatus              cashDrawerOpenStatus       __attribute__((unavailable("Not available. Please change to cashDrawerStatus.")));
@property (readonly, nonatomic) StarIoExtManagerCashDrawerStatus    cashDrawerStatus;
@property (readonly, nonatomic) StarIoExtManagerStatus              barcodeReaderConnectStatus __attribute__((unavailable("Not available. Please change to barcodeReaderStatus.")));
@property (readonly, nonatomic) StarIoExtManagerBarcodeReaderStatus barcodeReaderStatus;

@property (nonatomic) BOOL cashDrawerOpenActiveHigh;

@property (weak, nonatomic) id<StarIoExtManagerDelegate> delegate;

@property (readonly, nonatomic) NSRecursiveLock *lock;

- (id)initWithType:(StarIoExtManagerType)type portName:(NSString *)portName portSettings:(NSString *)portSettings ioTimeoutMillis:(NSUInteger)ioTimeoutMillis;

- (BOOL)connect;

- (BOOL)disconnect;

@end
