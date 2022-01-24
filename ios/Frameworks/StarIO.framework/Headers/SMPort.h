/*
 *  @file Port.h
 *  @framework StarIOPort
 *
 *  @discussion Entry point to StarIO.
 *  @copyright 2016 Star Micronics Co., Ltd. All rights reserved.
 */

#import <Foundation/Foundation.h>

#ifdef TARGET_OS_IPHONE
    #ifdef BUILDING_STARIO
        #include <starmicronics/StarIOPort.h>
    #else
        #include <StarIO/starmicronics/StarIOPort.h>
    #endif
#else
    #include <starmicronics/StarIOPort.h>
#endif

#import "WBluetoothPort.h"
#import "ExternalAccessoryPort.h"
#import "Lock.h"
#import "SMFileLogger.h"
#import "SMStarIOResultCode.h"

#import "exceptions/PortException.h"


@interface PortInfo : NSObject

- (id)initWithPortName:(NSString *)portName_
            macAddress:(NSString *)macAddress_
             modelName:(NSString *)modelName_;

@property(retain, readonly) NSString *portName;
@property(retain, readonly) NSString *macAddress;
@property(retain, readonly) NSString *modelName;

@end

@interface SMPort : NSObject {
    void * m_port;
    WBluetoothPort *wBluetoothPort;
    ExternalAccessoryPort *externalAccessoryPort;
    NSString * m_portName;
    NSString * m_portSettings;
    int m_ioTimeoutMillis;

    BOOL checkedBlockSupport;
}

@property(assign, nonatomic) NSString *name;
@property(assign, nonatomic) NSString *identifier;

@property(nonatomic) NSUInteger connectionID;

@property(assign, readwrite, nonatomic) u_int32_t endCheckedBlockTimeoutMillis;

+ (NSString *)StarIOVersion;

/*!
 *  Search printer on LAN or paired bluetooth device.
 *
 *  @return List of printers that were found.
 */
+ (NSArray *)searchPrinter
__attribute__((deprecated("Please replace this method with 'searchPrinter(target:) throws' for Swift or 'searchPrinter:(NSString *)target :(NSError **)error' for Objective-C, and pass 'ALL:' as the target argument.")));

/*!
 *  Search printer on LAN or paired bluetooth device.
 *
 *  @param  target   the interface type to search (ex. "TCP:", "BT:", "BT:xxx", "USB:xxx").
 *
 *  @return List of printers that were found.
 */
+ (NSArray *)searchPrinter:(NSString *)target
__attribute__((deprecated("Please replace this method with 'searchPrinter(target:) throws' for Swift or 'searchPrinter:(NSString *)target :(NSError **)error' for Objective-C.")));

/*!
 *  This function opens a connection to the port specified.
 *
 *  @param portName        String taking the following form
 *                           "tcp:nnn.nnn.nnn.nnn" which opens the network printer at the specified IP address (i.e. '192.168.11.3')
 *                           "bt:<iOS port name>"  which opens the bluetooth printer at the specified port name. (i.e. 'Star Micronics')
 *                           "usb:<iOS port name>" which opens the usb printer at specified port name.(i.e. 'TSP100')
 *  @param portSettings    Star Line Mode: Empty string ("")
 *                         Portable Printer (Star Line): "Portable"
 *                         Portable Printer (ESC/POS): "Portable;ESCPOS"
 *  @param ioTimeoutMillis This is the time out for trying to get the port in milliseconds.
 *
 *  @return SMPort class for StarIO port.
 */
+ (SMPort *)getPort:(NSString *)portName :(NSString *)portSettings :(u_int32_t)ioTimeoutMillis
__attribute__((deprecated("Please replace this method with 'getPort(portName:portSettings:ioTimeoutMillis:) throws' for Swift or 'getPort:(NSString *)portName :(NSString *)portSettings :(u_int32_t)ioTimeoutMillis :(NSError **)error;' for Objective-C.")));

