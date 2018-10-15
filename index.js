
import { NativeEventEmitter, NativeModules } from 'react-native';

const  { RNStarPrnt } = NativeModules;

export class StarPRNT {

    static StarPRNTManagerEmitter = new NativeEventEmitter(RNStarPrnt);

    /**
    * Constant for Emulation
    */
    static Emulation = {
        StarPRNT: 'StarPRNT',
        StarPRNTL: 'StarPRNTL',
        StarLine: 'StarLine',
        StarGraphic: 'StarGraphic',
        EscPos: 'EscPos',
        EscPosMobile: 'EscPosMobile',
        StarDotImpact: 'StarDotImpact',
    };

    /**
     * Constant for possible Encoding
     */
    static Encoding = {
        USASCII: 'US-ASCII',
        Windows1252: 'Windows-1252',
        ShiftJIS: 'Shift-JIS',
        Windows1251: 'Windows-1251',
        GB2312: 'GB2312',
        Big5: 'Big5',
        UTF8: 'UTF-8'
    };

    /**
     * CodePageType constants
     */
    static CodePageType = {
        CP737: 'CP737',
        CP772: 'CP772',
        CP774: 'CP774',
        CP851: 'CP851',
        CP852: 'CP852',
        CP855: 'CP855',
        CP857: 'CP857',
        CP858: 'CP858',
        CP860: 'CP860',
        CP861: 'CP861',
        CP862: 'CP862',
        CP863: 'CP863',
        CP864: 'CP864',
        CP865: 'CP865',
        CP869: 'CP869',
        CP874: 'CP874',
        CP928: 'CP928',
        CP932: 'CP932',
        CP999: 'CP999',
        CP1001: 'CP1001',
        CP1250: 'CP1250',
        CP1251: 'CP1251',
        CP1252: 'CP1252',
        CP2001: 'CP2001',
        CP3001: 'CP3001',
        CP3002: 'CP3002',
        CP3011: 'CP3011',
        CP3012: 'CP3012',
        CP3021: 'CP3021',
        CP3041: 'CP3041',
        CP3840: 'CP3840',
        CP3841: 'CP3841',
        CP3843: 'CP3843',
        CP3845: 'CP3845',
        CP3846: 'CP3846',
        CP3847: 'CP3847',
        CP3848: 'CP3848',
        UTF8: 'UTF8',
        Blank: 'Blank'
    };

    /**
     * Constant for possible InternationalType
     */
    static InternationalType = {
        UK: 'UK',
        USA: 'USA',
        France: 'France',
        Germany: 'Germany',
        Denmark: 'Denmark',
        Sweden: 'Sweden',
        Italy: 'Italy',
        Spain: 'Spain',
        Japan: 'Japan',
        Norway: 'Norway',
        Denmark2: 'Denmark2',
        Spain2: 'Spain2',
        LatinAmerica: 'LatinAmerica',
        Korea: 'Korea',
        Ireland: 'Ireland',
        Legal: 'Legal'
    };

    /**
     * Constant for possible FontStyleType
     */
    static FontStyleType = {
        /** Font-A (12 x 24 dots) / Specify 7 x 9 font (half dots) */
        A: 'A',
        /** Font-B (9 x 24 dots) / Specify 5 x 9 font (2P-1) */
        B: 'B'
    };

    /**
     * Constant for possible CutPaperAction
     */
    static CutPaperAction = {
        FullCut: 'FullCut',
        FullCutWithFeed: 'FullCutWithFeed',
        PartialCut: 'PartialCut',
        PartialCutWithFeed: 'PartialCutWithFeed'
    };

    /**
     * Constant for possible BlackMarkType
     */
    static BlackMarkType = {
        Valid: 'Valid',
        Invalid: 'Invalid',
        ValidWithDetection: 'ValidWithDetection'
    };

    /**
     * Constant for possible AlignmentPosition
     */
    static AlignmentPosition = {
        Left: 'Left',
        Center: 'Center',
        Right: 'Right'
    };

