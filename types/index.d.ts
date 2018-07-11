import { NativeEventEmitter } from 'react-native';

declare class StarPRNT {

    static StarPRNTManagerEmitter: NativeEventEmitter;

    /**
    * Constant for Emulation
    */
    static Emulation: {
        StarPRNT: string,
        StarPRNTL: string,
        StarLine: string,
        StarGraphic: string,
        EscPos: string,
        EscPosMobile: string,
        StarDotImpact: string,
    };

    /**
     * Constant for possible Encoding
     */
    static Encoding: {
        USASCII: string,
        Windows1252: string,
        ShiftJIS: string,
        Windows1251: string,
        GB2312: string,
        Big5: string,
        UTF8: string
    };

    /**
     * CodePageType constants
     */
    static CodePageType: {
        CP737: string,
        CP772: string,
        CP774: string,
        CP851: string,
        CP852: string,
        CP855: string,
        CP857: string,
        CP858: string,
        CP860: string,
        CP861: string,
        CP862: string,
        CP863: string,
        CP864: string,
        CP865: string,
        CP869: string,
        CP874: string,
        CP928: string,
        CP932: string,
        CP999: string,
        CP1001: string,
        CP1250: string,
        CP1251: string,
        CP1252: string,
        CP2001: string,
        CP3001: string,
        CP3002: string,
        CP3011: string,
        CP3012: string,
        CP3021: string,
        CP3041: string,
        CP3840: string,
        CP3841: string,
        CP3843: string,
        CP3845: string,
        CP3846: string,
        CP3847: string,
        CP3848: string,
        UTF8: string,
        Blank: string
    };

    /**
     * Constant for possible InternationalType
     */
    static InternationalType: {
        UK: string,
        USA: string,
        France: string,
        Germany: string,
        Denmark: string,
        Sweden: string,
        Italy: string,
        Spain: string,
        Japan: string,
        Norway: string,
        Denmark2: string,
        Spain2: string,
        LatinAmerica: string,
        Korea: string,
        Ireland: string,
        Legal: string
    };

    /**
     * Constant for possible FontStyleType
     */
    static FontStyleType: {
        /** Font-A (12 x 24 dots) / Specify 7 x 9 font (half dots) */
        A: string,
        /** Font-B (9 x 24 dots) / Specify 5 x 9 font (2P-1) */
        B: string
    };

    /**
     * Constant for possible CutPaperAction
     */
    static CutPaperAction: {
        FullCut: string,
        FullCutWithFeed: string,
        PartialCut: string,
        PartialCutWithFeed: string
    };

    /**
     * Constant for possible BlackMarkType
     */
    static BlackMarkType: {
        Valid: string,
        Invalid: string,
        ValidWithDetection: string
    };

    /**
     * Constant for possible AlignmentPosition
     */
    static AlignmentPosition: {
        Left: string,
        Center: string,
        Right: string
    };

    /**
     * Constant for possible LogoSize
     */
    static LogoSize: {
        Normal: string,
        DoubleWidth: string,
        DoubleHeight: string,
        DoubleWidthDoubleHeight: string
    };

    /**
     * Constant for possible BarcodeSymbology
     */
    static BarcodeSymbology: {
        Code128: string,
        Code39: string,
        Code93: string,
        ITF: string,
        JAN8: string,
        JAN13: string,
        NW7: string,
        UPCA: string,
        UPCE: string
    };

    /**
     * Constant for possible BarcodeWidth
     */
    static BarcodeWidth: {
        Mode1: string,
        Mode2: string,
        Mode3: string,
        Mode4: string,
        Mode5: string,
        Mode6: string,
        Mode7: string,
        Mode8: string,
        Mode9: string
    };

    /**
     * Constant for possible QrCodeModel
     */
    static QrCodeModel: {
        No1: string,
        No2: string
    };

    /**
     * Constant for possible QrCodeLevel
     */
    static QrCodeLevel: {
        H: string,
        L: string,
        M: string,
        Q: string
    };