/*!
 *  This function closes a connection to the port specified.
 *
 *  @param port Pointer to a previously created port.
 */
+ (void)releasePort: (SMPort *) port;

/*!
 *  This function writes data to the device.
 *
 *  @param writeBuffer Pointer to a byte buffer containing the write data.
 *  @param offSet      Amount of data that was already written.
 *  @param size        Amount of data left to write.
 *
 *  @return Amount of data written.
 *
 *  @note Throws PortException on failure.
 */
- (u_int32_t)writePort:(u_int8_t const *)writeBuffer :(u_int32_t)offSet :(u_int32_t)size
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception. "
                     "Please replace this method with 'write(writeBuffer:offset:size:numberOfBytesWritten:) throws'.")
__attribute__((deprecated("Please replace this method with 'write(writeBuffer:offset:size:numberOfBytesWritten:) throws' for Swift or 'writePort:(u_int8_t const *)writeBuffer :(u_int32_t)offSet :(u_int32_t)size :(NSError **)error;' for Objective-C.")));

/*!
 *  This function reads data from the device.
 *
 *  @param readBuffer   Pointer to a byte buffer into which data is read.
 *  @param offSet       Size in bytes to read.
 *  @param size         Amount of data to be write to the buffer.
 *
 *  @return Aount of data written to the buffer.
 *
 *  @note Throws PortException on failure.
 */
- (u_int32_t)readPort:(u_int8_t *)readBuffer
                     :(u_int32_t)offSet
                     :(u_int32_t)size
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception. "
                     "Please replace this method with 'read(readBuffer:offset:size:numberOfBytesRead:) throws'.")
__attribute__((deprecated("Please replace this method with 'read(readBuffer:offset:size:numberOfBytesRead:) throws' for Swift or 'readPort:(u_int8_t *)readBuffer :(u_int32_t)offSet :(u_int32_t)size :(NSError **)error' for Objective-C.")));

/*!
 *  This function retreives the device's detailed status.
 *
 *  @param starPrinterStatus Pointer to a StarPrinterStatus_n structure where the devices detailed status is written
 *                           (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2).
 *  @param level             Integer designating the level of status structure (either 0, 1, or 2).
 *
 *  @note Throws PortException on failure.
 */
- (void)getParsedStatus:(void *)starPrinterStatus
                       :(u_int32_t)level
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'getParsedStatus(starPrinterStatus:level:) throws'.")
__attribute__((deprecated("Please replace this method with 'getParsedStatus(starPrinterStatus:level:) throws' for Swift or 'getParsedStatus:(void *)starPrinterStatus :(u_int32_t)level :(NSError **)error' for Objective-C.")));

/*!
 *  This function retrieves the device's firmware information.
 *
 *  @return NSDictionary class that contains firmware information.
 */
- (NSDictionary *)getFirmwareInformation
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'getFirmwareInformation() throws'.")
__attribute__((deprecated("Please replace this method with 'getFirmwareInformation() throws' for Swift or 'getFirmwareInformation:(NSError **)error' for Objective-C.")));

/*!
 *  This function retrieves the device's Dip Switch information.
 *
 *  @return NSDictionary class that contains Dip Switch information.
 */
- (NSDictionary *)getDipSwitchInformation
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'getDipSwitchInformation(error:)'.")
__attribute__((deprecated("Please replace this method with 'getDipSwitchInformation(error:)'.")));

/*!
 *  This function retreives the device's online status.
 *
 *  @return SM_TRUE: printer is online.
 *          SM_FALSE: printer is offline.
 *
 *  @note Throws PortException on failure.
 */
- (bool)getOnlineStatus
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'getOnlineStatusWithError(error:)'.")
__attribute__((deprecated("Please replace this method with 'getOnlineStatusWithError(error:)'.")));

/*!
 *  This function initiates a checked block printing operation and returns the devices detailed status.
 *
 *  @param starPrinterStatus Pointer to a StarPrinterStatus_n structure where the devices detailed status is written
 *                           (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2).
 *  @param level             Integer designating the level of status structure (either 0, 1, or 2).
 *
 *  @note Throws PortException on failure.
 */
