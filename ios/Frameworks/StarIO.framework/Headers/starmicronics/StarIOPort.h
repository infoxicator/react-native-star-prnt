/*
  Visual Studio project setup
  ////////////////////////////
  1. Add this package's 'redistributables\include' directory to your project's 'Additional Include Directories' project property (under C/C++ -> General)
  2. Add this statement to your source code files: '#include <starmicronics/StarIOPort.h>'
  3. Add this package's 'redistributables\lib' directory to your project's 'Additional Library Directories' project property (under Linker -> General)
  4. Add 'StarIOPort.lib' to your project's 'Additional Dependencies' project property (under Linker -> Input)
  
  Linux & Mac  OS X sample build command
  ///////////////////////////////////////
  g++ -o bin/Star Micronics Co., Ltd._Sample -I./include -L./bin -W Star Micronics Co., Ltd._Sample.cpp -lStarIOPort
*/

#ifndef ioport__
#define ioport__


#ifdef BUILDING_STARIO
    #include <starmicronics/Platform.h>
    #include "enum.h"
#else
    #include <StarIO/starmicronics/Platform.h>
    #include <StarIO/enum.h>
#endif

#ifdef COMPILING_STARIOPORT
#define STARIOPORT_API DLL_EXPORT
#else
#define STARIOPORT_API DLL_IMPORT
#endif

#include "PreventingNameConflicts.h"

typedef struct StarPrinterStatus_
{
  // printer status 1
  SM_BOOLEAN coverOpen;
  SM_BOOLEAN offline;
  SM_BOOLEAN compulsionSwitch;

  // printer status 2
  SM_BOOLEAN overTemp;
  SM_BOOLEAN unrecoverableError;
  SM_BOOLEAN cutterError;
  SM_BOOLEAN mechError;

  // printer status 3
  SM_BOOLEAN pageModeCmdError;
  SM_BOOLEAN paperSizeError;
  SM_BOOLEAN presenterPaperJamError;
  SM_BOOLEAN headUpError;

  // printer status 4
  SM_BOOLEAN blackMarkDetectStatus;
  SM_BOOLEAN paperEmpty;
  SM_BOOLEAN paperNearEmptyInner;
  SM_BOOLEAN paperNearEmptyOuter;

  // printer status 5
  SM_BOOLEAN stackerFull;

  // printer status 6
  SM_BOOLEAN etbAvailable;
  UCHAR etbCounter;

  // printer status 7
  UCHAR presenterState;

  // raw
  UINT32 rawLength;
  UCHAR raw[63];
} StarPrinterStatus, StarPrinterStatus_0;

typedef struct StarPrinterStatus_1_
{
  // printer status 1
  SM_BOOLEAN coverOpen;
  SM_BOOLEAN offline;
  SM_BOOLEAN compulsionSwitch;

  // printer status 2
  SM_BOOLEAN overTemp;
  SM_BOOLEAN unrecoverableError;
  SM_BOOLEAN cutterError;
  SM_BOOLEAN mechError;

  // printer status 3
  SM_BOOLEAN receiveBufferOverflow;
  SM_BOOLEAN pageModeCmdError;
  SM_BOOLEAN blackMarkError;
  SM_BOOLEAN presenterPaperJamError;
  SM_BOOLEAN headUpError;

  // printer status 4
  SM_BOOLEAN receiptBlackMarkDetection;
  SM_BOOLEAN receiptPaperEmpty;
  SM_BOOLEAN receiptPaperNearEmptyInner;
  SM_BOOLEAN receiptPaperNearEmptyOuter;

  // printer status 5
  SM_BOOLEAN presenterPaperPresent;
  SM_BOOLEAN peelerPaperPresent;
  SM_BOOLEAN stackerFull;
  SM_BOOLEAN slipTOF;
  SM_BOOLEAN slipCOF;
  SM_BOOLEAN slipBOF;
  SM_BOOLEAN validationPaperPresent;
  SM_BOOLEAN slipPaperPresent;

  // printer status 6
  SM_BOOLEAN etbAvailable;
  UCHAR etbCounter;

  // printer status 7
  UCHAR presenterState;

  // raw
  UINT32 rawLength;
  UCHAR raw[63];
} StarPrinterStatus_1;

