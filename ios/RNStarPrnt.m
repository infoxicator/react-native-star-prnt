//
//  RNStarPrnt.m
//
//
//  Created by Ruben Casas on 06/05/18.
//
//

#import "RNStarPrnt.h"
#import <StarIO/SMPort.h>
#import <StarIO_Extension/StarIoExt.h>
#import <StarIO_Extension/StarIoExtManager.h>
#import "Communication.h"

@implementation RNStarPrnt

 bool RNStarPrnt_hasListeners;

- (dispatch_queue_t)methodQueue
{
    return dispatch_queue_create("net.infoxication.react.starprnt", DISPATCH_QUEUE_SERIAL);
}

+ (BOOL)requiresMainQueueSetup
{
    return YES;
}
RCT_EXPORT_MODULE();

- (NSArray<NSString *> *)supportedEvents
{
    return @[@"starPrntData"];
}

// Will be called when this module's first listener is added.
-(void)startObserving {
    RNStarPrnt_hasListeners = YES;
    // Set up any upstream listeners or background tasks as necessary
}

// Will be called when this module's last listener is removed, or on dealloc.
-(void)stopObserving {
    RNStarPrnt_hasListeners = NO;
    // Remove upstream listeners, stop unnecessary background tasks
}


RCT_REMAP_METHOD(portDiscovery, portType:(NSString *)portType
                 findPrintersWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableArray *info = [[NSMutableArray alloc] init];
    
    if ([portType isEqualToString:@"All"] || [portType isEqualToString:@"Bluetooth"]) {
        NSArray *btPortInfoArray = [SMPort searchPrinter:@"BT:"];
        for (PortInfo *p in btPortInfoArray) {
            [info addObject:[self portInfoToDictionary:p]];
        }
    }
    
    if ([portType isEqualToString:@"All"] || [portType isEqualToString:@"LAN"]) {
        NSArray *lanPortInfoArray = [SMPort searchPrinter:@"TCP:"];
        for (PortInfo *p in lanPortInfoArray) {
            [info addObject:[self portInfoToDictionary:p]];
        }
    }
    
    if ([portType isEqualToString:@"All"] || [portType isEqualToString:@"BluetoothLE"]) {
        NSArray *btPortInfoArray = [SMPort searchPrinter:@"BLE:"];
        for (PortInfo *p in btPortInfoArray) {
            [info addObject:[self portInfoToDictionary:p]];
        }
    }
    
    if ([portType isEqualToString:@"All"] || [portType isEqualToString:@"USB"]) {
        NSArray *usbPortInfoArray = [SMPort searchPrinter:@"USB:"];
        for (PortInfo *p in usbPortInfoArray) {
            [info addObject:[self portInfoToDictionary:p]];
        }
    }
    if (info) {
        resolve(info);
    } else {
        NSError *error;
        reject(@"no_printers_found", @"Printers not found", error);
    }
}

