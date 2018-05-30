
# react-native-star-prnt

react-native bridge for [Star micronics printers](http://www.starmicronics.com/pages/All-Products).

Ionic/Cordova Version ➜ [here](https://github.com/auctifera-josed/starprnt)

## Installation

`$ npm install react-native-star-prnt --save`

### Link

`$ react-native link react-native-star-prnt`


#### iOS Configuration

1. In XCode, go to Build Phases, Link Binary with Libraries and Add the following frameworks:

    - Go to `node_modules` ➜ `react-native-star-prnt` ➜ `ios` ➜ `Frameworks` and add `StarIO.framework` and `StarIO_Extension.framework`
    - Add the `CoreBluetooth.framework`
    - Add the `ExternalAccessory.framework`
2. Go to Build Settings ➜ Search Paths and Add 
`$(PROJECT_DIR)/../node_modules/react-native-star-prnt/ios/Frameworks` to Framework Search Paths  

For Bluetooth printers:

1. Click on the information property list file (default : “Info.plist”).
2. Add the “Supported external accessory protocols” Key.
3. Click the triangle of this key and set the value for the `Item 0` to `jp.star-m.starpro`

## Usage
```javascript
import { StarPRNT } from 'react-native-star-prnt';

async function portDiscovery() {
    try {
      let printers = await StarPRNT.portDiscovery('All');
      console.log(printers);
    } catch (e) {
      console.error(e);
    }
  }

```
  
## Take a look at the [Documentation](/Documentation.md)