    /**
     * Constant for possible BitmapConverterRotation
     */
    static BitmapConverterRotation: {
        Normal: string,
        Left90: string,
        Right90: string,
        Rotate180: string
    };

    /**
     * Find printers available
     * @param {string} type Iterface Type: All, LAN, Bluetooth, USB
     * @return {Promise<Printers>} Returns a promise that resolves with an array of printers
     */
    static portDiscovery: (type: string) => Promise<Printers>;

    /**
     * Checks the status of the printer 
     * @param {string} port printer name i.e BT:StarMicronics
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @return {Promise<PrinterStatus>} Returns a promise that resolves with the printer status object
     */
    static checkStatus: (port: string, emulation: string) => Promise<PrinterStatus>;

    /**
     * Allows you to connect to the printer, keep the connection alive and receive status updates through an observable
     * @param {string} port printer name i.e BT:StarMicronics.
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @param {boolean} hasBarcodeReader If device has an attached barcode reader i.e mPOP
     * @return {Promise<any>} Success! if connected or error message string returned by the SDK.
     */
    static connect: (port: string, emulation: string, hasBarcodeReader: boolean) => Promise<any>;
 
     /**
      * Allows to disconnect (close the connection to the peripherals), this is useful to avoid keeping alive a connection when not in the app to save device battery 
      * (energy consumption). You should call this function when the app is paused or closed.
      * @return {Promise<any>} Success! if connected or error message string returned by the SDK.
      */
     static disconnect: () => Promise<any>;

      /**
     * Sends an Array of commands to the command buffer using the Android ICommandBuilderInterface or iOS ISCBBuilderInterface
     * @param {string} emulation  StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @param {CommandsArray} commandsArray  each command in the array should be an instance of the PrintCommand object. Example [{append:"text"}, {"openCashDrawer: 1"}]
     * * @param {string} port Optional. printer name i.e BT:StarMicronics. If not set, a printer connected via StarIOExtManager using the connect() function will be used.
     * @return {Promise<any>} Success! if printed correctly or error message string returned by the SDK.
     */
    static print: (emulation: string, commandsArray: CommandsArray, port?: string) => Promise<any>;
}

export interface Printer {
    /**
     * Printer model name and model number
     */
    modelName?: string;
    /**
     * Printer Mac Address
     */
    macAddress?: string;
    /**
     * Printer port name used to create a new port instance of SMPort or StarIOExtManager
     */
    portName?: string;
    /**
     * USB Serial Number (USB Printers Only)
     */
    USBSerialNumber?: string;
}
/**
 * Array of Printer objects returned by the portDiscovery() function
 */
