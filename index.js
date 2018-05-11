
import { NativeModules } from 'react-native';

const  RNStarPrnt = NativeModules.RNStarPrnt;

export class StarPRNT {

    /**
     * Find printers available
     * @param {string} type Iterface Type: All, LAN, Bluetooth, USB
     * @return {Promise<Printers>} Returns a promise that resolves with an array of printers
     */
    static portDiscovery(type:string) {
        return RNStarPrnt.portDiscovery(type);
    }

    /**
     * Checks the status of the printer 
     * @param {string} port printer name i.e BT:StarMicronics
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @return {Promise<PrinterStatus>} Returns a promise that resolves with the printer status object
     */
    static checkStatus(port: string, emulation:string){
        return RNStarPrnt.checkStatus(port, emulation);
    }
    /**
     * Allows you to connect to the printer, keep the connection alive and receive status updates through an observable
     * @param {string} port printer name i.e BT:StarMicronics.
     * @param {string} emulation StarPrinter Emulation type: "StarPRNT", "StarPRNTL", "StarLine", "StarGraphic", "EscPos", "EscPosMobile", "StarDotImpact"
     * @return {Observable<any>} Success! if connected or error message string returned by the SDK.
     */
    static connect(port: string, emulation: string) { 
        return RNStarPrnt.connect(port, emulation);        
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
    static print(emulation: string, commandsArray: CommandsArray, port: string) { 
        return RNStarPrnt.print(port, emulation, commandsArray); 
    }


}