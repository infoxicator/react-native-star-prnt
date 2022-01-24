//
//  StarIoExtManager+Unavailable.h
//  StarIO_Extension
//
//  Copyright (c) 2018 Star Micronics. All rights reserved.
//

#pragma once

#import "StarIoExtManager.h"

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

@interface StarIoExtManager(Unavailable)

@property (readonly, nonatomic) StarIoExtManagerStatus printerPaperReadyStatus __attribute__((unavailable("Not available. Please change to printerPaperStatus")));

@property (readonly, nonatomic) StarIoExtManagerStatus printerOnlineStatus __attribute__((unavailable("Not available. Please change to printerStatus.")));

@property (readonly, nonatomic) StarIoExtManagerStatus printerCoverOpenStatus __attribute__((unavailable("Not available. Please change to printerCoverStatus.")));

@property (readonly, nonatomic) StarIoExtManagerStatus cashDrawerOpenStatus __attribute__((unavailable("Not available. Please change to cashDrawerStatus.")));

@property (readonly, nonatomic) StarIoExtManagerStatus barcodeReaderConnectStatus __attribute__((unavailable("Not available. Please change to barcodeReaderStatus.")));
@end
