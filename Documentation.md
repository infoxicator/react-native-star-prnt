## SMPort Example

SMPort opens the connection to the printer and closes it after the commands are successfully sent.

```javascript

let commands = [];
commands.push({append:
        "Star Clothing Boutique\n" +
        "123 Star Road\n" +
        "City, State 12345\n" +
        "\n"});
commands.push({appendCutPaper:StarPRNT.CutPaperAction.PartialCutWithFeed});

async function print() {
    try {
      var printResult = await StarPRNT.print(emulation, commands, portName);
      console.log(printResult); // Success!
    } catch (e) {
      console.error(e);
    }
  }
  
```

## StarIOExtManager Example

StarIOExtManager Allows you to connect to the printer and listen for hardware events, you will need to manually open and close the connection.

```javascript

async function connect() {
    try {
      var connect = await StarPRNT.connect(portName, emulation, hasBarcodeReader);
      console.log(connect); // Printer Connected!
    } catch (e) {
      console.error(e);
    }
  }

let commands = [];
commands.push({append:
        "Star Clothing Boutique\n" +
        "123 Star Road\n" +
        "City, State 12345\n" +
        "\n"});
commands.push({appendCutPaper:StarPRNT.CutPaperAction.PartialCutWithFeed});

async function print() {
    try {
      var printResult = await StarPRNT.print(emulation, commands);
      console.log(printResult); // Success!
    } catch (e) {
      console.error(e);
    }
  }
```

## Printing Special Characters ( £, € )