export interface Printers extends Array<Printer> {
}
export interface PrinterStatus {
    /**
     * Printer Online/Offline status
     */
    offline?: boolean;
    /**
     *  Printer model name and model number
     */
    ModelName?: string;
    /**
     * Printer cover status
     */
    coverOpen?: boolean;
    /**
     * Printer Paper Cutter status
     */
    cutterError?: boolean;
    /**
     * Printer Paper status
     */
    receiptPaperEmpty?: boolean;
    /**
     * Printer Firmware information
     */
    FirmwareVersion?: string;
}
export interface PrintObj {
    /**
     * string containing the text to print, Example: "Star Clothing Boutique\n123 Star Road\nCity, State 12345\n\n"
     */
    text: string;
    /**
     *  Sends a PartialCutWithFeed command to the printer, defaults to true
     */
    cutReceipt?: boolean;
    /**
     * sends a appendPeripheral command to the printer for channels No1 and No2 - Defaults to true
     */
    openCashDrawer?: boolean;
}
export interface RasterObj extends PrintObj {
    /**
     * Font size number, defaults to 25
     */
    fontSize?: number;
    /**
     * Paper width (Units: Dots). 2 inches: 384, 3 inches: 576, 4 inches: 832, ESCPos 3 inches: 512, Dot 3 inches: 210. Defaults to 576
     */
    paperWidth?: number;
}
export interface ImageObj {
    /**
     * Image URI to print, this can be obtained via the camera or photo library or as a static resource saved on the phone memory
     */
    uri: string;
    /**
     * Image width (Units: Dots) defaults to 576
     */
    paperWidth?: number;
    /**
     *  Sends a PartialCutWithFeed command to the printer, defaults to true
     */
    cutReceipt?: boolean;
    /**
     * sends a appendPeripheral command to the printer for channels No1 and No2 - Defaults to true
     */
    openCashDrawer?: boolean;
}
export interface PrintCommand {
    /**
     * Characther encoding is used to getByte data from all subsequent commands. Default 'US-ASCII'
     * Choose the format of the return value Defined in StarPRNT.Encoding or the Encoding enum.
     * Example: {appendEncoding:'US-ASCII'}
     */
    appendEncoding?: string;
    /**
     * Select command of the code page is generated and added to the commands property.
     * Choose the format of the return value Defined in StarPRNT.CodePageType or the CodePageType enum.
     * Example: {appendCodePage:'CP858'}
     */
    appendCodePage?: string;
    /**
     * Data (Text) is added to the command buffer. Example: {append:"Star Clothing Boutique\n123 Star Road\nCity, State 12345\n\n"}
     */
    append?: string;
    /**
     * Data (Text) is added to the command buffer. Example: {appendRaw:"Star Clothing Boutique\n123 Star Road\nCity, State 12345\n\n"}
     */
    appendRaw?: string;
    /**
     * Data (Command) is added to the command buffer. Takes an array of bytes.
     * Example: {appendBytes:[0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x2e]}
     */
    appendBytes?: Array<number>;
    /**
     * Data (Command) is added to the command buffer. Takes an array of bytes.
     * Example: {appendRawBytes:[0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x2e]}
     */
    appendRawBytes?: Array<number>;
    /**
     * Set command of the character space is generated and added to the command buffer. Character Spacs (Unit: Dots) Example: 4
     */
    appendCharacterSpace?: number;
    /**
     *  Select command of the emphasis mode is generated and added to the command buffer. Example: {appendEmphasis:"SALE\n"}
     */
    appendEmphasis?: string;
    /**
      *  Enable emphasis mode is generated and added to the command buffer. Example: {enableEmphasis:true}
     */
    enableEmphasis?: boolean;
    /**
     *  Select command of the invert mode is generated and added to the command buffer. Example: {appendInvert:"Refunds and Exchanges\n"}
     */
    appendInvert?: string;
    /**
     *  Enable invert mode is generated and added to the command buffer. Example: {enableInvert:true}
     */
    enableInvert?: boolean;
    /**
     *  Select command of the under line mode is generated and added to the command buffer. Example: {appendUnderline:"30 days"}
     */
    appendUnderline?: string;
    /**
     *  Enable under line mode is generated and added to the command buffer. Example: {enableUnderline:true}
     */
    enableUnderline?: boolean;
    /**
     * Select command of the international character mode is generated and added to the command buffer.
     * Choose the format of the return value Defined in StarPRNT.InternationalType or the InternationalType enum.
     * 'UK' | 'USA' | 'France' | 'Germany' | 'Denmark' | 'Sweden' | 'Italy' | 'Spain' | 'Japan' | 'Norway' | 'Denmark2' | 'Spain2' | 'LatinAmerica' | 'Korea' | 'Ireland' | 'Legal'
     * Example {appendInternational:InternationalType.UK}
     */
    appendInternational?: string;
    /**
     * Line feed command is generated and added to the command buffer. Paper feed units (Units: Lines) Example: 2
     */
    appendLineFeed?: number;
    /**
     * Unit feed command is generated and added to the command buffer. Paper feed units (Units: Dots) Example: 64
     */
    appendUnitFeed?: number;
    /**
     * Set command of the line space is generated and added to the command buffer. Line spaces (Units: Dots) Example: 32
     */
    appendLineSpace?: number;
    /**
     * Select command of the font style is generated and added to the command buffer.
     * Choose the format of the return value defined in StarPRNT.FontStyleType or the FontStyleType enum. 'A' | 'B'
     * Example: {appendFontStyle:FontStyleType.A}
     */
    appendFontStyle?: string;
    /**
     * Paper cut command is generated and added to the command buffer.
     * Choose the format of the return value defined in StarPRNT.CutPaperAction or the CutPaperAction enum. 'FullCut' | 'FullCutWithFeed' | 'PartialCut' | 'PartialCutWithFeed'
     * Example: {appendCutPaper:CutPaperAction.PartialCutWithFeed}
     */
    appendCutPaper?: string;
    /**
     * Black mark command is generated and added to the command buffer.
     * Choose the format of the return value defined in StarPRNT.BlackMarkType or the BlackMarkType enum. 'Valid' | 'Invalid' | 'ValidWithDetection'
     * Example: {appendBlackMark: BlackMarkType.Valid}
     */
    appendBlackMark?: string;
    /**
     * Absolute position command is generated and added to the command buffer. (Unit: Dots). Send in conjunction with the data property to append absolute position just to that string
     * Example1: Append data with Absolute position {appendAbsolutePosition:40, data: "Text with absolute position"}
     * Example2: Append absolute position to subsequent commands: {appendAbsolutePosition:40}
     */
    appendAbsolutePosition?: number;
    /**
     * Alignment command is generated and added to the command buffer. Send in conjunction with the data property to append alignment position just to that string
     * Choose the format of the return value defined in StarPRNT.AlignmentPosition or the AlignmentPosition enum. 'Left' | 'Center' | 'Right'.
     * Example1 Append data with Alignment position: {appendAlignment:AlignmentPosition.Center, data: "Text with centered position"}
     * Example2 Append absolute position to subsequent commands: {appendAlignment:AlignmentPosition.Center}
     */
    appendAlignment?: string;
    /**
     * Horizontal tab set/clear command is generated and added to the command buffer. (Only works for certain printer models, check the starSDK documentation for details)
     * Array of horizontal tab positions (Units: ANK character pitch). Specifying empty array deletes all currently set horizontal tab positions.
     * Example: {appendHorizontalTabPosition:[15, 35]}
     * Delete positions Example: {appendHorizontalTabPosition:[]}
     */
    appendHorizontalTabPosition?: Array<number>;
    /**
     * Print command of the logo is generated and added to the command buffer. The logo has to be uploaded to the printer using the Star Print utility.
     * Send in conjuction with the logoSize property to set the logo size
     * Example: {appendLogo:1}
     * Example with LogoSize: {appendLogo:1, logoSize:LogoSize.DoubleWidthDoubleHeight}
     */
    appendLogo?: number;
    /**
     * Property to be used with the appendLogo command.
     * Choose the format of the return value defined in StarPRNT.LogoSize or the LogoSize enum. 'Normal' | 'DoubleWidth' | 'DoubleHeight' | 'DoubleWidthDoubleHeight';
     * Example: {appendLogo:1, logoSize:LogoSize.DoubleWidthDoubleHeight}
     */
    logoSize?: string;
    /**
     * Print command of the barcode is generated and added to the command buffer.
     * Additional Properties: BarcodeSymbology, BarcodeWidth, height, hri, absolutePosition, alignment.
     * Example: {appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true }
     * Example with absolutePosition: {appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true, absolutePosition:40 }
     * Example with alignment:{appendBarcode:"{BStar", BarcodeSymbology:BarcodeSymbology.Code128, BarcodeWidth:BarcodeWidth.Mode2, height:40, hri:true, alignment:alignment:AlignmentPosition.Center }
     */
    appendBarcode?: string;
    /**
     * Property to be used with the appendBarcode command.
     * Choose the format of the return value defined in StarPRNT.BarcodeSymbology or the BarcodeSymbology enum.
     * 'Code128' | 'Code39' | 'Code93' | 'ITF' | 'JAN8' | 'JAN13' | 'NW7' | 'UPCA' | 'UPCE' |
     * Example: {appendBarcode:'{BStar', BarcodeSymbology:BarcodeSymbology.Code128}
     */
    BarcodeSymbology?: string;
    /**
     * Property to be used with the appendBarcode command.
     * Choose the format of the return value defined in StarPRNT.BarcodeWidth or the BarcodeWidth enum.
     * Mode1 | Mode2 | Mode3 | Mode4 | Mode5 | Mode6 | Mode7 | Mode8 | Mode9
     * Example: {appendBarcode:'{BStar', BarcodeWidth:BarcodeWidth.Mode2}
     */
    BarcodeWidth?: string;
    /**
     * Property to be used with the appendBarcode command.
     * Under-bar characters. true = Valid, false = Invalid
     * Example: {appendBarcode:'{BStar', hri:true}
     */
    hri?: boolean;
    /**
     * Property to be used with the appendBarcode command or the appendMultiple command (Units:Dots)
     * appendBarcode Example: {appendBarcode:'{BStar', height:40}
     * appendMultiple: {appendMultiple:'text to print', height:40}
     */
    height?: number;
    /**
     * Property to be used with the appendBitmap command or the appendMultiple command (Units:Dots)
     * appendBitmap Example: {appendBitmap:uri, width:576}
     * appendMultiple: {appendMultiple:'text to print', width:40}
     */
    width?: number;
    /**
     * Property to be used with the appendBitmap command, the appendBarcode command, or the appendQrCode command (Units:Dots)
     * appendBitmap Example: {appendBitmap:uri, absolutePosition:40}.
     * appendBarcode Example: {appendBarcode:'{BStar', absolutePosition:40}.
     * appendQrCode Example: {appendQrCode:'{BStar', absolutePosition:40}.
     */
    absolutePosition?: number;
    /**
     * Property to be used with the appendBitmap command, the appendBarcode command, or the appendQrCode command (Units:Dots)
     * Choose the format of the return value defined in StarPRNT.AlignmentPosition or the AlignmentPosition enum. 'Left' | 'Center' | 'Right'.
     * appendBitmap Example: {appendBitmap:uri, alignment:AlignmentPosition.Center}.
     * appendBarcode Example: {appendBarcode:'{BStar', alignment:AlignmentPosition.Center}.
     * appendQrCode Example: {appendQrCode:'{BStar', alignment:AlignmentPosition.Center}.
     */
    alignment?: string;
    /**
     * Select command of the multiple mode is generated and added to the command buffer.
     * Additional properties: width:number, height:number
     * Example: {appendMultiple:"   $156.95\n", width:2, height:2}.
     */
    appendMultiple?: string;
    /**
     * Enable multiple mode is generated and added to the command buffer.
     * Additional properties: width:number, height:number
     * Example: {enableMultiple:true, width:2, height:2}
     * Disable Example: {enableMultiple:false}
     */
    enableMultiple?: boolean;
    /**
     * Print command of the QR code is generated and added to the command buffer.
     * Additional Properties: QrCodeModel, QrCodeLevel, cell, absolutePosition, alignment.
     * Example: {appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8}.
     * Example with absolutePosition: {appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8, absolutePosition: 40 }.
     * Example with alignment: {appendQrCode:"{BStar", QrCodeModel:"No2", QrCodeLevel:"L", cell: 8, alignment:"Center" }.
     */
    appendQrCode?: string;
    /**
     * Property to be used with the appendQrCode command.
     * Choose the format of the return value defined in StarPRNT.QrCodeModel or the QrCodeModel enum. 'No1' | 'No2' Default 'No2'
     * Example: {appendQrCode:'{BStar', QrCodeModel:QrCodeModel.No1}
     */
    QrCodeModel?: string;
    /**
     * Property to be used with the appendQrCode command.
     * Choose the format of the return value defined in StarPRNT.QrCodeLevel or the QrCodeLevel enum. 'No1' | 'No2'. Default 'H'
     * Example: {appendQrCode:'{BStar', QrCodeLevel:QrCodeLevel.H}
     */
    QrCodeLevel?: string;
    /**
     * Property to be used with the appendQrCode command. QRCode Cell size. Default 4.
     * Example: {appendQrCode:'{BStar', cell:8}
     */
    cell?: number;
    /**
     * Print command of the bitmap is generated and added to the command buffer. Takes a string image URI
     * this can be obtained via the camera or photo library or as a static resource saved on the phone memory.
     * Additional Properties: diffusion, width, bothScale, rotation, absolutePosition, alignment.
     * Example: {appendBitmap:uri, diffusion: true, width:576, bothScale: true}
     * Example with absolutePosition: {appendBitmap:uri, diffusion: true, width:576, bothScale: true, absolutePosition: 40 }.
     * Example with alignment: {appendBitmap:uri, diffusion: true, width:576, bothScale: true, alignment:"Center" }.
     */
    appendBitmap?: string;
    /**
     * Property to be used with the appendBitmap command. Random dither: true = Valid, false = Invalid. Default true.
     * Example: {appendBitmap:uri, diffusion: false }
     */
    diffusion?: boolean;
    /**
     * Property to be used with the appendBitmap command. Height is changed according to the conversion rate of the width property.
     * true = Valid, false = Invalid. Default true.
     * Example: {appendBitmap:uri, bothScale: true }
     */
    bothScale?: boolean;
    /**
     * Property to be used with the appendBitmap command.
     * Choose the format of the return value defined in StarPRNT.BitmapConverterRotation or the BitmapConverterRotation enum.
     * 'Normal' | 'Left90' | 'Right90' | 'Rotate180'
     * Example: {appendBitmap:uri, rotation: BitmapConverterRotation.Left90 }
     */
    rotation?: string;
    /**
     * sends a appendPeripheral command to the printer for channel number: Example: 1 = No1, 2 = No2
     */
    openCashDrawer?: number;
}
/**
 * Emulation constants
 */