RCT_REMAP_METHOD(checkStatus, portName:(NSString *)portName
                 emulation:(NSString *)emulation
                 checkStatusWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    SMPort *port = nil;
    StarPrinterStatus_2 status;
    NSString *portSettings = [self getPortSettingsOption:emulation];
    @try {
        
        port = [SMPort getPort:portName :portSettings :10000];     // 10000mS!!!
        
        // Sleep to avoid a problem which sometimes cannot communicate with Bluetooth.
        
        NSOperatingSystemVersion version = {11, 0, 0};
        BOOL isOSVer11OrLater = [[NSProcessInfo processInfo] isOperatingSystemAtLeastVersion:version];
        if ((isOSVer11OrLater) && ([portName.uppercaseString hasPrefix:@"BT:"])) {
            [NSThread sleepForTimeInterval:0.2];
        }
        
        [port getParsedStatus:&status :2];
        NSDictionary *firmwareInformation = [[NSMutableDictionary alloc] init];
        @try {
            firmwareInformation = [port getFirmwareInformation];
        }
        @catch (PortException *exception) {
            //unable to get Firmware
        }
        
        NSDictionary *statusDictionary = [self portStatusToDictionary:status :firmwareInformation];
        resolve (statusDictionary);
    }
    @catch (NSError *exception) {
        NSLog(@"Port exception");
        reject(@"status_error", @"Error getting printer status", exception);
    }
    @finally {
        if (port != nil) {
            [SMPort releasePort:port];
        }
    }
}
RCT_REMAP_METHOD(connect, portName:(NSString *)portName
                 emulation:(NSString *)emulation
                 hasBarcodeReader:(nonnull NSNumber *)hasBarcodeReader
                 connectWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{

        NSString *portSettings = [self getPortSettingsOption:emulation];
    
        if (portName != nil && portName != (id)[NSNull null]){
            if ([hasBarcodeReader isEqual:@(YES)]) {
                _printerManager = [[StarIoExtManager alloc] initWithType:StarIoExtManagerTypeWithBarcodeReader
                                                                portName:portName
                                                            portSettings:portSettings
                                                         ioTimeoutMillis:10000];
            } else {
                _printerManager = [[StarIoExtManager alloc] initWithType:StarIoExtManagerTypeStandard
                                                                portName:portName
                                                            portSettings:portSettings
                                                         ioTimeoutMillis:10000];
            }
            _printerManager.delegate = self;
        }
    
    
        if ([_printerManager connect] == NO) {
            NSDictionary *userInfo = @{
                                       NSLocalizedDescriptionKey: NSLocalizedString(@"Fail to Open Port", nil),
                                       NSLocalizedFailureReasonErrorKey: NSLocalizedString(@"", nil),
                                       NSLocalizedRecoverySuggestionErrorKey: NSLocalizedString(@"Check the printer is online", nil)
                                       };
            NSError *error = [[NSError alloc] initWithDomain:@"StarPrntErrorDomain"
                                                        code:-1 userInfo:userInfo];
            
            reject(@"Fail to Open Port.", @"",error);
            
        }else{
            BOOL result = YES;
            NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
            [resultMessage setObject:[NSNumber numberWithBool:result == SM_TRUE] forKey:@"result"];
            [resultMessage setObject:@"Send Commands" forKey:@"title"];
            [resultMessage setObject:@"Printer Connected!" forKey:@"message"];
    
            resolve(resultMessage);
            
        }
}
RCT_REMAP_METHOD(disconnect,
                 disconnectWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    if (_printerManager != nil && _printerManager.port != nil) {
        if([_printerManager disconnect] == NO){
            NSDictionary *userInfo = @{
                                       NSLocalizedDescriptionKey: NSLocalizedString(@"Communication Error", nil),
                                       NSLocalizedFailureReasonErrorKey: NSLocalizedString(@"", nil),
                                       NSLocalizedRecoverySuggestionErrorKey: NSLocalizedString(@"Check the printer is online", nil)
                                       };
            NSError *error = [[NSError alloc] initWithDomain:@"StarPrntErrorDomain"
                                                        code:-1 userInfo:userInfo];
            
            reject(@"Communication Error.", @"",error);
            
        }else{
            BOOL result = YES;
            NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
            [resultMessage setObject:[NSNumber numberWithBool:result == SM_TRUE] forKey:@"result"];
            [resultMessage setObject:@"Send Commands" forKey:@"title"];
            [resultMessage setObject:@"Printer Disconnected!" forKey:@"message"];
            
            resolve(resultMessage);
            
        };
    }
}

RCT_REMAP_METHOD(print, portName:(NSString *)portName
                 emulation:(NSString *)emulation
                 printCommands:(NSArray *) printCommands
                 sendPrintCommandWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    NSString *portSettings = [self getPortSettingsOption:emulation];
    
    StarIoExtEmulation Emulation = [self getEmulation:emulation];
    
    ISCBBuilder *builder = [StarIoExt createCommandBuilder:Emulation];
    
    [builder beginDocument];
    
     [self appendCommands:builder
               printCommands:printCommands];

        [builder endDocument];
    
    [builder endDocument];
    
    if(portName != nil && portName != (id)[NSNull null]){
    
    [Communication sendCommands:[builder.commands copy]
                       portName:portName
                   portSettings:portSettings
                        timeout:10000
              completionHandler:^(BOOL result, NSString *title, NSString *message) {
                  if(result == YES){
                      NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
                      [resultMessage setObject:[NSNumber numberWithBool:result == SM_TRUE] forKey:@"result"];
                      [resultMessage setObject:title forKey:@"title"];
                      [resultMessage setObject:message forKey:@"message"];
                      
                      resolve(resultMessage);
                  }else{
                      NSDictionary *userInfo = @{
                                                 NSLocalizedDescriptionKey: NSLocalizedString(title, nil),
                                                 NSLocalizedFailureReasonErrorKey: NSLocalizedString(message, nil),
                                                 NSLocalizedRecoverySuggestionErrorKey: NSLocalizedString(@"Check the printer is online and connected to the device", nil)
                                                 };
                      NSError *error = [[NSError alloc] initWithDomain:@"StarPrntErrorDomain"
                                                                  code:-1 userInfo:userInfo];
                      reject(title, message, error);
                  }
              }];
    }else{ //Use StarIOExtManager and send command to connected printer
        [Communication sendCommands:[builder.commands copy]
                           port:_printerManager.port
                  completionHandler:^(BOOL result, NSString *title, NSString *message) {
                      if(result == YES){
                          NSMutableDictionary *resultMessage = [[NSMutableDictionary alloc] init];
                          [resultMessage setObject:[NSNumber numberWithBool:result == SM_TRUE] forKey:@"result"];
                          [resultMessage setObject:title forKey:@"title"];
                          [resultMessage setObject:message forKey:@"message"];
                          
                          resolve(resultMessage);
                      }else{
                          NSDictionary *userInfo = @{
                                                     NSLocalizedDescriptionKey: NSLocalizedString(title, nil),
                                                     NSLocalizedFailureReasonErrorKey: NSLocalizedString(message, nil),
                                                     NSLocalizedRecoverySuggestionErrorKey: NSLocalizedString(@"Check the printer is online and connected to the device", nil)
                                                     };
                          NSError *error = [[NSError alloc] initWithDomain:@"StarPrntErrorDomain"
                                                                      code:-1 userInfo:userInfo];
                          reject(title, message, error);
                      }
                  }];
        
    }
    
}
#pragma mark -
#pragma mark Printer Events
#pragma mark -
-(void)didPrinterCoverOpen {
        [self sendData:@"printerCoverOpen" data:nil];
}

-(void)didPrinterCoverClose {
        [self sendData:@"printerCoverClose" data:nil];
}

-(void)didPrinterImpossible {
        [self sendData:@"printerImpossible" data:nil];
}

-(void)didPrinterOnline {
        [self sendData:@"printerOnline" data:nil];
}

-(void)didPrinterOffline {
        [self sendData:@"printerOffline" data:nil];
}

-(void)didPrinterPaperEmpty {
        [self sendData:@"printerPaperEmpty" data:nil];
}

-(void)didPrinterPaperNearEmpty {
        [self sendData:@"printerPaperNearEmpty" data:nil];
}

-(void)didPrinterPaperReady {
        [self sendData:@"printerPaperReady" data:nil];
}

#pragma mark -
#pragma mark Cash drawer events
#pragma mark -

-(void)didCashDrawerOpen {
        [self sendData:@"cashDrawerOpen" data:nil];
}
-(void)didCashDrawerClose {
        [self sendData:@"cashDrawerClose" data:nil];
}


-(void)didBarcodeReaderImpossible {
        [self sendData:@"barcodeReaderImpossible" data:nil];
}

-(void)didBarcodeReaderConnect {
        [self sendData:@"barcodeReaderConnect" data:nil];
}

-(void)didBarcodeReaderDisconnect {
        [self sendData:@"barcodeReaderDisconnect" data:nil];
}

- (void)didBarcodeDataReceive:(NSData *)data {
        NSMutableString *text = [NSMutableString stringWithString:@""];
        const uint8_t *p = [data bytes];
        for (int i = 0; i < data.length; i++) {
            uint8_t ch = *(p + i);
            if(ch >= 0x20 && ch <= 0x7f) {
                [text appendFormat:@"%c", (char) ch];
            }
            else if (ch == 0x0d) {
                // text = [NSMutableString stringWithString:@""];
            }
        }
        [self sendData:@"barcodeDataReceive" data:text];
}

- (void)sendData:(NSString *)dataType data:(NSString *)data {
    
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setObject:dataType forKey:@"dataType"];
        if (data != nil) {
            [dict setObject:data forKey:@"data"];
        }
     if (RNStarPrnt_hasListeners) {
         [self sendEventWithName:@"starPrntData" body:dict];
     }
}


