package net.infoxication.reactstarprnt;

import android.util.SparseArray;

import static com.starmicronics.starioextension.StarIoExt.Emulation;
import static com.starmicronics.starioextension.StarIoExt.LedModel;

/**
 * This class expresses printer settings that should use on each model
 * and which printer function each model can use.
 */
@SuppressWarnings("WeakerAccess")
public class ModelCapability {

  public static final int NONE                       = -1;
  public static final int MPOP                       = 0;
  public static final int FVP10                      = 1;
  public static final int TSP100                     = 2;
  public static final int TSP650II                   = 3;
  public static final int TSP700II                   = 4;
  public static final int TSP800II                   = 5;
  public static final int SP700                      = 6;
  public static final int SM_S210I                   = 7;
  public static final int SM_S220I                   = 8;
  public static final int SM_S230I                   = 9;
  public static final int SM_T300I_T300              = 10;
  public static final int SM_T400I                   = 11;
  public static final int SM_L200                    = 12;
  public static final int BSC10                      = 13;
  public static final int SM_S210I_StarPRNT          = 14;
  public static final int SM_S220I_StarPRNT          = 15;
  public static final int SM_S230I_StarPRNT          = 16;
  public static final int SM_T300I_T300_StarPRNT     = 17;
  public static final int SM_T400I_StarPRNT          = 18;

  // V5.3.0
  public static final int SM_L300                    = 19;

  // V5.6.0
  public static final int MC_PRINT2                  = 20;
  public static final int MC_PRINT3                  = 21;

  // V5.11.0
  public static final int TUP500                     = 22;

  // V5.12.0
  public static final int SK1_211_221_V211           = 23;
  public static final int SK1_211_221_V211_Presenter = 24;
  public static final int SK1_311_321_V311           = 25;
  public static final int SK1_311_V311_Presenter     = 26;

  static class ModelInfo {
    String    modelTitle;
    String[]  modelNameArray;
    Emulation emulation;
    String    defaultPortSettings;
    int       defaultPaperSize;
    boolean   canSetDrawerOpenStatus;
    boolean   canPrintTextReceiptSample;
    boolean   canPrintUtf8EncodedText;
    boolean   canPrintRasterReceiptSample;
    boolean   canPrintCjk;
    boolean   canUseBlackMark;
    boolean   canUseBlackMarkDetection;
    boolean   canUsePageMode;
    boolean   canUseCashDrawer;
    boolean   canUseBarcodeReader;
    boolean   canUseCustomerDisplay;
    boolean   canUsePresenter;
    boolean   canUseLed;
    LedModel  ledModel;
    boolean   canUseBlinkLed;
    boolean   canUsePaperPresentStatus;
    boolean   canUseAllReceipt;
    boolean   canGetProductSerialNumber;
    int       settableUsbSerialNumberLength;
    boolean   isUsbSerialNumberEnabledByDefault;
    boolean   canUseMelodySpeaker;
    int       defaultSoundNumber;
    int       defaultVolume;
    int       volumeMax;
    int       volumeMin;