export declare enum Emulation {
    /** mPOP, SM-L200, SM-L300, SM-S210i, SM-S220i, SM-S230i, SM-T300i/T300, SM-T400i */
    StarPRNT = "StarPRNT",
    /** SM-L200, SM-L300 */
    StarPRNTL = "StarPRNTL",
    /** FVP10, TSP650II, TSP700II, TSP800II */
    StarLine = "StarLine",
    /** TSP100 */
    StarGraphic = "StarGraphic",
    /** BSC10 */
    EscPos = "EscPos",
    /** SM-S210i, SM-S220i, SM-S230i, SM-T300i/T300, SM-T400i */
    EscPosMobile = "EscPosMobile",
    /** SP700 */
    StarDotImpact = "StarDotImpact",
}
/**
 * Encoding constants
 */
export declare enum Encoding {
    /** English */
    USASCII = "US-ASCII",
    /** French, German, Portuguese, Spanish */
    Windows1252 = "Windows-1252",
    /** Japanese */
    ShiftJIS = "Shift-JIS",
    /** Russian */
    Windows1251 = "Windows-1251",
    /** Simplified Chinese */
    GB2312 = "GB2312",
    /** Traditional Chinese */
    Big5 = "Big5",
    /** UFT8 */
    UTF8 = "UTF-8",
}
/**
 * CodePageType constants
 */