#pragma mark -
#pragma mark Util
#pragma mark -

- (NSMutableDictionary*)portInfoToDictionary:(PortInfo *)portInfo {
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[portInfo portName] forKey:@"portName"];
    [dict setObject:[portInfo macAddress] forKey:@"macAddress"];
    [dict setObject:[portInfo modelName] forKey:@"modelName"];
    return dict;
}

-(NSString *)getPortSettingsOption:(NSString *)emulation {
    NSString *portSettings = [NSString string];
    
    if([emulation isEqualToString:@"EscPosMobile"]){
        portSettings = [@"mini" stringByAppendingString:portSettings];
    }else if([emulation isEqualToString:@"EscPos"]){
        portSettings = [@"escpos" stringByAppendingString:portSettings];
    }else if([emulation isEqualToString:@"StarPRNT"] || [emulation isEqualToString:@"StarPRNTL"]){
        portSettings = [@"Portable;l" stringByAppendingString:portSettings];
    }
    return portSettings;
}

- (NSMutableDictionary*)portStatusToDictionary:(StarPrinterStatus_2)status :(NSDictionary*)firmwareInformation {
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSNumber numberWithBool:status.coverOpen == SM_TRUE] forKey:@"coverOpen"];
    [dict setObject:[NSNumber numberWithBool:status.offline == SM_TRUE] forKey:@"offline"];
    [dict setObject:[NSNumber numberWithBool:status.overTemp == SM_TRUE] forKey:@"overTemp"];
    [dict setObject:[NSNumber numberWithBool:status.cutterError == SM_TRUE] forKey:@"cutterError"];
    [dict setObject:[NSNumber numberWithBool:status.receiptPaperEmpty == SM_TRUE] forKey:@"receiptPaperEmpty"];
    [dict addEntriesFromDictionary:firmwareInformation];
    
    return dict;
}

