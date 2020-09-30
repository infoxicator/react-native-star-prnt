
package net.infoxication.reactstarprnt;

import android.content.ContentResolver;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.Canvas;
import android.graphics.Typeface;
import android.graphics.Rect;
import android.graphics.Color;
import android.provider.MediaStore;
import android.text.TextPaint;
import android.net.Uri;
import android.provider.MediaStore;
import androidx.annotation.Nullable;
import android.text.StaticLayout;
import android.text.Layout;
import android.util.Base64;
import android.graphics.BitmapFactory;

import com.facebook.common.util.ExceptionWithNoStacktrace;
import com.facebook.react.bridge.Dynamic;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableType;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.nio.charset.UnsupportedCharsetException;
import java.util.Locale;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.starmicronics.stario.PortInfo;
import com.starmicronics.stario.StarIOPort;
import com.starmicronics.stario.StarIOPortException;
import com.starmicronics.stario.StarPrinterStatus;
import com.starmicronics.starioextension.IConnectionCallback;
import com.starmicronics.starioextension.StarIoExt;
import com.starmicronics.starioextension.StarIoExt.Emulation;
import com.starmicronics.starioextension.ICommandBuilder;
import com.starmicronics.starioextension.ICommandBuilder.CutPaperAction;
import com.starmicronics.starioextension.ICommandBuilder.CodePageType;
import com.starmicronics.starioextension.StarIoExtManager;
import com.starmicronics.starioextension.StarIoExtManagerListener;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

public class RNStarPrntModule extends ReactContextBaseJavaModule {

  private final ReactApplicationContext reactContext;
  private StarIoExtManager starIoExtManager;