    public ModelInfo(String    modelTitle,
                     String[]  modelNameArray,
                     Emulation emulation,
                     String    defaultPortSettings,
                     int       defaultPaperSize,
                     boolean   canSetDrawerOpenStatus,
                     boolean   canPrintTextReceiptSample,
                     boolean   canPrintUtf8EncodedText,
                     boolean   canPrintRasterReceiptSample,
                     boolean   canPrintCjk,
                     boolean   canUseBlackMark,
                     boolean   canUseBlackMarkDetection,
                     boolean   canUsePageMode,
                     boolean   canUseCashDrawer,
                     boolean   canUseBarcodeReader,
                     boolean   canUseCustomerDisplay,
                     boolean   canUsePresenter,
                     boolean   canUseLed,
                     LedModel  ledModel,
                     boolean   canUseBlinkLed,
                     boolean   canUsePaperPresentStatus,
                     boolean   canUseAllReceipt,
                     boolean   canGetProductSerialNumber,
                     int       settableUsbSerialNumberLength,
                     boolean   isUsbSerialNumberEnabledByDefault,
                     boolean   canUseMelodySpeaker,
                     int       defaultSoundNumber,
                     int       defaultVolume,
                     int       volumeMax,
                     int       volumeMin) {
      this.modelTitle                        = modelTitle;
      this.modelNameArray                    = modelNameArray;
      this.emulation                         = emulation;
      this.defaultPortSettings               = defaultPortSettings;
      this.defaultPaperSize                  = defaultPaperSize;
      this.canSetDrawerOpenStatus            = canSetDrawerOpenStatus;
      this.canPrintTextReceiptSample         = canPrintTextReceiptSample;
      this.canPrintUtf8EncodedText           = canPrintUtf8EncodedText;
      this.canPrintRasterReceiptSample       = canPrintRasterReceiptSample;
      this.canPrintCjk                       = canPrintCjk;
      this.canUseBlackMark                   = canUseBlackMark;
      this.canUseBlackMarkDetection          = canUseBlackMarkDetection;
      this.canUsePageMode                    = canUsePageMode;
      this.canUseCashDrawer                  = canUseCashDrawer;
      this.canUseBarcodeReader               = canUseBarcodeReader;
      this.canUseCustomerDisplay             = canUseCustomerDisplay;
      this.canUsePresenter                   = canUsePresenter;
      this.canUseLed                         = canUseLed;
      this.ledModel                          = ledModel;
      this.canUseBlinkLed                    = canUseBlinkLed;
      this.canUsePaperPresentStatus          = canUsePaperPresentStatus;
      this.canUseAllReceipt                  = canUseAllReceipt;
      this.canGetProductSerialNumber         = canGetProductSerialNumber;
      this.settableUsbSerialNumberLength     = settableUsbSerialNumberLength;
      this.isUsbSerialNumberEnabledByDefault = isUsbSerialNumberEnabledByDefault;
      this.canUseMelodySpeaker               = canUseMelodySpeaker;
      this.defaultSoundNumber                = defaultSoundNumber;
      this.defaultVolume                     = defaultVolume;
      this.volumeMax                         = volumeMax;
      this.volumeMin                         = volumeMin;
    }
  }