-(StarIoExtEmulation)getEmulation:(NSString *)emulation{
    
    if([emulation isEqualToString:@"StarPRNT"]) return StarIoExtEmulationStarPRNT;
    else if ([emulation isEqualToString:@"StarPRNTL"]) return StarIoExtEmulationStarPRNTL;
    else if ([emulation isEqualToString:@"StarLine"]) return StarIoExtEmulationStarLine;
    else if ([emulation isEqualToString:@"StarGraphic"]) return StarIoExtEmulationStarGraphic;
    else if ([emulation isEqualToString:@"EscPos"]) return StarIoExtEmulationEscPos;
    else if ([emulation isEqualToString:@"EscPosMobile"]) return StarIoExtEmulationEscPosMobile;
    else if ([emulation isEqualToString:@"StarDotImpact"]) return StarIoExtEmulationStarDotImpact;
    else return StarIoExtEmulationStarLine;
}
-(void)appendCommands:(ISCBBuilder *)builder
       printCommands:(NSArray *)printCommands {
    
    NSStringEncoding encoding = NSASCIIStringEncoding;
    
    for (id command in printCommands){
        if ([command valueForKey:@"appendInternational"]) [builder appendInternational:[self getInternational:[command valueForKey:@"appendInternational"]]];
        else if ([command valueForKey:@"appendCharacterSpace"]) [builder appendCharacterSpace:[[command valueForKey:@"appendCharacterSpace"] intValue]];
        else if ([command valueForKey:@"appendEncoding"]) encoding = [self getEncoding:[command valueForKey:@"appendEncoding"]];
        else if ([command valueForKey:@"appendCodePage"]) [builder appendCodePage:[self getCodePageType:[command valueForKey:@"appendCodePage"]]];
        else if ([command valueForKey:@"append"]) [builder appendData:[[command valueForKey:@"append"] dataUsingEncoding:encoding]];
        else if ([command valueForKey:@"appendRaw"]) [builder appendRawData:[[command valueForKey:@"appendRaw"] dataUsingEncoding:encoding]];
        else if ([command valueForKey:@"appendEmphasis"]) [builder appendDataWithEmphasis:[[command valueForKey:@"appendEmphasis"] dataUsingEncoding:encoding]];
        else if ([command valueForKey:@"enableEmphasis"]) [builder appendEmphasis:[[command valueForKey:@"enableEmphasis"] boolValue]];
        else if ([command valueForKey:@"appendInvert"]) [builder appendDataWithInvert:[[command valueForKey:@"appendInvert"] dataUsingEncoding:encoding]];
        else if ([command valueForKey:@"enableInvert"]) [builder appendInvert:[[command valueForKey:@"enableInvert"] boolValue]];
        else if ([command valueForKey:@"appendUnderline"]) [builder appendDataWithUnderLine:[[command valueForKey:@"appendUnderline"] dataUsingEncoding:encoding]];
        else if ([command valueForKey:@"enableUnderline"]) [builder appendUnderLine:[[command valueForKey:@"enableUnderline"] boolValue]];
        else if ([command valueForKey:@"appendLineFeed"]) [builder appendLineFeed:[[command valueForKey:@"appendLineFeed"] intValue]];
        else if ([command valueForKey:@"appendUnitFeed"]) [builder appendUnitFeed:[[command valueForKey:@"appendUnitFeed"] intValue]];
        else if ([command valueForKey:@"appendLineSpace"]) [builder appendLineSpace:[[command valueForKey:@"appendLineSpace"] intValue]];
        else if ([command valueForKey:@"appendFontStyle"])[builder appendFontStyle:[self getFont:[command valueForKey:@"appendFontStyle"]]];
        else if ([command valueForKey:@"appendCutPaper"]) [builder appendCutPaper:[self getCutPaperAction:[command valueForKey:@"appendCutPaper"]]];
        else if ([command valueForKey:@"openCashDrawer"])[builder appendPeripheral:[self getPeripheralChannel:[command valueForKey:@"openCashDrawer"]]];
        else if ([command valueForKey:@"appendBlackMark"]) [builder appendBlackMark:[self getBlackMarkType:[command valueForKey:@"appendBlackMark"]]];
        else if ([command valueForKey:@"appendBytes"]){
            NSMutableArray *byteArray = nil;
            byteArray = [command valueForKey:@"appendBytes"];
            int count = (int)[byteArray count];
            unsigned char buffer[count + 1];
            for (int i=0; i< count; i++){
                buffer[i] = [[byteArray objectAtIndex:i] unsignedCharValue];
            }
            [builder appendBytes:buffer length:sizeof(buffer)-1];
        }
        else if ([command valueForKey:@"appendRawBytes"]){
            NSMutableArray *rawByteArray = nil;
            rawByteArray = [command valueForKey:@"appendRawBytes"];
            int rawCount = (int)[rawByteArray count];
            unsigned char rawBuffer[rawCount + 1];
            for (int i=0; i< rawCount; i++){
                rawBuffer[i] = [[rawByteArray objectAtIndex:i] unsignedCharValue];
            }
            [builder appendRawBytes:rawBuffer length:sizeof(rawBuffer)-1];
        }
        else if ([command valueForKey:@"appendAbsolutePosition"]){
            if([command valueForKey:@"data"]) [builder appendDataWithAbsolutePosition:[[command valueForKey:@"data"] dataUsingEncoding:encoding]
                                                                             position:[[command valueForKey:@"appendAbsolutePosition"] intValue]];
            else [builder appendAbsolutePosition:[[command valueForKey:@"appendAbsolutePosition"] intValue]];
        }
        else if ([command valueForKey:@"appendAlignment"]) {
             if([command valueForKey:@"data"]) [builder appendDataWithAlignment:[[command valueForKey:@"data"] dataUsingEncoding:encoding]
                                                                       position:[self getAlignment:[command valueForKey:@"appendAlignment"]]];
             else [builder appendAlignment:[self getAlignment:[command valueForKey:@"appendAlignment"]]];
        }
        else if ([command valueForKey:@"appendHorizontalTabPosition"]) {
            NSArray<NSNumber *> *tabPositionArray = nil;
            tabPositionArray = [command valueForKey:@"appendHorizontalTabPosition"];
            if (tabPositionArray != nil && tabPositionArray != (id)[NSNull null])[builder appendHorizontalTabPosition:tabPositionArray];
        }
        else if ([command valueForKey:@"appendMultiple"]) {
            int width = ([[command valueForKey:@"width"] intValue]) ? [[command valueForKey:@"width"] intValue]: 2;
            int height = ([[command valueForKey:@"height"] intValue]) ? [[command valueForKey:@"height"] intValue]: 2;
            [builder appendDataWithMultiple:[[command valueForKey:@"appendMultiple"] dataUsingEncoding:encoding] width:width height:height];
        }
        else if ([command valueForKey:@"enableMultiple"]) {
            int width = ([[command valueForKey:@"width"] intValue]) ? [[command valueForKey:@"width"] intValue]: 1;
            int height = ([[command valueForKey:@"height"] intValue]) ? [[command valueForKey:@"height"] intValue]: 1;
            if([[command valueForKey:@"enableMultiple"] boolValue] == YES){
                [builder appendMultiple:width height:height];
            }else{
                [builder appendMultiple:1 height:1];
            }
        }
        else if ([command valueForKey:@"appendLogo"]) {
            if([command valueForKey:@"logoSize"]) [builder appendLogo:[self getLogoSize:[command valueForKey:@"logoSize"]]
                                                               number:[[command valueForKey:@"appendLogo"] intValue]];
            else [builder appendLogo:SCBLogoSizeNormal number:[[command valueForKey:@"appendLogo"] intValue]];
        }
        else if ([command valueForKey:@"appendBarcode"]) {
            SCBBarcodeSymbology barcodeSymbology = [self getBarcodeSymbology:[command valueForKey:@"BarcodeSymbology"]];
            SCBBarcodeWidth barcodeWidth = [self getBarcodeWidth:[command valueForKey:@"BarcodeWidth"]];
            int height = ([command valueForKey:@"height"]) ? [[command valueForKey:@"height"] intValue]: 40;
            BOOL hri = ([[command valueForKey:@"hri"] boolValue]  == NO) ? NO : YES;
            
            if([command valueForKey:@"absolutePosition"]){
                int position = ([[command valueForKey:@"absolutePosition"] intValue]) ? [[command valueForKey:@"absolutePosition"] intValue]: 40;
                [builder appendBarcodeDataWithAbsolutePosition:[[command valueForKey:@"appendBarcode"] dataUsingEncoding:encoding]
                                                     symbology:barcodeSymbology width:barcodeWidth height:height hri:hri position:position];
            }
            else if ([command valueForKey:@"alignment"]){
                SCBAlignmentPosition alignment = [self getAlignment:[command valueForKey:@"alignment"]];
                [builder appendBarcodeDataWithAlignment:[[command valueForKey:@"appendBarcode"] dataUsingEncoding:encoding]
                                              symbology:barcodeSymbology width:barcodeWidth height:height hri:hri position:alignment];
            }
            else [builder appendBarcodeData:[[command valueForKey:@"appendBarcode"] dataUsingEncoding:encoding]
                                  symbology:barcodeSymbology width:barcodeWidth height:height hri:hri];
            
        }
        else if ([command valueForKey:@"appendQrCode"]) {
            SCBQrCodeModel qrCodeModel = [self getQrCodeModel:[command valueForKey:@"QrCodeModel"]];
            SCBQrCodeLevel qrCodeLevel = [self getQrCodeLevel:[command valueForKey:@"QrCodeLevel"]];
            int cell = ([[command valueForKey:@"cell"] intValue]) ? [[command valueForKey:@"cell"] intValue]: 4;
            
            if([command valueForKey:@"absolutePosition"]){
                int position = ([[command valueForKey:@"absolutePosition"] intValue]) ? [[command valueForKey:@"absolutePosition"] intValue]: 40;
                [builder appendQrCodeDataWithAbsolutePosition:[[command valueForKey:@"appendQrCode"] dataUsingEncoding:encoding]
                                                          model:qrCodeModel level:qrCodeLevel cell:cell position:position];
            }
            else if ([command valueForKey:@"alignment"]){
                SCBAlignmentPosition alignment = [self getAlignment:[command valueForKey:@"alignment"]];
                [builder appendQrCodeDataWithAlignment:[[command valueForKey:@"appendQrCode"] dataUsingEncoding:encoding]
                                                 model:qrCodeModel level:qrCodeLevel cell:cell position:alignment];
            }
            else [builder appendQrCodeData:[[command valueForKey:@"appendQrCode"] dataUsingEncoding:encoding]
                                     model:qrCodeModel level:qrCodeLevel cell:cell];
        }
        else if ([command valueForKey:@"appendBitmap"]) {
            NSString *urlString = [command valueForKey:@"appendBitmap"];
            NSInteger width = ([command valueForKey:@"width"]) ? [[command valueForKey:@"width"] intValue] : 576;
            BOOL diffusion = ([[command valueForKey:@"diffusion"] boolValue] == NO) ? NO : YES;
            BOOL bothScale = ([[command valueForKey:@"bothScale"] boolValue]  == NO) ? NO : YES;
            SCBBitmapConverterRotation rotation = [self getBitmapConverterRotation:[command valueForKey:@"rotation"]];
            NSError *error = nil;
            NSURL *imageURL = [NSURL URLWithString:urlString];
            NSData *imageData = [NSData dataWithContentsOfURL:imageURL options:NSDataReadingUncached error:&error];

            if (error != nil) {
                NSURL *fileImageURL = [NSURL fileURLWithPath:urlString];
                imageData = [NSData dataWithContentsOfURL:fileImageURL];
            }

            UIImage *image = [UIImage imageWithData:imageData];
            
            if([command valueForKey:@"absolutePosition"]){
                int position = ([[command valueForKey:@"absolutePosition"] intValue]) ? [[command valueForKey:@"absolutePosition"] intValue]: 40;
                [builder appendBitmapWithAbsolutePosition:image diffusion:diffusion width:width bothScale:bothScale rotation:rotation position:position];
            }
            else if ([command valueForKey:@"alignment"]){
                SCBAlignmentPosition alignment = [self getAlignment:[command valueForKey:@"alignment"]];
                [builder appendBitmapWithAlignment:image diffusion:diffusion width:width bothScale:bothScale rotation:rotation position:alignment];
            }
            else [builder appendBitmap:image diffusion:diffusion width:width bothScale:bothScale rotation:rotation];
        }
        else if ([command valueForKey:@"appendBitmapText"]) {
            NSString *text = [command valueForKey:@"appendBitmapText"];
            NSInteger width = ([command valueForKey:@"width"]) ? [[command valueForKey:@"width"] intValue] : 576;
            NSString *fontName = ([command valueForKey:@"font"]) ? [command valueForKey:@"font"] : @"Menlo";
            NSInteger fontSize = ([command valueForKey:@"fontSize"]) ? [[command valueForKey:@"fontSize"] intValue] : 12;

            UIFont *font = [UIFont fontWithName:fontName size:fontSize * 2];
            UIImage *image = [self imageWithString:text font:font width:width];

            [builder appendBitmap:image diffusion:NO];
        }
    }
    
}
#pragma mark -
#pragma mark ISCBBuilder Constants
#pragma mark -