typedef struct StarPrinterStatus_2_
{
  // printer status 1
  SM_BOOLEAN coverOpen;
  SM_BOOLEAN offline;
  SM_BOOLEAN compulsionSwitch;

  // printer status 2
  SM_BOOLEAN overTemp;
  SM_BOOLEAN unrecoverableError;
  SM_BOOLEAN cutterError;
  SM_BOOLEAN mechError;
  SM_BOOLEAN headThermistorError;

  // printer status 3
  SM_BOOLEAN receiveBufferOverflow;
  SM_BOOLEAN pageModeCmdError;
  SM_BOOLEAN blackMarkError;
  SM_BOOLEAN presenterPaperJamError;
  SM_BOOLEAN headUpError;
  SM_BOOLEAN voltageError;

  // printer status 4
  SM_BOOLEAN receiptBlackMarkDetection;
  SM_BOOLEAN receiptPaperEmpty;
  SM_BOOLEAN receiptPaperNearEmptyInner;
  SM_BOOLEAN receiptPaperNearEmptyOuter;

  // printer status 5
  SM_BOOLEAN presenterPaperPresent;
  SM_BOOLEAN peelerPaperPresent;
  SM_BOOLEAN stackerFull;
  SM_BOOLEAN slipTOF;
  SM_BOOLEAN slipCOF;
  SM_BOOLEAN slipBOF;
  SM_BOOLEAN validationPaperPresent;
  SM_BOOLEAN slipPaperPresent;

  // printer status 6
  SM_BOOLEAN etbAvailable;
  UCHAR etbCounter;

  // printer status 7
  UCHAR presenterState;

  // printer status 10
  UCHAR connectedInterface;

  // raw
  UINT32 rawLength;
  UCHAR raw[63];
} StarPrinterStatus_2;