  public RNStarPrntModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
  }

  @Override
  public String getName() {
    return "RNStarPrnt";
  }

  @ReactMethod
  public void portDiscovery(final String strInterface, final Promise promise) {
    new Thread(new Runnable() {
      public void run() {

        WritableArray result = new WritableNativeArray();
        try {

          if (strInterface.equals("LAN")) {
            result = getPortDiscovery("LAN");
          } else if (strInterface.equals("Bluetooth")) {
            result = getPortDiscovery("Bluetooth");
          } else if (strInterface.equals("USB")) {
            result = getPortDiscovery("USB");
          } else {
            result = getPortDiscovery("All");
          }

        } catch (StarIOPortException exception) {
          promise.reject("PORT_DISCOVERY_ERROR", exception);

        } finally {
          promise.resolve(result);
        }

      }
    }).start();
  }

  @ReactMethod
  public void checkStatus(final String portName, final String emulation, final Promise promise) {
    new Thread(new Runnable() {
      public void run() {

        String portSettings = getPortSettingsOption(emulation);

        StarIOPort port = null;
        try {

          port = StarIOPort.getPort(portName, portSettings, 10000, getReactApplicationContext());

          // A sleep is used to get time for the socket to completely open
          try {
            Thread.sleep(500);
          } catch (InterruptedException e) {
          }

          StarPrinterStatus status;
          Map<String, String> firmwareInformationMap = port.getFirmwareInformation();
          status = port.retreiveStatus();


          WritableNativeMap json = new WritableNativeMap();
          json.putBoolean("offline", status.offline);
          json.putBoolean("coverOpen", status.coverOpen);
          json.putBoolean("cutterError", status.cutterError);
          json.putBoolean("receiptPaperEmpty", status.receiptPaperEmpty);
          json.putString("ModelName", firmwareInformationMap.get("ModelName"));
          json.putString("FirmwareVersion", firmwareInformationMap.get("FirmwareVersion"));

          promise.resolve(json);


        } catch (StarIOPortException e) {
          promise.reject("CHECK_STATUS_ERROR", e);
        } finally {

          if (port != null) {
            try {
              StarIOPort.releasePort(port);
            } catch (StarIOPortException e) {
              promise.reject("CHECK_STATUS_ERROR", e.getMessage());
            }
          }

        }

      }
    }).start();
  }

  @ReactMethod
  public void connect(final String portName, final String emulation, final Boolean hasBarcodeReader, final Promise promise) {
    Context context = getCurrentActivity();

    String portSettings = getPortSettingsOption(emulation);
    if (starIoExtManager != null && starIoExtManager.getPort() != null) {
      starIoExtManager.disconnect(new IConnectionCallback() {
          @Override
          public void onConnected(ConnectResult connectResult) {
              if (connectResult == ConnectResult.Success || connectResult == ConnectResult.AlreadyConnected) {

                  promise.resolve("Printer Connected");

              } else {
                  promise.reject("CONNECT_ERROR", "Error Connecting to the printer");
              }
          }
          @Override
          public void onDisconnected() {
              //Do nothing
          }
      });
    }
    starIoExtManager = new StarIoExtManager(hasBarcodeReader ? StarIoExtManager.Type.WithBarcodeReader : StarIoExtManager.Type.Standard, portName, portSettings, 10000, context);
    starIoExtManager.setListener(starIoExtManagerListener);

    new Thread(new Runnable() {
      public void run() {

        if (starIoExtManager != null) starIoExtManager.connect(new IConnectionCallback() {
          @Override
          public void onConnected(ConnectResult connectResult) {
            if (connectResult == ConnectResult.Success || connectResult == ConnectResult.AlreadyConnected) {

              promise.resolve("Printer Connected");

            } else {
              promise.reject("CONNECT_ERROR", "Error Connecting to the printer");
            }
          }

          @Override
          public void onDisconnected() {
            //Do nothing
          }
        });

      }
    }).start();
  }

  @ReactMethod
  public void disconnect(final Promise promise) {
    new Thread(new Runnable() {
      public void run() {
        if (starIoExtManager != null && starIoExtManager.getPort() != null) {
          starIoExtManager.disconnect(new IConnectionCallback() {
            @Override
            public void onConnected(ConnectResult connectResult) {
              // nothing
            }

            @Override
            public void onDisconnected() {
              //sendEvent("printerOffline", null);
              starIoExtManager.setListener(null); //remove the listener?
              promise.resolve("Printer Disconnected");
            }
          });
        } else {
          promise.resolve("No printers connected");
        }

      }
    }).start();
  }

  @ReactMethod
  public void print(final String portName, String emulation, final ReadableArray printCommands, final Promise promise) {

    final String portSettings = getPortSettingsOption(emulation);
    final Emulation _emulation = getEmulation(emulation);
    final Context context = getCurrentActivity();

    new Thread(new Runnable() {
      public void run() {

        ICommandBuilder builder = StarIoExt.createCommandBuilder(_emulation);

        builder.beginDocument();

        appendCommands(builder, printCommands, context);

        builder.endDocument();

        byte[] commands = builder.getCommands();

        if (portName == "null") { // use StarIOExtManager
          sendCommand(commands, starIoExtManager.getPort(), promise);

        } else {//use StarIOPort
          sendCommand(context, portName, portSettings, commands, promise);
        }
      }

    }).start();
  }

  private Emulation getEmulation(String emulation) {

    if (emulation.equals("StarPRNT")) return Emulation.StarPRNT;
    else if (emulation.equals("StarPRNTL")) return Emulation.StarPRNTL;
    else if (emulation.equals("StarLine")) return Emulation.StarLine;
    else if (emulation.equals("StarGraphic")) return Emulation.StarGraphic;
    else if (emulation.equals("EscPos")) return Emulation.EscPos;
    else if (emulation.equals("EscPosMobile")) return Emulation.EscPosMobile;
    else if (emulation.equals("StarDotImpact")) return Emulation.StarDotImpact;
    else return Emulation.StarLine;
  }

  ;

  private WritableArray getPortDiscovery(String interfaceName) throws StarIOPortException {
    List<PortInfo> BTPortList;
    List<PortInfo> TCPPortList;
    List<PortInfo> USBPortList;

    final ArrayList<PortInfo> arrayDiscovery = new ArrayList<PortInfo>();

    WritableArray arrayPorts = new WritableNativeArray();


    if (interfaceName.equals("Bluetooth") || interfaceName.equals("All")) {
      BTPortList = StarIOPort.searchPrinter("BT:");

      for (PortInfo portInfo : BTPortList) {
        arrayDiscovery.add(portInfo);
      }
    }
    if (interfaceName.equals("LAN") || interfaceName.equals("All")) {
      TCPPortList = StarIOPort.searchPrinter("TCP:");

      for (PortInfo portInfo : TCPPortList) {
        arrayDiscovery.add(portInfo);
      }
    }
    if (interfaceName.equals("USB") || interfaceName.equals("All")) {
      try {
        USBPortList = StarIOPort.searchPrinter("USB:", getReactApplicationContext());
      } catch (StarIOPortException e) {
        USBPortList = new ArrayList<PortInfo>();
      }
      for (PortInfo portInfo : USBPortList) {
        arrayDiscovery.add(portInfo);
      }
    }

    for (PortInfo discovery : arrayDiscovery) {
      String portName;

      WritableMap port = new WritableNativeMap();
      if (discovery.getPortName().startsWith("BT:"))
        port.putString("portName", "BT:" + discovery.getMacAddress());
      else port.putString("portName", discovery.getPortName());

      if (!discovery.getMacAddress().equals("")) {

        port.putString("macAddress", discovery.getMacAddress());

        if (discovery.getPortName().startsWith("BT:")) {
          port.putString("modelName", discovery.getPortName());
        } else if (!discovery.getModelName().equals("")) {
          port.putString("modelName", discovery.getModelName());
        }
      } else if (interfaceName.equals("USB") || interfaceName.equals("All")) {
        if (!discovery.getModelName().equals("")) {
          port.putString("modelName", discovery.getModelName());
        }
        if (!discovery.getUSBSerialNumber().equals(" SN:")) {
          port.putString("USBSerialNumber", discovery.getUSBSerialNumber());
        }
      }

      arrayPorts.pushMap(port);
    }

    return arrayPorts;
  }

  private String getPortSettingsOption(String emulation) { // generate the portsettings depending on the emulation type

    String portSettings = "";

    if (emulation.equals("EscPosMobile")) portSettings += "mini";
    else if (emulation.equals("EscPos")) portSettings += "escpos";
    else //StarLine, StarGraphic, StarDotImpact
      if (emulation.equals("StarPRNT") || emulation.equals("StarPRNTL")) {
        portSettings += "Portable";
        portSettings += ";l"; //retry on
      } else portSettings += "";
    return portSettings;
  }

  private boolean sendCommand(byte[] commands, StarIOPort port, Promise promise) {

    try {
			/*
			 * using StarIOPort3.1.jar (support USB Port) Android OS Version: upper 2.2
			 */
      try {
        Thread.sleep(200);
      } catch (InterruptedException e) {
      }
      if (port == null) { //Not connected or port closed
        promise.reject("STARIO_PORT_EXCEPTION", "Unable to Open Port, Please Connect to the printer before sending commands");
        return false;
      }

			/*
			 * Using Begin / End Checked Block method When sending large amounts of raster data,
			 * adjust the value in the timeout in the "StarIOPort.getPort" in order to prevent
			 * "timeout" of the "endCheckedBlock method" while a printing.
			 *
			 * If receipt print is success but timeout error occurs(Show message which is "There
			 * was no response of the printer within the timeout period." ), need to change value
			 * of timeout more longer in "StarIOPort.getPort" method.
			 * (e.g.) 10000 -> 30000
			 */
      StarPrinterStatus status;

      status = port.beginCheckedBlock();

      if (status.offline) {
        //sendEvent("printerOffline", null);
        throw new StarIOPortException("A printer is offline");
        //callbackContext.error("The printer is offline");
      }

      port.writePort(commands, 0, commands.length);

      port.setEndCheckedBlockTimeoutMillis(30000);// Change the timeout time of endCheckedBlock method.

      status = port.endCheckedBlock();

      if (status.coverOpen) {
        promise.reject("STARIO_PORT_EXCEPTION", "Cover open");
        //sendEvent("printerCoverOpen", null);
        return false;
      } else if (status.receiptPaperEmpty) {
        promise.reject("STARIO_PORT_EXCEPTION", "Empty paper");
        //sendEvent("printerPaperEmpty", null);
        return false;
      } else if (status.offline) {
        promise.reject("STARIO_PORT_EXCEPTION", "Printer offline");
        //sendEvent("printerOffline", null);
        return false;
      }
      promise.resolve("Success!");

    } catch (StarIOPortException e) {
      //sendEvent("printerImpossible", e.getMessage());
      promise.reject("STARIO_PORT_EXCEPTION", e.getMessage());
      return false;
    } finally {
      return true;
    }
  }

  private boolean sendCommand(Context context, String portName, String portSettings, byte[] commands, Promise promise) {

    StarIOPort port = null;
    try {
			/*
			 * using StarIOPort3.1.jar (support USB Port) Android OS Version: upper 2.2
			 */
      port = StarIOPort.getPort(portName, portSettings, 10000, context);
      try {
        Thread.sleep(100);
      } catch (InterruptedException e) {
      }

			/*
			 * Using Begin / End Checked Block method When sending large amounts of raster data,
			 * adjust the value in the timeout in the "StarIOPort.getPort" in order to prevent
			 * "timeout" of the "endCheckedBlock method" while a printing.
			 *
			 * If receipt print is success but timeout error occurs(Show message which is "There
			 * was no response of the printer within the timeout period." ), need to change value
			 * of timeout more longer in "StarIOPort.getPort" method.
			 * (e.g.) 10000 -> 30000
			 */
      StarPrinterStatus status = port.beginCheckedBlock();

      if (status.offline) {
        //throw new StarIOPortException("A printer is offline");
        throw new StarIOPortException("A printer is offline");
      }

      port.writePort(commands, 0, commands.length);


      port.setEndCheckedBlockTimeoutMillis(30000);// Change the timeout time of endCheckedBlock method.
      status = port.endCheckedBlock();

      if (status.coverOpen) {
        promise.reject("STARIO_PORT_EXCEPTION", "Cover open");
        return false;
      } else if (status.receiptPaperEmpty) {
        promise.reject("STARIO_PORT_EXCEPTION", "Empty paper");
        return false;
      } else if (status.offline) {
        promise.reject("STARIO_PORT_EXCEPTION", "Printer offline");
        return false;
      }
      promise.resolve("Success!");

    } catch (StarIOPortException e) {
      promise.reject("STARIO_PORT_EXCEPTION", e.getMessage());
    } finally {
      if (port != null) {
        try {
          StarIOPort.releasePort(port);
        } catch (StarIOPortException e) {
        }
      }
      return true;
    }
  }
    private void appendCommands(ICommandBuilder builder, ReadableArray printCommands, Context context) {
        Charset encoding = Charset.forName("US-ASCII");
        for (int i = 0; i < printCommands.size(); i++) {
            ReadableMap command = printCommands.getMap(i);
            if(command.hasKey("appendCharacterSpace")) builder.appendCharacterSpace(command.getInt("appendCharacterSpace"));
            else if (command.hasKey("appendEncoding")) encoding = getEncoding(command.getString("appendEncoding"));
            else if (command.hasKey("appendCodePage")) builder.appendCodePage(getCodePageType(command.getString("appendCodePage")));
            else if (command.hasKey("append")) builder.append(command.getString("append").getBytes(encoding));
            else if (command.hasKey("appendRaw")) builder.append(command.getString("appendRaw").getBytes(encoding));
            else if (command.hasKey("appendEmphasis")) builder.appendEmphasis(command.getString("appendEmphasis").getBytes(encoding));
            else if (command.hasKey("enableEmphasis")) builder.appendEmphasis(command.getBoolean("enableEmphasis"));
            else if (command.hasKey("appendInvert")) builder.appendInvert(command.getString("appendInvert").getBytes(encoding));
            else if (command.hasKey("enableInvert")) builder.appendInvert(command.getBoolean("enableInvert"));
            else if (command.hasKey("appendUnderline")) builder.appendUnderLine(command.getString("appendUnderline").getBytes(encoding));
            else if (command.hasKey("enableUnderline")) builder.appendUnderLine(command.getBoolean("enableUnderline"));
            else if (command.hasKey("appendInternational")) builder.appendInternational(getInternational(command.getString("appendInternational")));
            else if (command.hasKey("appendLineFeed")) builder.appendLineFeed(command.getInt("appendLineFeed"));
            else if (command.hasKey("appendUnitFeed")) builder.appendUnitFeed(command.getInt("appendUnitFeed"));
            else if (command.hasKey("appendLineSpace")) builder.appendLineSpace(command.getInt("appendLineSpace"));
            else if (command.hasKey("appendFontStyle")) builder.appendFontStyle(getFontStyle(command.getString("appendFontStyle")));
            else if (command.hasKey("appendCutPaper")) builder.appendCutPaper(getCutPaperAction(command.getString("appendCutPaper")));
            else if (command.hasKey("openCashDrawer")) builder.appendPeripheral(getPeripheralChannel(command.getInt("openCashDrawer")));
            else if (command.hasKey("appendBlackMark")) builder.appendBlackMark(getBlackMarkType(command.getString("appendBlackMark")));
            else if (command.hasKey("appendBytes")) {
                ReadableArray bytesArray = command.getArray("appendBytes");
                if (bytesArray != null ) {
                    byte[] byteData = new byte[bytesArray.size() + 1];
                    for (int j = 0; j < bytesArray.size(); j++) {
                        byteData[j] = (byte) bytesArray.getInt(j);
                    }
                    builder.append(byteData);
                }
            }else if (command.hasKey("appendRawBytes")) {
                ReadableArray rawBytesArray = command.getArray("appendRawBytes");
                    if (rawBytesArray != null ) {
                    byte[] rawByteData = new byte[rawBytesArray.size()+1];
                    for(int j=0; j < rawBytesArray.size(); j++){
                        rawByteData[j] = (byte)rawBytesArray.getInt(j);
                    }
                    builder.appendRaw(rawByteData);
                }
            }else if (command.hasKey("appendAbsolutePosition")) {
                if(command.hasKey("data")) builder.appendAbsolutePosition((command.getString("data").getBytes(encoding)), command.getInt("appendAbsolutePosition"));
                else builder.appendAbsolutePosition(command.getInt("appendAbsolutePosition"));
            } else if (command.hasKey("appendAlignment")) {
                if(command.hasKey("data")) builder.appendAlignment((command.getString("data").getBytes(encoding)), getAlignment(command.getString("appendAlignment")));
                else builder.appendAlignment(getAlignment(command.getString("appendAlignment")));
            } else if (command.hasKey("appendHorizontalTabPosition")) {
                ReadableArray tabPositionsArray = command.getArray("appendHorizontalTabPosition");
                if (tabPositionsArray != null ) {
                    int[] tabPositions = new int[tabPositionsArray.size()];
                    for (int j = 0; j < tabPositionsArray.size(); j++) {
                        tabPositions[j] = tabPositionsArray.getInt(j);
                    }
                    builder.appendHorizontalTabPosition(tabPositions);
                }
            } else if (command.hasKey("appendLogo")){
                ICommandBuilder.LogoSize logoSize = (command.hasKey("logoSize") ? getLogoSize(command.getString("logoSize")): getLogoSize("Normal"));
                builder.appendLogo(logoSize, command.getInt("appendLogo"));
            } else if (command.hasKey("appendBarcode")){
                ICommandBuilder.BarcodeSymbology barcodeSymbology =  (command.hasKey("BarcodeSymbology") ? getBarcodeSymbology(command.getString("BarcodeSymbology")): getBarcodeSymbology("Code128"));
                ICommandBuilder.BarcodeWidth barcodeWidth = (command.hasKey("BarcodeWidth") ? getBarcodeWidth(command.getString("BarcodeWidth")): getBarcodeWidth("Mode2"));
                int height = (command.hasKey("height") ? command.getInt("height"): 40);
                Boolean hri = (command.hasKey("hri") ? command.getBoolean("hri"): true);
                if(command.hasKey("absolutePosition")){
                    int position =  command.getInt("absolutePosition");
                    builder.appendBarcodeWithAbsolutePosition(command.getString("appendBarcode").getBytes(encoding), barcodeSymbology, barcodeWidth, height, hri, position);
                }else if(command.hasKey("alignment")){
                    ICommandBuilder.AlignmentPosition alignmentPosition = getAlignment(command.getString("alignment"));
                    builder.appendBarcodeWithAlignment(command.getString("appendBarcode").getBytes(encoding), barcodeSymbology, barcodeWidth, height, hri, alignmentPosition);
                }else builder.appendBarcode(command.getString("appendBarcode").getBytes(encoding), barcodeSymbology, barcodeWidth, height, hri);
            } else if (command.hasKey("appendMultiple")){
                int width = (command.hasKey("width") ? command.getInt("width"): 1);
                int height = (command.hasKey("height") ? command.getInt("height"): 1);
                builder.appendMultiple(command.getString("appendMultiple").getBytes(encoding), width, height);
            } else if (command.hasKey("enableMultiple")){
                int width = (command.hasKey("width") ? command.getInt("width"): 1);
                int height = (command.hasKey("height") ? command.getInt("height"): 1);
                Boolean enableMultiple = command.getBoolean("enableMultiple");
                if(enableMultiple) builder.appendMultiple(width, height);
                else builder.appendMultiple(1,1); // Reset to default when false sent
            } else if (command.hasKey("appendQrCode")){
                ICommandBuilder.QrCodeModel qrCodeModel =  (command.hasKey("QrCodeModel") ? getQrCodeModel(command.getString("QrCodeModel")): getQrCodeModel("No2"));
                ICommandBuilder.QrCodeLevel qrCodeLevel = (command.hasKey("QrCodeLevel") ? getQrCodeLevel(command.getString("QrCodeLevel")): getQrCodeLevel("H"));
                int cell = (command.hasKey("cell") ? command.getInt("cell"): 4);
                if(command.hasKey("absolutePosition")){
                    int position =  command.getInt("absolutePosition");
                    builder.appendQrCodeWithAbsolutePosition(command.getString("appendQrCode").getBytes(encoding), qrCodeModel, qrCodeLevel, cell, position);
                }else if(command.hasKey("alignment")){
                    ICommandBuilder.AlignmentPosition alignmentPosition = getAlignment(command.getString("alignment"));
                    builder.appendQrCodeWithAlignment(command.getString("appendQrCode").getBytes(encoding), qrCodeModel, qrCodeLevel, cell, alignmentPosition);
                }else builder.appendQrCode(command.getString("appendQrCode").getBytes(encoding), qrCodeModel, qrCodeLevel, cell);
            } else if (command.hasKey("appendBitmap")){
                ContentResolver contentResolver = context.getContentResolver();
                String _uriString = command.getString("appendBitmap");
                String uriString =  _uriString.substring(_uriString.indexOf(",")  + 1);
                boolean diffusion = (command.hasKey("diffusion")) ? command.getBoolean("diffusion") : true;
                int width = (command.hasKey("width")) ? command.getInt("width") : 576;
                boolean bothScale = (command.hasKey("bothScale")) ? command.getBoolean("bothScale") : true;
                ICommandBuilder.BitmapConverterRotation rotation = (command.hasKey("rotation")) ? getConverterRotation(command.getString("rotation")) : getConverterRotation("Normal");

                final byte[] decodedBytes = Base64.decode(uriString, Base64.DEFAULT);
                Bitmap bitmap = BitmapFactory.decodeByteArray(decodedBytes, 0, decodedBytes.length);
                if(command.hasKey("absolutePosition")){
                    int position =  command.getInt("absolutePosition");
                    builder.appendBitmapWithAbsolutePosition(bitmap, diffusion, width, bothScale, rotation, position);
                }else if(command.hasKey("alignment")){
                    ICommandBuilder.AlignmentPosition alignmentPosition = getAlignment(command.getString("alignment"));
                    builder.appendBitmapWithAlignment(bitmap, diffusion, width, bothScale, rotation, alignmentPosition);
                }else {
                  builder.appendBitmap(bitmap, diffusion, width, bothScale, rotation);
                }
            } else if (command.hasKey("appendBitmapText")){
                int fontSize = (command.hasKey("fontSize")) ? command.getInt("fontSize") : 25;
                boolean diffusion = (command.hasKey("diffusion")) ? command.getBoolean("diffusion") : true;
                int width = (command.hasKey("width")) ? command.getInt("width") : 576;
                boolean bothScale = (command.hasKey("bothScale")) ? command.getBoolean("bothScale") : true;
                String text = command.getString("appendBitmapText");
                Typeface typeface = Typeface.create(Typeface.MONOSPACE, Typeface.NORMAL);
                Bitmap bitmap = createBitmapFromText(text, fontSize, width, typeface);
                ICommandBuilder.BitmapConverterRotation rotation = (command.hasKey("rotation")) ? getConverterRotation(command.getString("rotation")) : getConverterRotation("Normal");
                if(command.hasKey("absolutePosition")){
                    int position =  command.getInt("absolutePosition");
                    builder.appendBitmapWithAbsolutePosition(bitmap, diffusion, width, bothScale, rotation, position);
                }else if(command.hasKey("alignment")){
                    ICommandBuilder.AlignmentPosition alignmentPosition = getAlignment(command.getString("alignment"));
                    builder.appendBitmapWithAlignment(bitmap, diffusion, width, bothScale, rotation, alignmentPosition);
                }else builder.appendBitmap(bitmap, diffusion, width, bothScale, rotation);
            }
        }
    };

    //ICommandBuilder Constant Functions
    private ICommandBuilder.InternationalType getInternational(String international){
        if(international.equals("UK")) return ICommandBuilder.InternationalType.UK;
        else if (international.equals("USA")) return ICommandBuilder.InternationalType.USA;
        else if (international.equals("France")) return ICommandBuilder.InternationalType.France;
        else if (international.equals("Germany")) return ICommandBuilder.InternationalType.Germany;
        else if (international.equals("Denmark")) return ICommandBuilder.InternationalType.Denmark;
        else if (international.equals("Sweden")) return ICommandBuilder.InternationalType.Sweden;
        else if (international.equals("Italy")) return ICommandBuilder.InternationalType.Italy;
        else if (international.equals("Spain")) return ICommandBuilder.InternationalType.Spain;
        else if (international.equals("Japan")) return ICommandBuilder.InternationalType.Japan;
        else if (international.equals("Norway")) return ICommandBuilder.InternationalType.Norway;
        else if (international.equals("Denmark2")) return ICommandBuilder.InternationalType.Denmark2;
        else if (international.equals("Spain2")) return ICommandBuilder.InternationalType.Spain2;
        else if (international.equals("LatinAmerica")) return ICommandBuilder.InternationalType.LatinAmerica;
        else if (international.equals("Korea")) return ICommandBuilder.InternationalType.Korea;
        else if (international.equals("Ireland")) return ICommandBuilder.InternationalType.Ireland;
        else if (international.equals("Legal")) return ICommandBuilder.InternationalType.Legal;
        else return ICommandBuilder.InternationalType.USA;
    };

    private ICommandBuilder.AlignmentPosition getAlignment(String alignment){
        if(alignment.equals("Left")) return ICommandBuilder.AlignmentPosition.Left;
        else if(alignment.equals("Center")) return ICommandBuilder.AlignmentPosition.Center;
        else if(alignment.equals("Right")) return ICommandBuilder.AlignmentPosition.Right;
        else return ICommandBuilder.AlignmentPosition.Left;
    }

    private ICommandBuilder.BarcodeSymbology getBarcodeSymbology(String barcodeSymbology){
        if(barcodeSymbology.equals("Code128")) return ICommandBuilder.BarcodeSymbology.Code128;
        else if (barcodeSymbology.equals("Code39")) return ICommandBuilder.BarcodeSymbology.Code39;
        else if (barcodeSymbology.equals("Code93")) return ICommandBuilder.BarcodeSymbology.Code93;
        else if (barcodeSymbology.equals("ITF")) return ICommandBuilder.BarcodeSymbology.ITF;
        else if (barcodeSymbology.equals("JAN8")) return ICommandBuilder.BarcodeSymbology.JAN8;
        else if (barcodeSymbology.equals("JAN13")) return ICommandBuilder.BarcodeSymbology.JAN13;
        else if (barcodeSymbology.equals("NW7")) return ICommandBuilder.BarcodeSymbology.NW7;
        else if (barcodeSymbology.equals("UPCA")) return ICommandBuilder.BarcodeSymbology.UPCA;
        else if (barcodeSymbology.equals("UPCE")) return ICommandBuilder.BarcodeSymbology.UPCE;
        else return ICommandBuilder.BarcodeSymbology.Code128;
    }
    private ICommandBuilder.BarcodeWidth getBarcodeWidth (String barcodeWidth){
        if(barcodeWidth.equals("Mode1")) return ICommandBuilder.BarcodeWidth.Mode1;
        if(barcodeWidth.equals("Mode2")) return ICommandBuilder.BarcodeWidth.Mode2;
        if(barcodeWidth.equals("Mode3")) return ICommandBuilder.BarcodeWidth.Mode3;
        if(barcodeWidth.equals("Mode4")) return ICommandBuilder.BarcodeWidth.Mode4;
        if(barcodeWidth.equals("Mode5")) return ICommandBuilder.BarcodeWidth.Mode5;
        if(barcodeWidth.equals("Mode6")) return ICommandBuilder.BarcodeWidth.Mode6;
        if(barcodeWidth.equals("Mode7")) return ICommandBuilder.BarcodeWidth.Mode7;
        if(barcodeWidth.equals("Mode8")) return ICommandBuilder.BarcodeWidth.Mode8;
        if(barcodeWidth.equals("Mode9")) return ICommandBuilder.BarcodeWidth.Mode9;
        return ICommandBuilder.BarcodeWidth.Mode2;
    }
    private ICommandBuilder.FontStyleType getFontStyle(String fontStyle){
        if(fontStyle.equals("A")) return ICommandBuilder.FontStyleType.A;
        if(fontStyle.equals("B")) return ICommandBuilder.FontStyleType.B;
        return ICommandBuilder.FontStyleType.A;
    }
    private ICommandBuilder.LogoSize getLogoSize(String logoSize){
        if(logoSize.equals("Normal")) return ICommandBuilder.LogoSize.Normal;
        else if(logoSize.equals("DoubleWidth")) return ICommandBuilder.LogoSize.DoubleWidth;
        else if(logoSize.equals("DoubleHeight")) return ICommandBuilder.LogoSize.DoubleHeight;
        else if(logoSize.equals("DoubleWidthDoubleHeight")) return ICommandBuilder.LogoSize.DoubleWidthDoubleHeight;
        else return ICommandBuilder.LogoSize.Normal;
    }

    private ICommandBuilder.CutPaperAction getCutPaperAction(String cutPaperAction){
        if(cutPaperAction.equals("FullCut")) return CutPaperAction.FullCut;
        else if(cutPaperAction.equals("FullCutWithFeed")) return CutPaperAction.FullCutWithFeed;
        else if(cutPaperAction.equals("PartialCut")) return CutPaperAction.PartialCut;
        else if(cutPaperAction.equals("PartialCutWithFeed")) return CutPaperAction.PartialCutWithFeed;
        else return CutPaperAction.PartialCutWithFeed;
    }
    private ICommandBuilder.PeripheralChannel getPeripheralChannel(int peripheralChannel){
        if(peripheralChannel == 1) return ICommandBuilder.PeripheralChannel.No1;
        else if(peripheralChannel == 2) return ICommandBuilder.PeripheralChannel.No2;
        else return ICommandBuilder.PeripheralChannel.No1;
    }
    private ICommandBuilder.QrCodeModel getQrCodeModel (String qrCodeModel){
        if(qrCodeModel.equals("No1")) return ICommandBuilder.QrCodeModel.No1;
        else if(qrCodeModel.equals("No2")) return ICommandBuilder.QrCodeModel.No2;
        else return ICommandBuilder.QrCodeModel.No1;
    }
    private ICommandBuilder.QrCodeLevel getQrCodeLevel (String qrCodeLevel){
        if(qrCodeLevel.equals("H")) return ICommandBuilder.QrCodeLevel.H;
        else if(qrCodeLevel.equals("L")) return ICommandBuilder.QrCodeLevel.L;
        else if(qrCodeLevel.equals("M")) return ICommandBuilder.QrCodeLevel.M;
        else if(qrCodeLevel.equals("Q")) return ICommandBuilder.QrCodeLevel.Q;
        else return ICommandBuilder.QrCodeLevel.H;
    }
    private ICommandBuilder.BitmapConverterRotation getConverterRotation (String converterRotation){
        if(converterRotation.equals("Normal")) return ICommandBuilder.BitmapConverterRotation.Normal;
        else if(converterRotation.equals("Left90")) return ICommandBuilder.BitmapConverterRotation.Left90;
        else if(converterRotation.equals("Right90")) return ICommandBuilder.BitmapConverterRotation.Right90;
        else if(converterRotation.equals("Rotate180")) return ICommandBuilder.BitmapConverterRotation.Rotate180;
        else return ICommandBuilder.BitmapConverterRotation.Normal;
    }
    private ICommandBuilder.BlackMarkType getBlackMarkType(String blackMarkType){
        if(blackMarkType.equals("Valid")) return ICommandBuilder.BlackMarkType.Valid;
        else if(blackMarkType.equals("Invalid")) return ICommandBuilder.BlackMarkType.Invalid;
        else if(blackMarkType.equals("ValidWithDetection")) return ICommandBuilder.BlackMarkType.ValidWithDetection;
        else return ICommandBuilder.BlackMarkType.Valid;
    }
    private ICommandBuilder.CodePageType getCodePageType(String codePageType){
        if (codePageType.equals("CP437")) return CodePageType.CP437;
        else if (codePageType.equals("CP737")) return CodePageType.CP737;
        else if (codePageType.equals("CP772")) return CodePageType.CP772;
        else if (codePageType.equals("CP774")) return CodePageType.CP774;
        else if (codePageType.equals("CP851")) return CodePageType.CP851;
        else if (codePageType.equals("CP852")) return CodePageType.CP852;
        else if (codePageType.equals("CP855")) return CodePageType.CP855;
        else if (codePageType.equals("CP857")) return CodePageType.CP857;
        else if (codePageType.equals("CP858")) return CodePageType.CP858;
        else if (codePageType.equals("CP860")) return CodePageType.CP860;
        else if (codePageType.equals("CP861")) return CodePageType.CP861;
        else if (codePageType.equals("CP862")) return CodePageType.CP862;
        else if (codePageType.equals("CP863")) return CodePageType.CP863;
        else if (codePageType.equals("CP864")) return CodePageType.CP864;
        else if (codePageType.equals("CP865")) return CodePageType.CP866;
        else if (codePageType.equals("CP869")) return CodePageType.CP869;
        else if (codePageType.equals("CP874")) return CodePageType.CP874;
        else if (codePageType.equals("CP928")) return CodePageType.CP928;
        else if (codePageType.equals("CP932")) return CodePageType.CP932;
        else if (codePageType.equals("CP999")) return CodePageType.CP999;
        else if (codePageType.equals("CP1001")) return CodePageType.CP1001;
        else if (codePageType.equals("CP1250")) return CodePageType.CP1250;
        else if (codePageType.equals("CP1251")) return CodePageType.CP1251;
        else if (codePageType.equals("CP1252")) return CodePageType.CP1252;
        else if (codePageType.equals("CP2001")) return CodePageType.CP2001;
        else if (codePageType.equals("CP3001")) return CodePageType.CP3001;
        else if (codePageType.equals("CP3002")) return CodePageType.CP3002;
        else if (codePageType.equals("CP3011")) return CodePageType.CP3011;
        else if (codePageType.equals("CP3012")) return CodePageType.CP3012;
        else if (codePageType.equals("CP3021")) return CodePageType.CP3021;
        else if (codePageType.equals("CP3041")) return CodePageType.CP3041;
        else if (codePageType.equals("CP3840")) return CodePageType.CP3840;
        else if (codePageType.equals("CP3841")) return CodePageType.CP3841;
        else if (codePageType.equals("CP3843")) return CodePageType.CP3843;
        else if (codePageType.equals("CP3845")) return CodePageType.CP3845;
        else if (codePageType.equals("CP3846")) return CodePageType.CP3846;
        else if (codePageType.equals("CP3847")) return CodePageType.CP3847;
        else if (codePageType.equals("CP3848")) return CodePageType.CP3848;
        else if (codePageType.equals("UTF8")) return CodePageType.UTF8;
        else if (codePageType.equals("Blank")) return CodePageType.Blank;
        else return CodePageType.CP998;
    };

    //Helper functions

    private Charset getEncoding(String encoding){

        if (encoding.equals("US-ASCII")) return Charset.forName("US-ASCII"); //English
        else if (encoding.equals("Windows-1252")){
            try {
                return Charset.forName("Windows-1252"); //French, German, Portuguese, Spanish
            }
            catch (UnsupportedCharsetException e) { //not supported using UTF-8 Instead
                return Charset.forName("UTF-8");
            }
        }
        else if (encoding.equals("Shift-JIS")) {
            try {
                return Charset.forName("Shift-JIS"); //Japanese
            }
            catch (UnsupportedCharsetException e) { //not supported using UTF-8 Instead
                return Charset.forName("UTF-8");
            }
        }
        else if (encoding.equals("Windows-1251")){
            try {
                return Charset.forName("Windows-1251"); //Russian
            }
            catch (UnsupportedCharsetException e) { //not supported using UTF-8 Instead
                return Charset.forName("UTF-8");
            }
        }
        else if (encoding.equals("GB2312")) {
            try {
                return Charset.forName("GB2312"); // Simplified Chinese
            }
            catch (UnsupportedCharsetException e) { //not supported using UTF-8 Instead
                return Charset.forName("UTF-8");
            }
        }
        else if (encoding.equals("Big5")) {
            try {
                return Charset.forName("Big5"); // Traditional Chinese
            }
            catch (UnsupportedCharsetException e) { //not supported using UTF-8 Instead
                return Charset.forName("UTF-8");
            }
        }
        else if (encoding.equals("UTF-8")) return Charset.forName("UTF-8"); // UTF-8
        else return Charset.forName("US-ASCII");
    };

    private void sendEvent(String dataType, String info) {
        ReactContext reactContext = getReactApplicationContext();
        String eventName = "starPrntData";
        WritableMap params = new WritableNativeMap();
        params.putString("dataType", dataType);
        if (info != null) params.putString("data", info);
        reactContext
                .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit(eventName, params);
    };

    
    private Bitmap createBitmapFromText(String printText, int textSize, int printWidth, Typeface typeface) {
        Paint paint = new Paint();
        Bitmap bitmap;
        Canvas canvas;

        paint.setTextSize(textSize);
        paint.setTypeface(typeface);
        paint.getTextBounds(printText, 0, printText.length(), new Rect());

        TextPaint textPaint = new TextPaint(paint);
        android.text.StaticLayout staticLayout = new StaticLayout(printText, textPaint, printWidth, Layout.Alignment.ALIGN_NORMAL, 1, 0, false);

        // Create bitmap
        bitmap = Bitmap.createBitmap(staticLayout.getWidth(), staticLayout.getHeight(), Bitmap.Config.ARGB_8888);

        // Create canvas
        canvas = new Canvas(bitmap);
        canvas.drawColor(Color.WHITE);
        canvas.translate(0, 0);
        staticLayout.draw(canvas);

        return bitmap;
    }


    private StarIoExtManagerListener starIoExtManagerListener = new StarIoExtManagerListener() {
        @Override
        public void onPrinterImpossible() {
            sendEvent("printerImpossible", null);
        }

        @Override
        public void onPrinterOnline() {
            sendEvent("printerOnline", null);
        }

        @Override
        public void onPrinterOffline() {
            sendEvent("printerOffline", null);
        }

        @Override
        public void onPrinterPaperReady() {
            sendEvent("printerPaperReady", null);
        }

        @Override
        public void onPrinterPaperNearEmpty() {
            sendEvent("printerPaperNearEmpty", null);
        }

        @Override
        public void onPrinterPaperEmpty() {
            sendEvent("printerPaperEmpty", null);
        }

        @Override
        public void onPrinterCoverOpen() {
            sendEvent("printerCoverOpen", null);
        }

        @Override
        public void onPrinterCoverClose() {
            sendEvent("printerCoverClose", null);
        }

        //Cash Drawer events
        @Override
        public void onCashDrawerOpen() {
            sendEvent("cashDrawerOpen", null);
        }

        @Override
        public void onCashDrawerClose() {
            sendEvent("cashDrawerClose", null);
        }

        @Override
        public void onBarcodeReaderImpossible() {
            sendEvent("barcodeReaderImpossible", null);
        }

        @Override
        public void onBarcodeReaderConnect() {
            sendEvent("barcodeReaderConnect", null);
        }

        @Override
        public void onBarcodeReaderDisconnect() {
            sendEvent("barcodeReaderDisconnect", null);
        }

        @Override
        public void onBarcodeDataReceive(byte[] data) {
            sendEvent("barcodeDataReceive", new String(data));
        }

    };



}