- (NSStringEncoding)getEncoding:(NSString *)encoding {
    if (encoding != nil && encoding != (id)[NSNull null]){
        if ([encoding isEqualToString:@"US-ASCII"]) return NSASCIIStringEncoding; //English
        else if ([encoding isEqualToString:@"Windows-1252"]) return NSWindowsCP1252StringEncoding; //French, German, Portuguese, Spanish
        else if ([encoding isEqualToString:@"Shift-JIS"]) return NSShiftJISStringEncoding; //Japanese
        else if ([encoding isEqualToString:@"Windows-1251"]) return NSWindowsCP1251StringEncoding; //Russian
        else if ([encoding isEqualToString:@"GB2312"]) return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000); // Simplified Chinese
        else if ([encoding isEqualToString:@"Big5"]) return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingBig5); // Traditional Chinese
        else if ([encoding isEqualToString:@"UTF-8"]) return NSUTF8StringEncoding; // UTF-8
        return NSWindowsCP1252StringEncoding;

    } else {
        return NSWindowsCP1252StringEncoding;
    }
}

- (SCBAlignmentPosition)getAlignment:(NSString *)alignment {
    if (alignment != nil && alignment != (id)[NSNull null]){
        if ([alignment caseInsensitiveCompare:@"left"] == NSOrderedSame) return SCBAlignmentPositionLeft;
        else if ([alignment caseInsensitiveCompare:@"center"] == NSOrderedSame) return SCBAlignmentPositionCenter;
        else if ([alignment caseInsensitiveCompare:@"right"] == NSOrderedSame)  return SCBAlignmentPositionRight;
        else return SCBAlignmentPositionLeft;
    } else {
        return SCBAlignmentPositionLeft;
    }
}