#ifdef __cplusplus
extern "C"
{
#endif

/*
    OpenPort
    --------
    This function opens a connection to the port specified.

    Parameters: portName               - (Windows) string taking on one of these forms:
                                                   "usbven:" which opens the first available USB Vendor Class device
                                                   "usbven:sNsNsNsN" which opens the USB Vendor Class device with that serial number
                                                   "usbven:COMx" which opens the USB Vendor Class device that has been assigned to COMx (i.e. 'COM4' or 'COM17')
                                                   "usbprn:Queue Name" which opens the USB Printer Class device associated with the specified printer queue
                                                   "COMx" which opens the real serial port (i.e. 'COM1')
                                                   "LPTx" which opens the real parallel port (i.e. 'LPT1')
                                                   "tcp:nnn.nnn.nnn.nnn" which opens the network printer at the specified IP address (i.e. '192.168.11.3')
                                       - (Linux) string taking on one of these forms:
                                                   "usbven:" which opens the first available USB Vendor Class device
                                                   "/dev/ttySX" which opens the real serial port (i.e. '/dev/ttyS0'), this can changed from system to system depending on the location of the serial port
                                                   "/dev/parportX" which opens the real parallel port (i.e. '/dev/parport0'), this can changed from system to system depending on the location of the parallel port
                                                   "tcp:nnn.nnn.nnn.nnn" which opens the network printer at the specified IP address (i.e. '192.168.11.3')
                portSettings           - string of the form "9600,n,8,1,h" for serial, "" for all others
                ioRequestTimeoutMillis - millisecond timeout controlling internally used communication APIs (this parameter garantees that all of the below APIs will complete in a bounded amount of time, but does NOT garantee the exact timeout length)
    Returns:    0 on failure
                    or
                pointer to the created port (opaque)
    Notes:      1. In the case of serial, the portSettings string contains the
                   following fields:
                       baud: 38400, 19200, 9600, 4800, 2400
                       parity: n, e, o
                       data-bits: 8, 7
                       stop-bits: 1
                       flow-ctrl: n, h

                2. On Windows, OpenPort will fail and return 0 if another process (or driver) already has the same port
                   opened.  In many cases you will want to call OpenPort in a loop until the other process has
                   finished its usage.  For example:

                   void * port = 0; // port handle (opaque pointer)
                   while ((port = OpenPort(L"COM1", L"9600,n,8,1,h", 5000)) == 0)
                   {
                       if (GetLastError() == ERROR_ALREADY_EXISTS) // ALREADY_EXISTS indicates another process's usage - try again
                       {
                           Sleep(100); // suspend the thread - save the earth

                           continue; // try again
                       }
                       else
                       {
                           return EXIT_FAILURE; // this is a different kind of failure - dead
                       }
                   }
*/
    

#if defined(_WINDOWS) || defined(WIN32)

  STARIOPORT_API void * CALL_CONVENT OpenPortW(wchar_t const * portName, wchar_t const * portSettings, UINT32 ioRequestTimeoutMillis);

  STARIOPORT_API void * CALL_CONVENT OpenPortA(char const * portName, char const * portSettings, UINT32 ioRequestTimeoutMillis);

  #ifdef _UNICODE

    #define OpenPort(portName, portSettings, ioRequestTimeoutMillis) OpenPortW(portName, portSettings, ioRequestTimeoutMillis)

  #else

    #define OpenPort(portName, portSettings, ioRequestTimeoutMillis) OpenPortA(portName, portSettings, ioRequestTimeoutMillis)

  #endif

#else

    STARIOPORT_API void * CALL_CONVENT OpenPort(char const * portName, char const * portSettings, UINT32 ioRequestTimeoutMillis, SMEmulation emulation, SMConnectionResult *connectionResult);
    
#endif

    
/*
    ClosePort
    --------
    This function closes a connection to the port specified.

    Parameters: port - pointer to a previously created port
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT ClosePort(void * port);

/*
    ReadPort
    --------
    This function reads data from the device.

    Parameters: port             - pointer to a previously created port
                readBuffer       - pointer to a byte buffer into which data is read
                size             - size in bytes to read
                sizeCommunicated - out variable into which the actual read size is written
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
    Notes:      Under some interface types, this function will return SM_TRUE even when no data was read in.  Your application should call
                this function a limited number of times until the expected data has been read in or until an application determined
                retry threshold has been reached.
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT ReadPort(void * port, UCHAR * readBuffer, UINT32 size, UINT32 * sizeCommunicated);

/*
    WritePort
    --------
    This function writes data to the device.

    Parameters: port             - pointer to a previously created port
                writeBuffer      - pointer to a byte buffer containing the write data
                size             - size in bytes to write
                sizeCommunicated - out variable into which the actual write size is written
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
    Notes:      Under some interface types, this function will return SM_TRUE even when no data was written out.  Your application should call
                this function a limited number of times until all the data has been written out or until an application determined
                retry threshold has been reached.
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT WritePort(void * port, UCHAR const * writeBuffer, UINT32 size, UINT32 * sizeCommunicated);

/*
    GetOnlineStatus
    --------
    This function retreives the device's online status.

    Parameters: port         - pointer to a previously created port
                onlineStatus - out variable into which the device's online status is written (SM_FALSE = offline, SM_TRUE = online)
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT GetOnlineStatus(void * port, SM_BOOLEAN * onlineStatus);

/*
    GetParsedStatus
    --------
    This function retreives the device's detailed status.

    Parameters: port              - pointer to a previously created port
                StarPrinterStatus - pointer to a StarPrinterStatus structure where the devices detailed status is written
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT GetParsedStatus(void * port, StarPrinterStatus * starPrinterStatus);

/*
    GetParsedStatusEx
    --------
    This function retreives the device's detailed status.

    Parameters: port              - pointer to a previously created port
                starPrinterStatus - pointer to a StarPrinterStatus_n structure where the devices detailed status is written (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2)
                level             - integer designating the level of status structure (either 0, 1, or 2)
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT GetParsedStatusEx(void * port, void * starPrinterStatus, UINT32 level);

    
/*
    GetParsedStatusEx
    --------
    This function retreives the device's detailed status.
     
    Parameters: port              - pointer to a previously created port
    starPrinterStatus - pointer to a StarPrinterStatus_n structure where the devices detailed status is written (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2)
    level             - integer designating the level of status structure (either 0, 1, or 2)
    Returns:    SM_FALSE on failure
    or
    SM_TRUE on success
 */
STARIOPORT_API SM_BOOLEAN RetrieveFirmwareInformation(void * port);

/*
    RetrieveDipSwitchInformation
    --------
    This function retreives the device's dip switch status.
 
    Parameters: port  - pointer to a previously created port
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN RetrieveDipSwitchInformation(void * port);

/*
    BeginCheckedBlock
    --------
    This function initiates a checked block printing operation and returns the devices detailed status.

    Parameters: port              - pointer to a previously created port
                starPrinterStatus - pointer to a StarPrinterStatus structure where the devices detailed status is written
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT BeginCheckedBlock(void * port, StarPrinterStatus * starPrinterStatus);

/*
    BeginCheckedBlockEx
    --------
    This function initiates a checked block printing operation and returns the devices detailed status.

    Parameters: port              - pointer to a previously created port
                starPrinterStatus - pointer to a StarPrinterStatus_n structure where the devices detailed status is written (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2)
                level             - integer designating the level of status structure (either 0, 1, or 2)
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT BeginCheckedBlockEx(void * port, void * starPrinterStatus, UINT32 level);

/*
    EndCheckedBlock
    --------
    This function ends a checked block printing operation and returns the devices detailed status.
    This function does not return until either the printer has successfully printed all data or has gone offline in error.
    If the starPrinterStatus structure indicates that the printer is online upon return than all data was successfully printed.

    Parameters: port              - pointer to a previously created port
                starPrinterStatus - pointer to a StarPrinterStatus structure where the devices detailed status is written
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT EndCheckedBlock(void * port, StarPrinterStatus * starPrinterStatus);

/*
    EndCheckedBlockEx
    --------
    This function ends a checked block printing operation and returns the devices detailed status.
    This function does not return until either the printer has successfully printed all data or has gone offline in error.
    If the starPrinterStatus structure indicates that the printer is online upon return than all data was successfully printed.

    Parameters: port              - pointer to a previously created port
                starPrinterStatus - pointer to a StarPrinterStatus_n structure where the devices detailed status is written (either StarPrinterStatus_0, StarPrinterStatus_1, or StarPrinterStatus_2)
                level             - integer designating the level of status structure (either 0, 1, or 2)

    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT EndCheckedBlockEx(void * port, void * starPrinterStatus, UINT32 level);

/*
    ResetDevice
    --------
    This function resets the device at the hardware level.

    Parameters: port - pointer to a previously created port
    Returns:    SM_FALSE on failure
                  or
                SM_TRUE on success
*/
STARIOPORT_API SM_BOOLEAN CALL_CONVENT ResetDevice(void * port);

/*!
 *  デバイスからファームウェア情報を取得する。
 *  @param  port    ポート構造体へのポインタ
 *
 *  @return 成功時はSM_TRUE, 失敗時はSM_FALSEを返す。
 */
STARIOPORT_API char * CALL_CONVENT GetFirmwareInformation(void * port);

/*!
 *  デバイスからDip Switch情報を取得する。
 *
 *  @param  port    ポート構造体へのポインタ
 *  @param  dsInfo  Dip Switch Channel番号
 *  @return 成功時はSip Switch情報を格納したポインタ, 失敗時はnillを返す。
 */
STARIOPORT_API char * CALL_CONVENT GetDipSwitchInformation(void * port, u_int8_t dsInfo);

/*!
 *  ボタンセキュリティのタイムアウト時間を取得する。
 *
 *  @param  port    ポート構造体へのポインタ
 *  @return ボタンセキュリティ有効時はタイムアウト時間を、無効の場合は0を返す。エラー時は-1を返す。
 */
STARIOPORT_API int CALL_CONVENT retrieveButtonSecurityTimeout(void * port);
    
UINT32 GetEndCheckedBlockTimeoutMillis(void * port);
    
/*
    SetEndCheckedBlockTimeoutMillis
    --------
    This function is to change timeout value of endCheckedBlock function.
    Parameters: port          - pointer to a previously created port
               timeoutMillis - timeout of endCheckedBlock[msec]
 */
void SetEndCheckedBlockTimeoutMillis(void * port, UINT32 timeoutMillis);

#pragma mark Private
    
STARIOPORT_API SM_BOOLEAN CALL_CONVENT IsUSBSharing(void * port);
    
STARIOPORT_API SM_BOOLEAN CALL_CONVENT IsDKAirCash(void * port);
    

    
#ifdef __cplusplus
}
#endif

#endif

