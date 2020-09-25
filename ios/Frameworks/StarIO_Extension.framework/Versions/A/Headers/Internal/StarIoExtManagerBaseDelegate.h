//
//  StarIoExtManagerBaseDelegate.h
//  StarIO_Extension
//
//  Copyright (c) 2018 Star Micronics. All rights reserved.
//

@class StarIoExtManager;


@protocol StarIoExtManagerBaseDelegate <NSObject>

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