  public static final SparseArray<ModelInfo> mModelCapabilityMap = new SparseArray<ModelInfo>() {
    {
      put(MC_PRINT2, new ModelInfo(
              "mC-Print2",                                    // modelTitle
              new String[]{                                   // modelNameArray
                      "MCP20 (STR-001)",                      // <-LAN interface
                      "MCP21 (STR-001)",
                      "mC-Print2-",                           // <-Bluetooth interface
                      "mC-Print2"},                           // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              true,                                           // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              true,                                           // canUseCashDrawer
              true,                                           // canUseBarcodeReader
              true,                                           // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              true,                                           // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(MC_PRINT3, new ModelInfo(
              "mC-Print3",                                    // modelTitle
              new String[]{                                   // modelNameArray
                      "MCP31 (STR-001)",                      // <-LAN interface
                      "mC-Print3-",                           // <-Bluetooth interface
                      "mC-Print3"},                           // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              true,                                           // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              true,                                           // canUseCashDrawer
              true,                                           // canUseBarcodeReader
              true,                                           // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              true,                                           // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              true,                                           // canUseMelodySpeaker
              0,                                              // defaultSoundNumber
              12,                                             // defaultVolume
              15,                                             // volumeMax
              0                                               // volumeMin
      ));

      put(MPOP, new ModelInfo(
              "mPOP",                                         // modelTitle
              new String[]{                                   // modelNameArray
                      "STAR mPOP-",                           // <-Bluetooth interface
                      "mPOP"},                                // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              true,                                           // canUseCashDrawer
              true,                                           // canUseBarcodeReader
              true,                                           // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              true,                                           // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(FVP10, new ModelInfo(
              "FVP10",                                        // modelTitle
              new String[]{                                   // modelNameArray
                      "FVP10 (STR_T-001)",                    // <-LAN interface
                      "Star FVP10"},                          // <-USB interface
              Emulation.StarLine,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              true,                                           // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              true,                                           // canUseMelodySpeaker
              1,                                              // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(TSP100, new ModelInfo(
              "TSP100",                                       // modelTitle
              new String[]{                                   // modelNameArray
                      "TSP113", "TSP143",                     // <-LAN model
                      "TSP100-",                              // <-Bluetooth model
                      "Star TSP113", "Star TSP143"},          // <-USB model
              Emulation.StarGraphic,                          // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              true,                                           // canSetDrawerOpenStatus
              false,                                          // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              false,                                          // canUsePageMode
              true,                                           // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              true,                                           // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              true,                                           // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(TSP650II, new ModelInfo(
              "TSP650II",                                     // modelTitle
              new String[]{                                   // modelNameArray
                      "TSP654II (STR_T-001)",                 // Only LAN model->
                      "TSP654 (STR_T-001)",
                      "TSP651 (STR_T-001)"},
              Emulation.StarLine,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              true,                                           // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              true,                                           // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(TSP700II, new ModelInfo(
              "TSP700II",                                     // modelTitle
              new String[]{                                   // modelNameArray
                      "TSP743II (STR_T-001)",
                      "TSP743 (STR_T-001)"},
              Emulation.StarLine,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              false,                                          // canUsePageMode
              true,                                           // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(TSP800II, new ModelInfo(
              "TSP800II",                                     // modelTitle
              new String[]{                                   // modelNameArray
                      "TSP847II (STR_T-001)",
                      "TSP847 (STR_T-001)"},                  // <-Only LAN model
              Emulation.StarLine,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_FOUR_INCH,    // Default paper size
              true,                                           // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              false,                                          // canUsePageMode
              true,                                           // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(TUP500, new ModelInfo(
              "TUP500",                                       // modelTitle
              new String[]{                                   // modelNameArray
                      "TUP592 (STR_T-001)",
                      "TUP542 (STR_T-001)"},
              Emulation.StarLine,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              false,                                          // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              true,                                           // canUsePresenter
              true,                                           // canUseLed
              LedModel.Star,                                  // ledModel
              true,                                           // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              1,                                              // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SP700, new ModelInfo(
              "SP700",                                            // modelTitle
              new String[]{                                       // modelNameArray
                      "SP712 (STR-001)",                          // Only LAN model
                      "SP717 (STR-001)",
                      "SP742 (STR-001)",
                      "SP747 (STR-001)"},
              Emulation.StarDotImpact,                            // Emulation
              "",                                                 // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_DOT_THREE_INCH,   // Default paper size
              true,                                               // canSetDrawerOpenStatus
              true,                                               // canPrintTextReceiptSample
              true,                                               // canPrintUtf8EncodedText
              false,                                              // canPrintRasterReceiptSample
              false,                                              // canPrintCjk
              true,                                               // canUseBlackMark
              true,                                               // canUseBlackMarkDetection
              false,                                              // canUsePageMode
              true,                                               // canUseCashDrawer
              false,                                              // canUseBarcodeReader
              false,                                              // canUseCustomerDisplay
              false,                                              // canUsePresenter
              false,                                              // canUseLed
              LedModel.None,                                      // ledModel
              false,                                              // canUseBlinkLed
              false,                                              // canUsePaperPresentStatus
              false,                                              // canUseAllReceipt
              false,                                              // canGetProductSerialNumber
              8,                                                  // settableUsbSerialNumberLength
              false,                                              // isUsbSerialNumberEnabledByDefault
              false,                                              // canUseMelodySpeaker
              -1,                                                 // defaultSoundNumber
              -1,                                                 // defaultVolume
              -1,                                                 // volumeMax
              -1                                                  // volumeMin
      ));

      put(SM_S210I, new ModelInfo(
              "SM-S210i",                                     // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.EscPosMobile,                         // Emulation
              "mini",                                         // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_S220I, new ModelInfo(
              "SM-S220i",                                     // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.EscPosMobile,                         // Emulation
              "mini",                                         // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_S230I, new ModelInfo(
              "SM-S230i",                                     // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.EscPosMobile,                         // Emulation
              "mini",                                         // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_T300I_T300, new ModelInfo(
              "SM-T300i/T300",                                // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.EscPosMobile,                         // Emulation
              "mini",                                         // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_T400I, new ModelInfo(
              "SM-T400i",                                     // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.EscPosMobile,                         // Emulation
              "mini",                                         // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_FOUR_INCH,    // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_L200, new ModelInfo(
              "SM-L200",                                      // modelTitle
              new String[]{                                   // modelNameArray
                      "STAR L200-",
                      "STAR L204-"},                          // <-Bluetooth interface
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_L300, new ModelInfo(
              "SM-L300",                                      // modelTitle
              new String[]{                                   // modelNameArray
                      "STAR L300-",
                      "STAR L304-"},                          // <-Bluetooth interface
              Emulation.StarPRNTL,                            // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(BSC10, new ModelInfo(
              "BSC10",                                                // modelTitle
              new String[]{                                           // modelNameArray
                      "BSC10",                                        // <-LAN model
                      "Star BSC10"},                                  // <-USB model
              Emulation.EscPos,                                       // Emulation
              "escpos",                                               // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_ESCPOS_THREE_INCH,    // Default paper size
              true,                                                   // canSetDrawerOpenStatus
              true,                                                   // canPrintTextReceiptSample
              false,                                                  // canPrintUtf8EncodedText
              true,                                                   // canPrintRasterReceiptSample
              false,                                                  // canPrintCjk
              false,                                                  // canUseBlackMark
              false,                                                  // canUseBlackMarkDetection
              true,                                                   // canUsePageMode
              true,                                                   // canUseCashDrawer
              false,                                                  // canUseBarcodeReader
              false,                                                  // canUseCustomerDisplay
              false,                                                  // canUsePresenter
              false,                                                  // canUseLed
              LedModel.None,                                          // ledModel
              false,                                                  // canUseBlinkLed
              false,                                                  // canUsePaperPresentStatus
              true,                                                   // canUseAllReceipt
              false,                                                  // canGetProductSerialNumber
              8,                                                      // settableUsbSerialNumberLength
              false,                                                  // isUsbSerialNumberEnabledByDefault
              false,                                                  // canUseMelodySpeaker
              -1,                                                     // defaultSoundNumber
              -1,                                                     // defaultVolume
              -1,                                                     // volumeMax
              -1                                                      // volumeMin
      ));

      put(SM_S210I_StarPRNT, new ModelInfo(
              "SM-S210i StarPRNT",                            // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_S220I_StarPRNT, new ModelInfo(
              "SM-S220i StarPRNT",                            // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_S230I_StarPRNT, new ModelInfo(
              "SM-S230i StarPRNT",                            // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_TWO_INCH,     // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              false,                                          // canUseBlackMark
              false,                                          // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              8,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_T300I_T300_StarPRNT, new ModelInfo(
              "SM-T300i StarPRNT",                            // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SM_T400I_StarPRNT, new ModelInfo(
              "SM-T400i StarPRNT",                            // modelTitle
              new String[]{},                                 // modelNameArray
              Emulation.StarPRNT,                             // Emulation
              "Portable",                                     // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_FOUR_INCH,    // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              false,                                          // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              false,                                          // canUseLed
              LedModel.None,                                  // ledModel
              false,                                          // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              0,                                              // settableUsbSerialNumberLength
              false,                                          // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SK1_211_221_V211, new ModelInfo(
              "SK1-211/221/V211",                             // modelTitle
              new String[]{                                   // modelNameArray
                      "SK1-211_221"},                         // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_SK1_TWO_INCH, // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              true,                                           // canUseLed
              LedModel.SK,                                    // ledModel
              false,                                          // canUseBlinkLed
              true,                                           // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SK1_211_221_V211_Presenter, new ModelInfo(
              "SK1-211/221/V211 Presenter",                   // modelTitle
              new String[]{                                   // modelNameArray
                      "SK1-211_221 Presenter"},               // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_SK1_TWO_INCH, // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              true,                                           // canUsePresenter
              true,                                           // canUseLed
              LedModel.SK,                                    // ledModel
              true,                                           // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SK1_311_321_V311, new ModelInfo(
              "SK1-311/321/V311",                             // modelTitle
              new String[]{                                   // modelNameArray
                      "SK1-311_321"},                         // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              false,                                          // canUsePresenter
              true,                                           // canUseLed
              LedModel.SK,                                    // ledModel
              false,                                          // canUseBlinkLed
              true,                                           // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));

      put(SK1_311_V311_Presenter, new ModelInfo(
              "SK1-311/V311 Presenter",                       // modelTitle
              new String[]{                                   // modelNameArray
                      "SK1-311 Presenter"},                   // <-USB interface
              Emulation.StarPRNT,                             // Emulation
              "",                                             // Default portSettings
              PrinterSettingConstant.PAPER_SIZE_THREE_INCH,   // Default paper size
              false,                                          // canSetDrawerOpenStatus
              true,                                           // canPrintTextReceiptSample
              true,                                           // canPrintUtf8EncodedText
              true,                                           // canPrintRasterReceiptSample
              false,                                          // canPrintCjk
              true,                                           // canUseBlackMark
              true,                                           // canUseBlackMarkDetection
              true,                                           // canUsePageMode
              false,                                          // canUseCashDrawer
              false,                                          // canUseBarcodeReader
              false,                                          // canUseCustomerDisplay
              true,                                           // canUsePresenter
              true,                                           // canUseLed
              LedModel.SK,                                    // ledModel
              true,                                           // canUseBlinkLed
              false,                                          // canUsePaperPresentStatus
              true,                                           // canUseAllReceipt
              false,                                          // canGetProductSerialNumber
              16,                                             // settableUsbSerialNumberLength
              true,                                           // isUsbSerialNumberEnabledByDefault
              false,                                          // canUseMelodySpeaker
              -1,                                             // defaultSoundNumber
              -1,                                             // defaultVolume
              -1,                                             // volumeMax
              -1                                              // volumeMin
      ));
    }
  };

  public static String getModelTitle(int model) {
    return mModelCapabilityMap.get(model).modelTitle;
  }

  public static Emulation getEmulation(int model) {
    return mModelCapabilityMap.get(model).emulation;
  }

  public static String getPortSettings(int model) {
    return mModelCapabilityMap.get(model).defaultPortSettings;
  }

  public static boolean canSetDrawerOpenStatus(int model) {
    return mModelCapabilityMap.get(model).canSetDrawerOpenStatus;
  }

  public static boolean canPrintTextReceiptSample(int model) {
    return mModelCapabilityMap.get(model).canPrintTextReceiptSample;
  }

  public static boolean canPrintUtf8EncodedText(int model) {
    return mModelCapabilityMap.get(model).canPrintUtf8EncodedText;
  }

  public static boolean canPrintRasterReceiptSample(int model) {
    return mModelCapabilityMap.get(model).canPrintRasterReceiptSample;
  }

  public static boolean canPrintCjk(int model) {
    return mModelCapabilityMap.get(model).canPrintCjk;
  }

  public static boolean canUseBlackMark(int model) {
    return mModelCapabilityMap.get(model).canUseBlackMark;
  }

  public static boolean canUseBlackMarkDetection(int model) {
    return mModelCapabilityMap.get(model).canUseBlackMarkDetection;
  }

  public static boolean canUsePageMode(int model) {
    return mModelCapabilityMap.get(model).canUsePageMode;
  }

  public static boolean canUseCashDrawer(int model) {
    return mModelCapabilityMap.get(model).canUseCashDrawer;
  }

  public static boolean canUseBarcodeReader(int model) {
    return mModelCapabilityMap.get(model).canUseBarcodeReader;
  }

  public static boolean canUseCustomerDisplay(int model, String modelName) {
    boolean canUse = mModelCapabilityMap.get(model).canUseCustomerDisplay;

    if (model == TSP100) {
      canUse = modelName.equals(mModelCapabilityMap.get(TSP100).modelTitle) ||    // If setting a printer manually, the customer display menu is always valid.
              modelName.equals("Star TSP143IIIU");                               // Support TSP100IIIU.
      // Not support TSP100LAN, TSP100U, TSP100GT, TSP100IIU, TSP100IIILAN, TSP100IIIW and TSP100IIIBI.
    }

    return canUse;
  }

  public static boolean canUsePresenter(int model) {
    return mModelCapabilityMap.get(model).canUsePresenter;
  }

  public static boolean canUseLed(int model) {
    return mModelCapabilityMap.get(model).canUseLed;
  }

  public static LedModel getLedModel(int model) {
    return mModelCapabilityMap.get(model).ledModel;
  }

  public static boolean canUseBlinkLed(int model) {
    return mModelCapabilityMap.get(model).canUseBlinkLed;
  }

  public static boolean canUsePaperPresentStatus(int model) {
    return mModelCapabilityMap.get(model).canUsePaperPresentStatus;
  }

  public static boolean canUseAllReceipt(int model) {
    return mModelCapabilityMap.get(model).canUseAllReceipt;
  }

  public static boolean canGetProductSerialNumber(int model, String modelName, boolean isBluetoothInterface) {
    boolean canGet = mModelCapabilityMap.get(model).canGetProductSerialNumber;

    if (model == TSP100) {
      canGet = modelName.equals(mModelCapabilityMap.get(TSP100).modelTitle) ||    // If setting a printer manually, the serial number menu is always valid.
              modelName.equals("TSP143IIILAN (STR_T-001)") ||                    // Support TSP100IIILAN.
              modelName.equals("TSP143IIIW (STR_T-001)") ||                      // Support TSP100IIIW.
              isBluetoothInterface ||                                            // Support TSP100IIIBI.
              modelName.equals("Star TSP143IIIU");                               // Support TSP100IIIU.
      // Not support TSP100LAN, TSP100U, TSP100GT and TSP100IIU.
    }

    return canGet;
  }

  public static int settableUsbSerialNumberLength(int model, String modelName, boolean isUsbInterface) {
    int length = mModelCapabilityMap.get(model).settableUsbSerialNumberLength;

    if (model == TSP100) {
      if (!isUsbInterface) {
        return 0;
      }

      if (modelName.equals(mModelCapabilityMap.get(TSP100).modelTitle) || // If setting a printer manually, the max length is set to 16.
              modelName.equals("Star TSP143IIIU")) {                          // TSP100IIIU supports 16digits USB-ID.
        length = 16;
      }
      else {                                                              // TSP100U, TSP100GT and TSP100IIU support 8digits USB-ID.
        length = 8;
      }
    }

    if (model == BSC10 && !isUsbInterface) {                                // It is useless to set a USB serial number to BSC10LAN.
      length = 0;
    }

    return length;
  }

  public static boolean isUsbSerialNumberEnabledByDefault(int model) {
    return mModelCapabilityMap.get(model).isUsbSerialNumberEnabledByDefault;
  }

  public static boolean canUseMelodySpeaker(int model) {
    return mModelCapabilityMap.get(model).canUseMelodySpeaker;
  }

  public static int getDefaultSoundNumber(int model) {
    return mModelCapabilityMap.get(model).defaultSoundNumber;
  }

  public static int getDefaultPaperSize(int model) {
    return mModelCapabilityMap.get(model).defaultPaperSize;
  }

  public static int getDefaultVolume(int model) {
    return mModelCapabilityMap.get(model).defaultVolume;
  }

  public static int getVolumeMax(int model) {
    return mModelCapabilityMap.get(model).volumeMax;
  }

  public static int getVolumeMin(int model) {
    return mModelCapabilityMap.get(model).volumeMin;
  }

  /**
   * Get a model index from model name string that can be got by
   * PortInfo.getModelName() or PortInfo.getPortName();
   */
  public static int getModel(String modelNameSrc) {
    // Perfect match
    for (int i = 0; i < mModelCapabilityMap.size(); i++) {
      for (String modelName : mModelCapabilityMap.valueAt(i).modelNameArray) {
        if (modelNameSrc.equals(modelName)) {
          return mModelCapabilityMap.keyAt(i);
        }
      }
    }

    // Partial match from the head
    for (int i = 0; i < mModelCapabilityMap.size(); i++) {
      for (String modelName : mModelCapabilityMap.valueAt(i).modelNameArray) {
        if (modelNameSrc.startsWith(modelName)) {
          return mModelCapabilityMap.keyAt(i);
        }
      }
    }

    return NONE;
  }
}

