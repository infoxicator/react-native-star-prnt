/*
 *  @file SMProxiPRNTManager.h
 *  @framework StarIOPort
 *
 *  @discussion Entry point to Star Bluetooth Low Energy devices.
 *  @copyright 2014 Star Micronics Co., Ltd. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "SMBluetoothManager.h"


static NSString const *kSMPortSettings = @"Port Settings";
static NSString const *kSMDeviceType = @"Device Type";
static NSString const *kSMWithDrawer = @"With Drawer";
static NSString const *kSMDongleMACAddr = @"MAC Address";
static NSString const *kSMThreshouldRSSI = @"Threshold RSSI";
static NSString const *kSMNickName = @"Nick Name";

@protocol SMProxiPRNTManagerDelegate;

/*!
 *  Control class for Star ProxiPRNT.
 */
@interface SMProxiPRNTManager : NSObject <CBCentralManagerDelegate> {
    CBCentralManager *manager;
    NSMutableDictionary *mutableSettings;
    NSMutableDictionary *rssiData;
}

/*!
 *  Receiver to get events from SMProxiPRNTManager class.
 */
@property(retain, nonatomic) id <SMProxiPRNTManagerDelegate> delegate;

/*!
 *  Settings for Star ProxiPRNT.
 */
@property(retain, readwrite, getter = getSettings, setter = setSettings:) NSDictionary* settings;

/*!
 *  Get instance of SMProxiPRNTManager class by property.
 */
@property(retain, readonly, getter = retain) SMProxiPRNTManager* sharedManager;

/*!
 *  Get instance of SMProxiPRNTManager class.
 */
+ (SMProxiPRNTManager *)sharedManager;

/*!
 *  Start scanning Bluetooth Low Energy devices.
 *  Do not execute this method when printing data or opening the drawer.
 *  Execute 'stopScan' method to stop scanning BLE device before printing data or opening the drawer.
 *
 *  @return NO if calibrateActionArea is alive or duplicate execution with 'startScan' or 'calibrateActionArea'.
 */
- (BOOL)startScan;

/*!
 *  Start scanning Bluetooth Low Energy devices.
 *  Do not execute this method when printing data or opening the drawer.
 *  Execute 'stopScan' method to stop scanning BLE device before printing data or opening the drawer.
 *
 *  @param  samplingNumber Sampling number of RSSI
 *  @return NO if calibrateActionArea is alive or duplicate execution with 'startScan' or 'calibrateActionArea'.
 */
- (BOOL)startScan:(NSUInteger)samplingNumber;

/*!
 *  Stop scanning Bluetooth Low Energy devices.
 *  Execute 'stopScan' method to stop scanning BLE device before printing data or opening the drawer.
 */
- (void)stopScan;

/*!
 *  Adds the settings of the printer to be connected with the Star BLE devices.
 *
 *  @param portName     Identifies the printer to use.
 *  @param portSettings The settings for the port.
 *  @param useDrawer    Presence/absence of a cash drawer.
 *  @param MACAddr      MAC address of Star BLE dongle.
 *  @param Threshold    Threashold value of RSSI in dBm.
 *  @param nickName     Nick name to connect the Star BLE device and the POS Printer.
 *
 *  @note Throws PortException on failure.
 */
- (void)addSettingForPrinterPortName:(NSString *)portName portSettings:(NSString *)portSettings withDrawer:(BOOL)useDrawer dongleMACAddr:(NSString *)MACAddr RSSIthreshould:(NSNumber *)Threshold nickName:(NSString *)nickName;

/*!
 *  Adds the settings of the DK-AirCash to be connected with the Star BLE devices.
 *
 *  @param portName     Identifies the DK-AirCash to use.
 *  @param portSettings The settings for the port.
 *  @param MACAddr      MAC address of Star BLE dongle.
 *  @param Threshold    Threashold value of RSSI in dBm.
 *  @param nickName     Nick name to connect the Star BLE device and the DK-AirCash.
 *
 *  @note Throws PortException on failure.
 */
- (void)addSettingForDKAirCashPortName:(NSString *)portName portSettings:(NSString *)portSettings dongleMACAddr:(NSString *)MACAddr RSSIthreshould:(NSNumber *)Threshold nickName:(NSString *)nickName;

/*!
 *  This method removes the setting information connected to the Star BLE device by the port name.
 *
 *  @param portName A port name to delete settings.
 *
 *  @discussion This will do nothing if the settings of specified portName is not exists or nil.
 */
- (void)removeSettingWithPortName:(NSString *)portName;

/*!
 *  Get serialized settings by NSData class.
 *
 *  @return Serialized settings by NSData if succeeded, otherwise nil.
 */
- (NSData *)serializedSettings;

/*!
 *  Set settings property by specified NSData class.
 *
 *  @param data Value obtained from 'serializedSettings' method.
 *
 *  @return NO if the restoration is failed.
 */
- (BOOL)deserializeSettings:(NSData *)data;

/*!
 *  Calibrate RSSI to make action area.
 *
 *  @param MACAddr MAC address of Star BLE dongle.
 *
 *  @return The maximum RSSI value approximately five seconds later. A value of <code>127</code> is reserved and indicates the RSSI was not available.
 
 */
- (int)calibrateActionArea:(NSString*)MACAddr;

/*!
 *  Gets the RSSI value of the connected printer or DK-AirCash.
 *
 *  @param MACAddr MAC address of Star BLE dongle.
 *
 *  @return RSSI value of selected MAC address. A value of <code>127</code> is reserved and indicates the given MAC address was not found.
 */
- (int)getRSSI:(NSString *)MACAddr;

@end


#pragma mark - SMBleManagerDelegate

/*!
 *  Delegate to inform from SMProxiPRNTManager class.
 */
@protocol SMProxiPRNTManagerDelegate <NSObject>

/*!
 *  Delegate method that reports an RSSI value of specified device changed during a device scan initiated by the 'startScan' function.
 *
 *  @param  portName   Port name which is currently getting rssi.
 *  @param  deviceType Device type which is currently getting rssi.
 *  @param  MACAddr    MAC address of Star BLE dongle.
 *  @param  RSSI       RSSI value that is currently getting in dBm.
 */
@optional
- (void)didDiscoverPort:(NSString *)portName deviceType:(SMDeviceType)deviceType MACAddr:(NSString *)MACAddr RSSI:(NSNumber *)RSSI;

/*!
 *  Delegate method that reports an device that could not be get the rssi value for five seconds or more
 *  during a device scan initiated by the 'startScan' function.
 *
 *  @param portName   A port name of target device.
 *  @param MACAddr    MAC address of Star BLE dongle.
 */
@optional
- (void)didUpdateState:(NSString *)portName MACAddr:(NSString *)MACAddr;

@end