export declare enum CodePageType {
    CP737 = "CP737",
    CP772 = "CP772",
    CP774 = "CP774",
    CP851 = "CP851",
    CP852 = "CP852",
    CP855 = "CP855",
    CP857 = "CP857",
    CP858 = "CP858",
    CP860 = "CP860",
    CP861 = "CP861",
    CP862 = "CP862",
    CP863 = "CP863",
    CP864 = "CP864",
    CP865 = "CP865",
    CP869 = "CP869",
    CP874 = "CP874",
    CP928 = "CP928",
    CP932 = "CP932",
    CP999 = "CP999",
    CP1001 = "CP1001",
    CP1250 = "CP1250",
    CP1251 = "CP1251",
    CP1252 = "CP1252",
    CP2001 = "CP2001",
    CP3001 = "CP3001",
    CP3002 = "CP3002",
    CP3011 = "CP3011",
    CP3012 = "CP3012",
    CP3021 = "CP3021",
    CP3041 = "CP3041",
    CP3840 = "CP3840",
    CP3841 = "CP3841",
    CP3843 = "CP3843",
    CP3845 = "CP3845",
    CP3846 = "CP3846",
    CP3847 = "CP3847",
    CP3848 = "CP3848",
    UTF8 = "UTF8",
    Blank = "Blank",
}
/**
 * InternationalType constants
 */