- (SCBInternationalType)getInternational:(NSString *)internationl {
    if (internationl != nil && internationl != (id)[NSNull null]){
        if ([internationl isEqualToString:@"US"] || [internationl isEqualToString:@"USA"]) return SCBInternationalTypeUSA;
        else if ([internationl isEqualToString:@"FR"] || [internationl isEqualToString:@"France"]) return SCBInternationalTypeFrance;
        else if ([internationl isEqualToString:@"UK"]) return SCBInternationalTypeUK;
        else if ([internationl isEqualToString:@"Germany"]) return SCBInternationalTypeGermany;
        else if ([internationl isEqualToString:@"Denmark"]) return SCBInternationalTypeDenmark;
        else if ([internationl isEqualToString:@"Sweden"]) return SCBInternationalTypeSweden;
        else if ([internationl isEqualToString:@"Italy"]) return SCBInternationalTypeItaly;
        else if ([internationl isEqualToString:@"Spain"]) return SCBInternationalTypeSpain;
        else if ([internationl isEqualToString:@"Japan"]) return SCBInternationalTypeJapan;
        else if ([internationl isEqualToString:@"Norway"]) return SCBInternationalTypeNorway;
        else if ([internationl isEqualToString:@"Denmark2"]) return SCBInternationalTypeDenmark2;
        else if ([internationl isEqualToString:@"Spain2"]) return SCBInternationalTypeSpain2;
        else if ([internationl isEqualToString:@"LatinAmerica"]) return SCBInternationalTypeLatinAmerica;
        else if ([internationl isEqualToString:@"Korea"]) return SCBInternationalTypeKorea;
        else if ([internationl isEqualToString:@"Ireland"]) return SCBInternationalTypeIreland;
        else if ([internationl isEqualToString:@"Legal"]) return SCBInternationalTypeLegal;
        else return SCBInternationalTypeUSA;
    } else
        return SCBInternationalTypeUSA;
}

- (SCBFontStyleType)getFont:(NSString *)font {
    if (font != nil && font != (id)[NSNull null]){
        if ([font isEqualToString:@"A"]) return SCBFontStyleTypeA;
        else if ([font isEqualToString:@"B"]) return SCBFontStyleTypeB;
        else return SCBFontStyleTypeA;
    } else
        return SCBFontStyleTypeA;
}

