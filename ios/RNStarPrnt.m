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

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}
RCT_EXPORT_MODULE();

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

RCT_REMAP_METHOD(print, portName:(NSString *)portName
                 Emulation:(NSString *)emulation
                 sendPrintCommandWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    NSString *portSettings = [self getPortSettingsOption:emulation];
    
    StarIoExtEmulation Emulation = [self getEmulation:emulation];
    
    ISCBBuilder *builder = [StarIoExt createCommandBuilder:Emulation];
    
    [builder beginDocument];
    
    NSStringEncoding encoding = NSASCIIStringEncoding;
    
    [builder appendData:[@"Hello World \n \n \n" dataUsingEncoding:encoding]];
    
    [builder endDocument];
    
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

- (NSDictionary *)constantsToExport
{
    return @{ @"StarPRNT" : @(StarIoExtEmulationStarPRNT),
              @"StarPRNTL" : @(StarIoExtEmulationStarPRNTL),
              @"StarLine" : @(StarIoExtEmulationStarLine)};
};

@end