    /**
     * Constant for possible LogoSize
     */
    static LogoSize = {
        Normal: 'Normal',
        DoubleWidth: 'DoubleWidth',
        DoubleHeight: 'DoubleHeight',
        DoubleWidthDoubleHeight: 'DoubleWidthDoubleHeight'
    };

    /**
     * Constant for possible BarcodeSymbology
     */
    static BarcodeSymbology = {
        Code128: 'Code128',
        Code39: 'Code39',
        Code93: 'Code93',
        ITF: 'ITF',
        JAN8: 'JAN8',
        JAN13: 'JAN13',
        NW7: 'NW7',
        UPCA: 'UPCA',
        UPCE: 'UPCE'
    };

    /**
     * Constant for possible BarcodeWidth
     */
    static BarcodeWidth = {
        Mode1: 'Mode1',
        Mode2: 'Mode2',
        Mode3: 'Mode3',
        Mode4: 'Mode4',
        Mode5: 'Mode5',
        Mode6: 'Mode6',
        Mode7: 'Mode7',
        Mode8: 'Mode8',
        Mode9: 'Mode9'
    };

    /**
     * Constant for possible QrCodeModel
     */
    static QrCodeModel = {
        No1: 'No1',
        No2: 'No2'
    };

    /**
     * Constant for possible QrCodeLevel
     */
    static QrCodeLevel = {
        H: 'H',
        L: 'L',
        M: 'M',
        Q: 'Q'
    };

    /**
     * Constant for possible BitmapConverterRotation
     */
    static BitmapConverterRotation = {
        Normal: 'Normal',
        Left90: 'Left90',
        Right90: 'Right90',
        Rotate180: 'Rotate180'
    };

    /**
     * Find printers available
     * @param {string} type Iterface Type: All, LAN, Bluetooth, USB
     * @return {Promise<Printers>} Returns a promise that resolves with an array of printers
     */
    static portDiscovery(type) {
        return RNStarPrnt.portDiscovery(type);
    }

    /**
     * Checks the status of the printer 
     * @param {string} port printer name i.e BT:StarMicronics
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @return {Promise<PrinterStatus>} Returns a promise that resolves with the printer status object
     */
    static checkStatus(port, emulation){
        return RNStarPrnt.checkStatus(port, emulation);
    }
    /**
     * Allows you to connect to the printer, keep the connection alive and receive status updates through an observable
     * @param {string} port printer name i.e BT:StarMicronics.
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @param {boolean} hasBarcodeReader If device has an attached barcode reader i.e mPOP
     * @return {Observable<any>} Success! if connected or error message string returned by the SDK.
     */
    static connect(port, emulation, hasBarcodeReader) {
        hasBarcodeReader = (hasBarcodeReader) ? true : false; 
        return RNStarPrnt.connect(port, emulation, hasBarcodeReader);        
       }
 
     /**
      * Allows to disconnect (close the connection to the peripherals), this is useful to avoid keeping alive a connection when not in the app to save device battery 
      * (energy consumption). You should call this function when the app is paused or closed.
      * @return {Promise<any>} Success! if connected or error message string returned by the SDK.
      */
     static disconnect() { 
         return RNStarPrnt.disconnect(); 
       }

      /**
     * Sends an Array of commands to the command buffer using the Android ICommandBuilderInterface or iOS ISCBBuilderInterface
     * @param {string} emulation  StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @param {CommandsArray} commandsArray  each command in the array should be an instance of the PrintCommand object. Example [{append:"text"}, {"openCashDrawer: 1"}]
     * * @param {string} port Optional. printer name i.e BT:StarMicronics. If not set, a printer connected via StarIOExtManager using the connect() function will be used.
     * @return {Promise<any>} Success! if printed correctly or error message string returned by the SDK.
     */
    static print(emulation, commandsArray, port) { 
        return RNStarPrnt.print(port, emulation, commandsArray); 
    }


}