- (SCBCodePageType)getCodePageType:(NSString *)codePageType {
    if (codePageType != nil && codePageType != (id)[NSNull null]){
        if ([codePageType isEqualToString:@"CP437"]) return SCBCodePageTypeCP437;
        else if ([codePageType isEqualToString:@"CP737"]) return SCBCodePageTypeCP737;
        else if ([codePageType isEqualToString:@"CP772"]) return SCBCodePageTypeCP772;
        else if ([codePageType isEqualToString:@"CP774"]) return SCBCodePageTypeCP774;
        else if ([codePageType isEqualToString:@"CP851"]) return SCBCodePageTypeCP851;
        else if ([codePageType isEqualToString:@"CP852"]) return SCBCodePageTypeCP852;
        else if ([codePageType isEqualToString:@"CP855"]) return SCBCodePageTypeCP855;
        else if ([codePageType isEqualToString:@"CP857"]) return SCBCodePageTypeCP857;
        else if ([codePageType isEqualToString:@"CP858"]) return SCBCodePageTypeCP858;
        else if ([codePageType isEqualToString:@"CP860"]) return SCBCodePageTypeCP860;
        else if ([codePageType isEqualToString:@"CP861"]) return SCBCodePageTypeCP861;
        else if ([codePageType isEqualToString:@"CP862"]) return SCBCodePageTypeCP862;
        else if ([codePageType isEqualToString:@"CP863"]) return SCBCodePageTypeCP863;
        else if ([codePageType isEqualToString:@"CP864"]) return SCBCodePageTypeCP864;
        else if ([codePageType isEqualToString:@"CP865"]) return SCBCodePageTypeCP866;
        else if ([codePageType isEqualToString:@"CP869"]) return SCBCodePageTypeCP869;
        else if ([codePageType isEqualToString:@"CP874"]) return SCBCodePageTypeCP874;
        else if ([codePageType isEqualToString:@"CP928"]) return SCBCodePageTypeCP928;
        else if ([codePageType isEqualToString:@"CP932"]) return SCBCodePageTypeCP932;
        else if ([codePageType isEqualToString:@"CP999"]) return SCBCodePageTypeCP999;
        else if ([codePageType isEqualToString:@"CP1001"]) return SCBCodePageTypeCP1001;
        else if ([codePageType isEqualToString:@"CP1250"]) return SCBCodePageTypeCP1250;
        else if ([codePageType isEqualToString:@"CP1251"]) return SCBCodePageTypeCP1251;
        else if ([codePageType isEqualToString:@"CP1252"]) return SCBCodePageTypeCP1252;
        else if ([codePageType isEqualToString:@"CP2001"]) return SCBCodePageTypeCP2001;
        else if ([codePageType isEqualToString:@"CP3001"]) return SCBCodePageTypeCP3001;
        else if ([codePageType isEqualToString:@"CP3002"]) return SCBCodePageTypeCP3002;
        else if ([codePageType isEqualToString:@"CP3011"]) return SCBCodePageTypeCP3011;
        else if ([codePageType isEqualToString:@"CP3012"]) return SCBCodePageTypeCP3012;
        else if ([codePageType isEqualToString:@"CP3021"]) return SCBCodePageTypeCP3021;
        else if ([codePageType isEqualToString:@"CP3041"]) return SCBCodePageTypeCP3041;
        else if ([codePageType isEqualToString:@"CP3840"]) return SCBCodePageTypeCP3840;
        else if ([codePageType isEqualToString:@"CP3841"]) return SCBCodePageTypeCP3841;
        else if ([codePageType isEqualToString:@"CP3843"]) return SCBCodePageTypeCP3843;
        else if ([codePageType isEqualToString:@"CP3845"]) return SCBCodePageTypeCP3845;
        else if ([codePageType isEqualToString:@"CP3846"]) return SCBCodePageTypeCP3846;
        else if ([codePageType isEqualToString:@"CP3847"]) return SCBCodePageTypeCP3847;
        else if ([codePageType isEqualToString:@"CP3848"]) return SCBCodePageTypeCP3848;
        else if ([codePageType isEqualToString:@"UTF8"]) return SCBCodePageTypeUTF8;
        else if ([codePageType isEqualToString:@"Blank"]) return SCBCodePageTypeBlank;
        else return SCBCodePageTypeCP998;
    } else
        return SCBCodePageTypeCP998;
}