export declare enum InternationalType {
    UK = "UK",
    USA = "USA",
    France = "France",
    Germany = "Germany",
    Denmark = "Denmark",
    Sweden = "Sweden",
    Italy = "Italy",
    Spain = "Spain",
    Japan = "Japan",
    Norway = "Norway",
    Denmark2 = "Denmark2",
    Spain2 = "Spain2",
    LatinAmerica = "LatinAmerica",
    Korea = "Korea",
    Ireland = "Ireland",
    Legal = "Legal",
}
/**
 * FontStyleType constants.
 */
export declare enum FontStyleType {
    /** Font-A (12 x 24 dots) / Specify 7 x 9 font (half dots) */
    A = "A",
    /** Font-B (9 x 24 dots) / Specify 5 x 9 font (2P-1) */
    B = "B",
}
/**
 * CutPaperAction constants.
 */
export declare enum CutPaperAction {
    FullCut = "FullCut",
    FullCutWithFeed = "FullCutWithFeed",
    PartialCut = "PartialCut",
    PartialCutWithFeed = "PartialCutWithFeed",
}
/**
 * BlackMarkType constants.
 */
export declare enum BlackMarkType {
    Valid = "Valid",
    Invalid = "Invalid",
    ValidWithDetection = "ValidWithDetection",
}
/**
 * LogoSize constants
 */