- (void)beginCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'beginCheckedBlock(starPrinterStatus:level:) throws'.")
__attribute__((deprecated("Please replace this method with 'beginCheckedBlock(starPrinterStatus:level:) throws' for Swift or 'beginCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level :(NSError **)error' for Objective-C.")));

/*!
 *  This function ends a checked block printing operation and returns the devices detailed status.
 *  This function does not return until either the printer has successfully printed all data or has gone offline in error.
 *  If the starPrinterStatus_2 structure indicates that the printer is online upon return than all data was successfully printed.
 *
 *  @param starPrinterStatus Pointer to a StarPrinterStatus_n structure where the devices detailed status is written
 *                           (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2).
 *  @param level             Integer designating the level of status structure (either 0, 1, or 2)
 *
 *  @note Throws PortException on failure
 */
- (void)endCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level
NS_SWIFT_UNAVAILABLE("This method throws an Objective-C exception."
                     "Please replace this method with 'endCheckedBlock(starPrinterStatus:level:) throws'.")
__attribute__((deprecated("Please replace this method with 'endCheckedBlock(starPrinterStatus:level:) throws' for Swift or 'endCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level :(NSError **)error' for Objective-C.")));

/*!
 *  Disconnect Bluetooth port for Desktop Printer and DK-AirCash.
 *
 *  @return YES if succeed to disconnect Bluetooth or I/F is Ethernet, otherwise NO.
 */
- (BOOL)disconnect;

//
// NSError was added to the argument of API.
//

+ (NSArray *)searchPrinter:(NSString *)target
                          :(NSError **)error NS_SWIFT_NOTHROW;

+ (SMPort *)getPort:(NSString *)portName
                   :(NSString *)portSettings
                   :(u_int32_t)ioTimeoutMillis
                   :(NSError **)error NS_SWIFT_NOTHROW;

- (u_int32_t)writePort:(u_int8_t const *)writeBuffer
                      :(u_int32_t)offSet
                      :(u_int32_t)size
                      :(NSError **)error;

- (u_int32_t)readPort:(u_int8_t *)readBuffer
                     :(u_int32_t)offSet
                     :(u_int32_t)size
                     :(NSError **)error;

- (SM_BOOLEAN)getParsedStatus:(void *)starPrinterStatus
                             :(u_int32_t)level
                             :(NSError **)error;

- (NSDictionary *)getFirmwareInformation:(NSError **)error NS_SWIFT_NOTHROW;

- (NSDictionary *)getDipSwitchInformation:(NSError **)error NS_SWIFT_NOTHROW;

- (bool)getOnlineStatus:(NSError **)error
__attribute__((unavailable("Not available. Please replace this method with 'getOnlineStatusWithError(error:)'.")));

- (SM_BOOLEAN)getOnlineStatusWithError:(NSError **)error;

- (SM_BOOLEAN)beginCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level :(NSError **)error;

- (SM_BOOLEAN)endCheckedBlock:(void *)starPrinterStatus :(u_int32_t)level :(NSError **)error;

- (BOOL)disconnect:(NSError **)error NS_SWIFT_NOTHROW;



+ (NSMutableData *)compressRasterData:(int32_t)width
                                     :(int32_t)height
                                     :(u_int8_t *)imageData
                                     :(NSString *)portSettings;

+ (NSMutableData *)generateBitImageCommand:(int32_t)width
                                          :(int32_t)height
                                          :(u_int8_t *)imageData
                                          :(NSString *)portSettings __attribute__((deprecated));

- (NSString *)portName;

- (NSString *)portSettings;

- (u_int32_t)timeoutMillis;

- (BOOL)connected;

+ (void)setMACAddressSourceBlock:(NSString *(^)(EAAccessory *accessory))macAddressSourceBlock;

@end