-(SCBCutPaperAction)getCutPaperAction:(NSString *)cutPaperAction {
    if (cutPaperAction != nil && cutPaperAction != (id)[NSNull null]){
        if([cutPaperAction isEqualToString:@"FullCut"]) return SCBCutPaperActionFullCut;
        else if([cutPaperAction isEqualToString:@"FullCutWithFeed"]) return SCBCutPaperActionFullCutWithFeed;
        else if([cutPaperAction isEqualToString:@"PartialCut"]) return SCBCutPaperActionPartialCut;
        else if([cutPaperAction isEqualToString:@"PartialCutWithFeed"]) return SCBCutPaperActionPartialCutWithFeed;
        else return SCBCutPaperActionPartialCutWithFeed;
    }else
        return SCBCutPaperActionPartialCutWithFeed;
}
-(SCBPeripheralChannel) getPeripheralChannel:(NSNumber *)peripheralChannel{
    if (peripheralChannel != nil ){
        if([peripheralChannel intValue]  == 1) return SCBPeripheralChannelNo1;
        else if([peripheralChannel intValue] == 2) return SCBPeripheralChannelNo2;
        else return SCBPeripheralChannelNo1;
    }else
        return SCBPeripheralChannelNo1;
}
-(SCBBlackMarkType) getBlackMarkType:(NSString *) blackMarkType{
    if (blackMarkType != nil && blackMarkType != (id)[NSNull null]){
        if([blackMarkType isEqualToString:@"Valid"]) return SCBBlackMarkTypeValid;
        else if([blackMarkType isEqualToString:@"Invalid"]) return SCBBlackMarkTypeInvalid;
        else if([blackMarkType isEqualToString:@"ValidWithDetection"]) return SCBBlackMarkTypeValidWithDetection;
            else return SCBBlackMarkTypeValid;
    }else
        return SCBBlackMarkTypeValid;
}
-(SCBLogoSize) getLogoSize:(NSString *) logoSize{
    if (logoSize != nil && logoSize != (id)[NSNull null]){
        if([logoSize isEqualToString:@"Normal"]) return SCBLogoSizeNormal;
        else if([logoSize isEqualToString:@"DoubleWidth"]) return SCBLogoSizeDoubleWidth;
        else if([logoSize isEqualToString:@"DoubleHeight"]) return SCBLogoSizeDoubleHeight;
        else if([logoSize isEqualToString:@"DoubleWidthDoubleHeight"]) return SCBLogoSizeDoubleWidthDoubleHeight;
        else return SCBLogoSizeNormal;
    }else
  return SCBLogoSizeNormal;
}
-(SCBBarcodeSymbology) getBarcodeSymbology:(NSString *) barcodeSymbology{
    if (barcodeSymbology != nil && barcodeSymbology != (id)[NSNull null]){
        if([barcodeSymbology isEqualToString:@"Code128"]) return SCBBarcodeSymbologyCode128;
        else if([barcodeSymbology isEqualToString:@"Code39"]) return SCBBarcodeSymbologyCode39;
        else if([barcodeSymbology isEqualToString:@"Code93"]) return SCBBarcodeSymbologyCode128;
        else if([barcodeSymbology isEqualToString:@"ITF"]) return SCBBarcodeSymbologyITF;
        else if([barcodeSymbology isEqualToString:@"JAN8"]) return SCBBarcodeSymbologyJAN8;
        else if([barcodeSymbology isEqualToString:@"JAN13"]) return SCBBarcodeSymbologyJAN13;
        else if([barcodeSymbology isEqualToString:@"NW7"]) return SCBBarcodeSymbologyNW7;
        else if([barcodeSymbology isEqualToString:@"UPCA"]) return SCBBarcodeSymbologyUPCA;
        else if([barcodeSymbology isEqualToString:@"UPCE"]) return SCBBarcodeSymbologyUPCE;
        else return SCBBarcodeSymbologyCode128;
    }else
        return SCBBarcodeSymbologyCode128;
}
-(SCBBarcodeWidth) getBarcodeWidth:(NSString *) barcodeWidth{
    if (barcodeWidth != nil && barcodeWidth != (id)[NSNull null]){
        if([barcodeWidth isEqualToString:@"Mode1"]) return SCBBarcodeWidthMode1;
        else if([barcodeWidth isEqualToString:@"Mode2"]) return SCBBarcodeWidthMode2;
        else if([barcodeWidth isEqualToString:@"Mode3"]) return SCBBarcodeWidthMode3;
        else if([barcodeWidth isEqualToString:@"Mode4"]) return SCBBarcodeWidthMode4;
        else if([barcodeWidth isEqualToString:@"Mode5"]) return SCBBarcodeWidthMode5;
        else if([barcodeWidth isEqualToString:@"Mode6"]) return SCBBarcodeWidthMode6;
        else if([barcodeWidth isEqualToString:@"Mode7"]) return SCBBarcodeWidthMode7;
        else if([barcodeWidth isEqualToString:@"Mode8"]) return SCBBarcodeWidthMode8;
        else if([barcodeWidth isEqualToString:@"Mode9"]) return SCBBarcodeWidthMode9;
        else return SCBBarcodeWidthMode2;
    }else
        return SCBBarcodeWidthMode2;
}
-(SCBQrCodeModel) getQrCodeModel:(NSString *) qrCodeModel{
    if (qrCodeModel != nil && qrCodeModel != (id)[NSNull null]){
        if([qrCodeModel isEqualToString:@"No1"]) return SCBQrCodeModelNo1;
        else if([qrCodeModel isEqualToString:@"No2"]) return SCBQrCodeModelNo2;
        else return SCBQrCodeModelNo1;
    }else
        return SCBQrCodeModelNo1;
}
-(SCBQrCodeLevel) getQrCodeLevel:(NSString *) qrCodeLevel {
    if (qrCodeLevel != nil && qrCodeLevel != (id)[NSNull null]){
        if([qrCodeLevel isEqualToString:@"H"]) return SCBQrCodeLevelH;
        else if([qrCodeLevel isEqualToString:@"L"]) return SCBQrCodeLevelL;
        else if([qrCodeLevel isEqualToString:@"M"]) return SCBQrCodeLevelM;
        else if([qrCodeLevel isEqualToString:@"Q"]) return SCBQrCodeLevelQ;
        else return SCBQrCodeLevelH;
    }else
        return SCBQrCodeLevelH;
}
-(SCBBitmapConverterRotation) getBitmapConverterRotation:(NSString *) rotation {
    if (rotation != nil && rotation != (id)[NSNull null]){
        if([rotation isEqualToString:@"Normal"]) return SCBBitmapConverterRotationNormal;
        else if([rotation isEqualToString:@"Left90"]) return SCBBitmapConverterRotationLeft90;
        else if([rotation isEqualToString:@"Right90"]) return SCBBitmapConverterRotationRight90;
        else if([rotation isEqualToString:@"Rotate180"]) return SCBBitmapConverterRotationRotate180;
        else return SCBBitmapConverterRotationNormal;
    }else
        return SCBBitmapConverterRotationNormal;
}

- (NSDictionary *)constantsToExport
{
    return @{ @"StarPRNT" : @(StarIoExtEmulationStarPRNT),
              @"StarPRNTL" : @(StarIoExtEmulationStarPRNTL),
              @"StarLine" : @(StarIoExtEmulationStarLine)};
};

- (UIImage *)imageWithString:(NSString *)string font:(UIFont *)font width:(CGFloat)width {
    NSDictionary *attributeDic = @{NSFontAttributeName:font};
    
    CGSize size = [string boundingRectWithSize:CGSizeMake(width, 10000)
                                       options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingTruncatesLastVisibleLine
                                    attributes:attributeDic
                                       context:nil].size;
    
    if ([UIScreen.mainScreen respondsToSelector:@selector(scale)]) {
        if (UIScreen.mainScreen.scale == 2.0) {
            UIGraphicsBeginImageContextWithOptions(size, NO, 1.0);
        } else {
            UIGraphicsBeginImageContext(size);
        }
    } else {
        UIGraphicsBeginImageContext(size);
    }
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    [[UIColor whiteColor] set];
    
    CGRect rect = CGRectMake(0, 0, size.width + 1, size.height + 1);
    
    CGContextFillRect(context, rect);
    
    NSDictionary *attributes = @ {
        NSForegroundColorAttributeName:[UIColor blackColor],
                   NSFontAttributeName:font
    };
    
    [string drawInRect:rect withAttributes:attributes];
    
    UIImage *imageToPrint = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return imageToPrint;
}

@end