To print special characters using the print() function, select the correct [Encoding](#encoding), [CodePageType](#codepagetype) and [International](#internationaltype) then send the bytes using the appendBytes command.

## Pound Sign (£) Example

 [CodePage 858](https://en.wikipedia.org/wiki/Code_page_858)

 ```javascript
 let commands = [];
 commands.push({appendCodePage:StarPRNT.CodePageType.CP858});
             commands.push({appendEncoding: StarPRNT.Encoding.USASCII});
             commands.push({appendInternational: StarPRNT.InternationalType.UK});
             commands.push({appendBytes:[0x9c]});
```

## Euro Sign (€) Example

 [CodePage 858](https://en.wikipedia.org/wiki/Code_page_858)

 ```javascript 
 var commands = [];
 commands.push({appendCodePage:StarPRNT.CodePageType.CP858});
             commands.push({appendEncoding: StarPRNT.Encoding.Windows1252});
             commands.push({appendInternational: StarPRNT.InternationalType.Spain});
             commands.push({appendBytes:[0xd5]});
```

## API Reference

- [portDiscovery(type)](#port-discovery)
- [checkStatus(portName, emulation)](#check-status)
- [print(emulation, commandsArray, portName)](#print)
- [connect(portName, emulation, hasBarcodeReader)](#connect)
- [disconnect()](#disconnect)

### Events

- [Printer Events](#printer-events)
- [Barcode Reader Events](#barcode-reader-events)
- [Cash Drawer Events](#cash-drawer-events)

### PrintCommand

List of [commands](#printcommand-object) available through the print() function

### PrintCommand Constants

- [InternationalType](#internationaltype)
- [FontStyleType](#fontstyletype)
- [CutPaperAction](#cutpaperaction)
- [BlackMarkType](#blackmarktype)
- [LogoSize](#logosize)
- [AlignmentPosition](#alignmentposition)
- [BarcodeSymbology](#barcodesymbology)
- [BarcodeWidth](#barcodewidth)
- [QrCodeModel](#qrcodemodel)
- [QrCodeLevel](#qrcodelevel)
- [BitmapConverterRotation](#bitmapconverterrotation)

### Functions

All methods return a promise that you can wrap with Async/Await.

Note: asterisk (*) indicates a required parameter

### Port discovery

The `portDiscovery(type, success, error)` Find available printers

| Parameter | Description | Type/Example |
| ----------- | -------- | ---------- |
| type* | Port types are: 'All', 'Bluetooth', 'USB', 'LAN' | String |

### Check Status

The `checkStatus(portName, emulation)` returns the current status of the printer, as well as model number and firmware information. *Checking status of a printer while connected to that printer can produce unexpected results.*

| Parameter | Description | Type/Example |
| ----------- | -------- | ---------- |
| port* | Printer port name i.e BT:StarMicronics | String: "TCP:192.168.1.1" |
| emulation* | Emulation type depending on the printer model | String: [Emulation](#emulation) |


### Print

The `print(emulation, CommandsArray, portName)` Sends an Array of commands to the command buffer using the Android ICommandBuilderInterface or iOS ISCBBuilderInterface

| Parameter | Description | Type/Example |
| ----------- | -------- | ---------- |
| emulation* | Emulation type depending on the printer model | String: [Emulation](#emulation) |
| CommandsArray* | Each command in the array should be an instance of the [PrintCommand Object](#printcommand-object)  | Array:  [{append:"text"}, {"openCashDrawer: 1"}] |
| portName? | Optional. Printer port name i.e BT:StarMicronics. if the portName not set, it will use a printer connected via StarIOExtManager using the connect() function | String: "TCP:192.168.1.1" |

```javascript
var commandsArray = [];
commandsArray.push({appendInternational: StarPRNT.InternationalType.UK});
commandsArray.push({
    appendLogo:1,  //Logo number configured using Star Print utility
    logoSize:StarPRNT.LogoSize.Normal
});
commandsArray.push({appendAlignment: StarPRNT.AlignmentPosition.Center});
commandsArray.push({append: "Star Clothing Boutique\n"});
commandsArray.push({appendCutPaper: StarPRNT.CutPaperAction.PartialCutWithFeed});

async function print() {
    try {
      var printResult = await StarPRNT.print(emulation, commandsArray, portName);
      console.log(printResult); // Success!
    } catch (e) {
      console.error(e);
    }
  }
```

### Connect

The `connect(portName, emulation, hasBarcodeReader)` function allows to 'connect' to the peripheral, to keep alive the connection between the device and the peripheral.

| Parameter | Description | Type/Example |
| ----------- | -------- | ---------- |
| portName | Printer port name i.e BT:StarMicronics | String: "BT:StarMicronics" |
| emulation | Printer emulation | StarPRNT, StarLine, etc...  String: [Emulation](#emulation)  |
| hasBarcodeReader? | Optional. Default to false, If device has an attached barcode reader | true or false (mPOP device has a barcode reader) |

```javascript
async function connect() {
    try {
      var connect = await StarPRNT.connect(portName, emulation, hasBarcodeReader);
      console.log(connect); // Printer Connected!
    } catch (e) {
      console.error(e);
    }
  }

```

**Notes:**

- You need to connect before printing if using StarIOExtManager
- You should call this function on app **resume** event if you have disconnected on **pause** event
- After connecting you will start receiving status, cash drawer and barcode reader events.

### Disconnect

The `disconnect()` function allows to disconnect (i.e. close the connection to the peripherals), this is useful to avoid keeping alive a connection when not in the app to save device battery (or energy consumption).

**Notes:**
- You should call this function on app **pause** event or when the app is closed

### Events

Listen to printer events as cases of the **starPrntData** event, call the connect() function first to start receiving events:

#### Printer Events

- Printer cover open: printerCoverOpen
- Printer cover close: printerCoverClose
- Printer impossible: printerImpossible
- Printer online: printerOnline
- Printer offline: printerOffline
- Printer paper empty: printerPaperEmpty
- Printer paper near empty: printerPaperNearEmpty
- Printer paper ready: printerPaperReady

#### Barcode Reader Events
- Barcode reader impossible: barcodeReaderImpossible
- Barcode reader connect: barcodeReaderConnect
- Barcode reader disconnect: barcodeReaderDisconnect
- Barcode data receive: barcodeDataReceive

#### Cash Drawer Events

- Cash drawer open: cashDrawerOpen
- Cash drawer close: cashDrawerClose

**Notes:**
- Call connect() first to start receiving events.
- Register your listeners for Android and iOS on componentDidMount() and remove the listener on componentWillUnmount()

```javascript
componentDidMount() {
    this.listener = Platform.select({
      ios: () => {
       return StarPRNT.StarPRNTManagerEmitter.addListener(
          'starPrntData',
          (e) => console.log(e)
        );
      },
      android: () => {return DeviceEventEmitter.addListener('starPrntData', e => console.log(e))},
    })();   
  }

  componentWillUnmount(){
    if(this.listener) this.listener.remove();
  }

});
```


### PrintCommand Object

| Property (Command) | Description |
| ----------- | -------- |
| appendEncoding: string | Characther encoding is used to getByte data from all subsequent commands. Default 'US-ASCII' Choose the format of the return value Defined in [Encoding](#encoding) Example: ```{appendEncoding:'US-ASCII'}``` |  
| appendCodePage: string | Select command of the code page is generated and added to the commands property.Choose the format of the return value Defined in [CodePageType](#codepagetype) Example: ```{appendCodePage:'CP858'}``` |
| appendBytes: Array | Data (Command) is added to the command buffer. Takes an array of bytes. Example: ``` {appendBytes:[0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x2e]}``` |
| appendRawBytes: Array | Data (Command) is added to the command buffer. Takes an array of bytes. Example: ``` {appendRawBytes:[0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x2e]} ``` |  
| append: string | Data (Text) is added to the command buffer. Example: ```{append:"Star Clothing Boutique\n123 Star Road\nCity, State 12345\n\n"} ``` |  
| appendRaw: string | Data (Text) is added to the command buffer. Example: ```{appendRaw:"Star Clothing Boutique\n123 Star Road\nCity, State 12345\n\n"}``` |
|appendCharacterSpace: number | Set command of the character space is generated and added to the command buffer. Character Spacs (Unit: Dots) Example: ```{appendCharacterSpace: 4}``` |
|appendEmphasis: string | Select command of the emphasis mode is generated and added to the command buffer. Example: ```{appendEmphasis:"SALE\n"}``` |
|enableEmphasis: boolean | Enable emphasis mode is generated and added to the command buffer. Example: ```{enableEmphasis:true}``` |  
| appendInvert: string | Select command of the invert mode is generated and added to the command buffer. Example: ```{appendInvert:"Refunds and Exchanges\n"}``` |
| enableInvert: boolean | Enable invert mode is generated and added to the command buffer. Example: ```{enableInvert:true}``` |
| appendUnderline: string | Select command of the under line mode is generated and added to the command buffer. Example: ```{appendUnderline:"30 days"}```|
| enableUnderline: boolean| Enable under line mode is generated and added to the command buffer. Example: ```{enableUnderline:true}``` |
| appendInternational: string | Select command of the international character mode is generated and added to the command buffer.Choose the format of the return value Defined in [InternationalType](#internationaltype) Example ```{appendInternational:'UK'}```|
| appendLineFeed: number | Line feed command is generated and added to the command buffer. Paper feed units (Units: Lines) Example: ```{appendLineFeed:2}``` |
| appendUnitFeed: number | Unit feed command is generated and added to the command buffer. Paper feed units (Units: Dots) Example: ```{appendUnitFeed:64}``` |
| appendLineSpace: number |Set command of the line space is generated and added to the command buffer. Line spaces (Units: Dots) Example: ```{appendLineSpace:32}``` |
|appendFontStyle: string | Select command of the font style is generated and added to the command buffer. Choose the format of the return value defined in [FontStyleType](#fontstyletype). Example: ```{appendFontStyle: 'A'}``` |
| appendCutPaper: string | Paper cut command is generated and added to the command buffer. Choose the format of the return value defined [CutPaperAction](#cutpaperaction). Example: ```{appendCutPaper:'PartialCutWithFeed'}``` |
| appendBlackMark: string | Black mark command is generated and added to the command buffer. Choose the format of the return value defined in [BlackMarkType](#blackmarktype). Example: ```{appendBlackMark: 'Valid'}```|
| appendAbsolutePosition: number | Absolute position command is generated and added to the command buffer. (Unit: Dots). Send in conjunction with the data property to append absolute position just to that string. Example1: Append data with Absolute position ```{appendAbsolutePosition:40, data: "Text with absolute position"}```. Example2: Append absolute position to subsequent commands: ```{appendAbsolutePosition:40}``` |
| appendAlignment: string | Alignment command is generated and added to the command buffer. Send in conjunction with the data property to append alignment position just to that string. Choose the format of the return value defined in [AlignmentPosition](#alignmentposition). Example1 Append data with Alignment position: ```{appendAlignment:AlignmentPosition.Center, data: "Text with centered position"}```. Example2 Append absolute position to subsequent commands: ```{appendAlignment:'Center'}``` |
| appendHorizontalTabPosition: Array | Horizontal tab set/clear command is generated and added to the command buffer. (Only works for certain printer models, check the starSDK documentation for details). Array of horizontal tab positions (Units: ANK character pitch). Specifying empty array deletes all currently set horizontal tab positions. Example: ```{appendHorizontalTabPosition:[15, 35]}```. Delete positions Example: ```{appendHorizontalTabPosition:[]}``` |
|appendLogo: number | Print command of the logo is generated and added to the command buffer. The logo has to be uploaded to the printer using the Star Print utility. Send in conjuction with the logoSize property to set the logo size [LogoSize](#logosize). Example: ```{appendLogo:1}``` Example with LogoSize: ```{appendLogo:1, logoSize:'DoubleWidthDoubleHeight'}``` |
| logoSize: string |Property to be used with the appendLogo command. Choose the format of the return value defined in [LogoSize](#logosize). Example: ```{appendLogo:1, logoSize:'DoubleWidthDoubleHeight'}``` |
| appendBarcode: string | Print command of the barcode is generated and added to the command buffer. Additional Properties: BarcodeSymbology, BarcodeWidth, height, hri, absolutePosition, alignment. Example: ```{appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true }```. Example with absolutePosition: ```{appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true, absolutePosition:40 }```. Example with alignment: ```{appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true, alignment:alignment:AlignmentPosition.Center }```|
| BarcodeSymbology: string | Property to be used with the appendBarcode command. Choose the format of the return value defined in [BarcodeSymbology](#barcodesymbology). Example: ```{appendBarcode:'{BStar', BarcodeSymbology:'Code128'}``` |
| BarcodeWidth: string; |Property to be used with the appendBarcode command. Choose the format of the return value defined in [BarcodeWidth](#barcodewidth). Example: ```{appendBarcode:'{BStar', BarcodeWidth:'Mode2'}```|
| hri: boolean | Property to be used with the appendBarcode command. Under-bar characters. true = Valid, false = Invalid. Example: ```{appendBarcode:'{BStar', hri:true}``` | 
|height: number | Property to be used with the appendBarcode command or the appendMultiple command (Units:Dots) appendBarcode Example: ```{appendBarcode:'{BStar', height:40}``` appendMultiple Example: ```{appendMultiple:'text to print', height:40}``` |
| width: number | Property to be used with the appendBitmap command or the appendMultiple command (Units:Dots). appendBitmap Example: ```{appendBitmap:uri, width:576}```. appendMultiple Example: ```{appendMultiple:'text to print', width:40}``` |
| absolutePosition: number | Property to be used with the appendBitmap command, the appendBarcode command, or the appendQrCode command (Units:Dots). appendBitmap Example: ```{appendBitmap:uri, absolutePosition:40}```. appendBarcode Example: ```{appendBarcode:'{BStar', absolutePosition:40}```. appendQrCode Example: ```{appendQrCode:'{BStar', absolutePosition:40}```|
| alignment: string | Property to be used with the appendBitmap command, the appendBarcode command, or the appendQrCode command (Units:Dots). Choose the format of the return value defined in  [AlignmentPosition](#alignmentposition). appendBitmap Example: ```{appendBitmap:uri, alignment:'Center'}```.appendBarcode Example: ```{appendBarcode:'{BStar', alignment:'Center'}```. appendQrCode Example: ```{appendQrCode:'{BStar', alignment:'Center'}``` |
| appendMultiple: string | Select command of the multiple mode is generated and added to the command buffer. Additional properties: width:number, height:number. Example: ```{appendMultiple:"   $156.95\n", width:2, height:2}``` |
| enableMultiple: boolean | Enable multiple mode is generated and added to the command buffer. Additional properties: width:number, height:number. Example: ```{enableMultiple:true, width:2, height:2}``` Disable Example: ```{enableMultiple:false}``` |   
| appendQrCode: string | Print command of the QR code is generated and added to the command buffer. Additional Properties: QrCodeModel, QrCodeLevel, cell, absolutePosition, alignment. Example: ```{appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8}``` Example with absolutePosition: ``` {appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8, absolutePosition: 40 }``` Example with alignment: ```{appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8, alignment:"Center" }``` | 
| QrCodeModel: string | Property to be used with the appendQrCode command. Choose the format of the return value defined in  [QrCodeModel](#qrcodemodel). Example: ```{appendQrCode:'{BStar', QrCodeModel:'No1'}``` |
| QrCodeLevel: string |Property to be used with the appendQrCode command. Choose the format of the return value defined in  [QrCodeLevel](#qrcodelevel) Example: ```{appendQrCode:'{BStar', QrCodeLevel:'H'}``` |
| cell: number | Property to be used with the appendQrCode command. QRCode Cell size. Default 4. Example: ```{appendQrCode:'{BStar', cell:8}``` |
| appendBitmap: string; |Print command of the bitmap is generated and added to the command buffer. Takes a string image URI. This can be obtained via the camera or photo library or as a static resource saved on the phone memory. Additional Properties: diffusion, width, bothScale, rotation, absolutePosition, alignment. Example: ```{appendBitmap:uri, diffusion: true, width:576, bothScale: true}``` Example with absolutePosition: ```{appendBitmap:uri, diffusion: true, width:576, bothScale: true, absolutePosition: 40 }``` Example with alignment: ```{appendBitmap:uri, diffusion: true, width:576, bothScale: true, alignment:"Center" }``` |
|   diffusion: boolean | Property to be used with the appendBitmap command. Random dither: true = Valid, false = Invalid. Default true. Example: ```{appendBitmap:uri, diffusion: false } ``` |
| bothScale: boolean| Property to be used with the appendBitmap command. Height is changed according to the conversion rate of the width property. true = Valid, false = Invalid. Default true. Example:  ```{appendBitmap:uri, bothScale: true }``` |
| rotation: string|Property to be used with the appendBitmap command. Choose the format of the return value defined in  [BitmapConverterRotation](#bitmapconverterrotation) Example: ```{appendBitmap:uri, rotation:'Left90'}```
| openCashDrawer: number;| Sends a appendPeripheral command to the printer for channel number: Example: ```{openCashDrawer:1}``` |

## PrintCommand Constants

Values for the PrintCommand properties. (Case and type sensitive)

### Encoding

| Encoding | Languages |
| ----------- | -------- |
| 'US-ASCII' |  English |
| 'Windows-1252' | French, German, Portuguese, Spanish |
| 'Shift-JIS' | Japanese |
| 'Windows-1251' | Russian |
| 'GB2312' | Simplified Chinese |
| 'Big5' | Traditional Chinese |
| 'UTF-8' | UFT8 |

### CodePageType

    CP737 = 'CP737',
    CP772 = 'CP772',
    CP774 = 'CP774',
    CP851 = 'CP851',
    CP852 = 'CP852',
    CP855 = 'CP855',
    CP857 = 'CP857',
    CP858 = 'CP858',
    CP860 = 'CP860',
    CP861 = 'CP861',
    CP862 = 'CP862',
    CP863 = 'CP863',
    CP864 = 'CP864',
    CP865 = 'CP865',
    CP869 = 'CP869',
    CP874 = 'CP874',
    CP928 = 'CP928',
    CP932 = 'CP932',
    CP999 = 'CP999',
    CP1001 = 'CP1001',
    CP1250 = 'CP1250',
    CP1251 = 'CP1251',
    CP1252 = 'CP1252',
    CP2001 = 'CP2001',
    CP3001 = 'CP3001',
    CP3002 = 'CP3002',
    CP3011 = 'CP3011',
    CP3012 = 'CP3012',
    CP3021 = 'CP3021',
    CP3041 = 'CP3041',
    CP3840 = 'CP3840',
    CP3841 = 'CP3841',
    CP3843 = 'CP3843',
    CP3845 = 'CP3845',
    CP3846 = 'CP3846',
    CP3847 = 'CP3847',
    CP3848 = 'CP3848',
    UTF8 = 'UTF8',
    Blank = 'Blank'
}

### InternationalType

    UK = 'UK',
    USA = 'USA',
    France = 'France',
    Germany = 'Germany',
    Denmark = 'Denmark',
    Sweden = 'Sweden',
    Italy = 'Italy',
    Spain = 'Spain',
    Japan = 'Japan',
    Norway = 'Norway',
    Denmark2 = 'Denmark2',
    Spain2 = 'Spain2',
    LatinAmerica = 'LatinAmerica',
    Korea = 'Korea',
    Ireland = 'Ireland',
    Legal = 'Legal'

### FontStyleType

    Font-A (12 x 24 dots) / Specify 7 x 9 font (half dots) = 'A'
    Font-B (9 x 24 dots) / Specify 5 x 9 font (2P-1) = 'B'

### CutPaperAction

    FullCut = 'FullCut',
    FullCutWithFeed = 'FullCutWithFeed',
    PartialCut = 'PartialCut',
    PartialCutWithFeed = 'PartialCutWithFeed'

### BlackMarkType

    Valid = 'Valid',
    Invalid = 'Invalid',
    ValidWithDetection = 'ValidWithDetection'

### LogoSize

    Normal = 'Normal',
    DoubleWidth = 'DoubleWidth',
    DoubleHeight = 'DoubleHeight',
    DoubleWidthDoubleHeight = 'DoubleWidthDoubleHeight'

### AlignmentPosition

    Left = 'Left',
    Center = 'Center',
    Right = 'Right'

### BarcodeSymbology

    Code128 = 'Code128',
    Code39 = 'Code39',
    Code93 = 'Code93',
    ITF = 'ITF',
    JAN8 = 'JAN8',
    JAN13 = 'JAN13',
    NW7 = 'NW7',
    UPCA = 'UPCA',
    UPCE = 'UPCE'

### BarcodeWidth

    Mode1 = 'Mode1',
    Mode2 = 'Mode2',
    Mode3 = 'Mode3',
    Mode4 = 'Mode4',
    Mode5 = 'Mode5',
    Mode6 = 'Mode6',
    Mode7 = 'Mode7',
    Mode8 = 'Mode8',
    Mode9 = 'Mode9'

### QrCodeModel

    No1 = 'No1',
    No2 = 'No2'

### QrCodeLevel

    H = 'H',
    L = 'L',
    M = 'M',
    Q = 'Q'

### BitmapConverterRotation

    Normal = 'Normal',
    Left90 = 'Left90',
    Right90 = 'Right90',
    Rotate180 = 'Rotate180'

### Emulation

Source: Star SDK Documentation

| Printer Models | Emulation | 
| ----------- | -------- |
| mPOP  | StarPRNT |
| FVP10  | StarLine |
| TSP100  | StarGraphic |
| TSP650II  | StarLine |
| TSP700II  | StarLine |
| TSP800II  | StarLine |
| SP700  | StarDotImpact |
| SM-S210i  | EscPosMobile |
| SM-S220i  | EscPosMobile |
| SM-S230i  | EscPosMobile |
| SM-T300i/T300  | EscPosMobile |
| SM-T400i  | EscPosMobile |
| SM-L200  | StarPRNT |
| SM-L300  | StarPRNT |
| BSC10  | EscPos |
| SM-S210i StarPRNT  | StarPRNT |
| SM-S220i StarPRNT | StarPRNT |
| SM-S230i StarPRNT | StarPRNT |
| SM-T300i/T300 StarPRNT  | StarPRNT |
| SM-T400i StarPRNT  | StarPRNT |
