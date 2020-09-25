//
//  PrinterManager.h
//  BluetoothSettingUtility
//
//  Created by u3237 on 13/03/06.
//  Copyright (c) 2013年 Star Micronics co.,ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum _SMDeviceType {
    SMDeviceTypeUnknown = 0,
    SMDeviceTypeDesktopPrinter,
    SMDeviceTypePortablePrinter,
    SMDeviceTypeDKAirCash,
} SMDeviceType;

typedef enum _SMBluetoothSecurity {
    SMBluetoothSecurityDisable,
    SMBluetoothSecuritySSP,
    SMBluetoothSecurityPINcode
} SMBluetoothSecurity;

typedef enum _SMBluetoothSettingCapability {
    SMBluetoothSettingCapabilitySupport,
    SMBluetoothSettingCapabilityNoSupport
} SMBluetoothSettingCapability;

@interface SMBluetoothManager : NSObject

#pragma mark readonly property

@property(retain, readonly) NSString *portName;
@property(assign, readonly) SMDeviceType deviceType;
@property(assign, readonly) BOOL opened;

#pragma mark property

@property(retain) NSString *deviceName;
@property(retain) NSString *iOSPortName;
@property(assign) BOOL autoConnect;
@property(assign) SMBluetoothSecurity security;
@property(assign) BOOL pairingPermission;
@property(retain) NSString *pinCode;
@property(assign) BOOL discoveryPermission;
@property(assign) BOOL bluetoothDiagnosticMode;

@property(assign, readonly) SMBluetoothSettingCapability deviceNameCapability;
@property(assign, readonly) SMBluetoothSettingCapability iOSPortNameCapability;
@property(assign, readonly) SMBluetoothSettingCapability autoConnectCapability;
@property(assign, readonly) SMBluetoothSettingCapability securityTypeCapability;
@property(assign, readonly) SMBluetoothSettingCapability pairingPermissionCapability;
@property(assign, readonly) SMBluetoothSettingCapability pinCodeCapability;
@property(assign, readonly) SMBluetoothSettingCapability discoveryPermissionCapability;
@property(assign, readonly) SMBluetoothSettingCapability bluetoothDiagnosticModeCapability;

#pragma mark Public API

- (id)initWithPortName:(NSString *)portName deviceType:(SMDeviceType)deviceType;
- (BOOL)open;
- (BOOL)loadSetting;
- (BOOL)apply;
- (void)close;

@end