export declare enum LogoSize {
    Normal = "Normal",
    DoubleWidth = "DoubleWidth",
    DoubleHeight = "DoubleHeight",
    DoubleWidthDoubleHeight = "DoubleWidthDoubleHeight",
}
/**
 * AlignmentPosition constants
 */
export declare enum AlignmentPosition {
    Left = "Left",
    Center = "Center",
    Right = "Right",
}
/**
 * BarcodeSymbology constants
 */
export declare enum BarcodeSymbology {
    Code128 = "Code128",
    Code39 = "Code39",
    Code93 = "Code93",
    ITF = "ITF",
    JAN8 = "JAN8",
    JAN13 = "JAN13",
    NW7 = "NW7",
    UPCA = "UPCA",
    UPCE = "UPCE",
}
/**
 * BarcodeWidth constants
 */
export declare enum BarcodeWidth {
    Mode1 = "Mode1",
    Mode2 = "Mode2",
    Mode3 = "Mode3",
    Mode4 = "Mode4",
    Mode5 = "Mode5",
    Mode6 = "Mode6",
    Mode7 = "Mode7",
    Mode8 = "Mode8",
    Mode9 = "Mode9",
}
/**
 * QrCodeModel constants
 */
export declare enum QrCodeModel {
    No1 = "No1",
    No2 = "No2",
}
/**
 * QrCodeLevel constants
 */
export declare enum QrCodeLevel {
    H = "H",
    L = "L",
    M = "M",
    Q = "Q",
}
/**
 * BitmapConverterRotation constants
 */
export declare enum BitmapConverterRotation {
    Normal = "Normal",
    Left90 = "Left90",
    Right90 = "Right90",
    Rotate180 = "Rotate180",
}
/**
 * Push a new PrintCommand object to the array for a separate instruction to the printer. Example [{append:"text"}, {"openCashDrawer: 1"}]
 */
export interface CommandsArray extends Array<PrintCommand> {
}
