//
//  ISCBBuilder.h
//  StarIO_Extension
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, SCBFactoryEmulation) {
    SCBFactoryEmulationStar   __attribute__((unavailable("Not available. Please change to StarIoExtEmulationStar...."))),     // Star Emulation
    SCBFactoryEmulationEscPos __attribute__((unavailable("Not available. Please change to StarIoExtEmulationEscPos.")))       // ESC/POS Emulation
} __attribute__((unavailable("Not available. Please change to StarIoExtEmulation.")));

#pragma mark - Initialization

typedef NS_ENUM(NSUInteger, SCBInitializationType) {
    SCBInitializationTypeCommand
//  SCBInitializationTypeCommand,
//  SCBInitializationTypeReset,
//  SCBInitializationTypeResetWithPrint
};

#pragma mark - FontStyle

typedef NS_ENUM(NSUInteger, SCBFontStyleType) {
    SCBFontStyleTypeA,
    SCBFontStyleTypeB
};

#pragma mark - CodePage

typedef NS_ENUM(NSUInteger, SCBCodePageType) {
    SCBCodePageTypeCP437,
    SCBCodePageTypeCP737,
    SCBCodePageTypeCP772,
    SCBCodePageTypeCP774,
    SCBCodePageTypeCP851,
    SCBCodePageTypeCP852,
    SCBCodePageTypeCP855,
    SCBCodePageTypeCP857,
    SCBCodePageTypeCP858,
    SCBCodePageTypeCP860,
    SCBCodePageTypeCP861,
    SCBCodePageTypeCP862,
    SCBCodePageTypeCP863,
    SCBCodePageTypeCP864,
    SCBCodePageTypeCP865,
    SCBCodePageTypeCP866,
    SCBCodePageTypeCP869,
    SCBCodePageTypeCP874,
    SCBCodePageTypeCP928,
    SCBCodePageTypeCP932,
    SCBCodePageTypeCP998,
    SCBCodePageTypeCP999,
    SCBCodePageTypeCP1001,
    SCBCodePageTypeCP1250,
    SCBCodePageTypeCP1251,
    SCBCodePageTypeCP1252,
    SCBCodePageTypeCP2001,
    SCBCodePageTypeCP3001,
    SCBCodePageTypeCP3002,
    SCBCodePageTypeCP3011,
    SCBCodePageTypeCP3012,
    SCBCodePageTypeCP3021,
    SCBCodePageTypeCP3041,
    SCBCodePageTypeCP3840,
    SCBCodePageTypeCP3841,
    SCBCodePageTypeCP3843,
    SCBCodePageTypeCP3844,
    SCBCodePageTypeCP3845,
    SCBCodePageTypeCP3846,
    SCBCodePageTypeCP3847,
    SCBCodePageTypeCP3848,
    SCBCodePageTypeUTF8,
    SCBCodePageTypeBlank
};

#pragma mark - International

typedef NS_ENUM(NSUInteger, SCBInternationalType) {
    SCBInternationalTypeUSA,
    SCBInternationalTypeFrance,
    SCBInternationalTypeGermany,
    SCBInternationalTypeUK,
    SCBInternationalTypeDenmark,
    SCBInternationalTypeSweden,
    SCBInternationalTypeItaly,
    SCBInternationalTypeSpain,
    SCBInternationalTypeJapan,
    SCBInternationalTypeNorway,
    SCBInternationalTypeDenmark2,
    SCBInternationalTypeSpain2,
    SCBInternationalTypeLatinAmerica,
    SCBInternationalTypeKorea,
    SCBInternationalTypeIreland,
    SCBInternationalTypeLegal
};

#pragma mark - Logo

typedef NS_ENUM(NSUInteger, SCBLogoSize) {
    SCBLogoSizeNormal,
    SCBLogoSizeDoubleWidth,
    SCBLogoSizeDoubleHeight,
    SCBLogoSizeDoubleWidthDoubleHeight
};

#pragma mark - Alignment

typedef NS_ENUM(NSInteger, SCBAlignmentPosition) {
    SCBAlignmentPositionLeft,
    SCBAlignmentPositionCenter,
    SCBAlignmentPositionRight
};

#pragma mark - CutPaper

typedef NS_ENUM(NSInteger, SCBCutPaperAction) {
    SCBCutPaperActionFullCut,
    SCBCutPaperActionPartialCut,
    SCBCutPaperActionFullCutWithFeed,
    SCBCutPaperActionPartialCutWithFeed
};

#pragma mark - Peripheral

typedef NS_ENUM(NSInteger, SCBPeripheralChannel) {
    SCBPeripheralChannelNo1,
    SCBPeripheralChannelNo2
};

#pragma mark - Sound

typedef NS_ENUM(NSInteger, SCBSoundChannel) {
    SCBSoundChannelNo1,
    SCBSoundChannelNo2
};

#pragma mark - Barcode

typedef NS_ENUM(NSUInteger, SCBBarcodeSymbology) {
    SCBBarcodeSymbologyUPCE,
    SCBBarcodeSymbologyUPCA,
    SCBBarcodeSymbologyJAN8,
    SCBBarcodeSymbologyJAN13,
    SCBBarcodeSymbologyCode39,
    SCBBarcodeSymbologyITF,
    SCBBarcodeSymbologyCode128,
    SCBBarcodeSymbologyCode93,
//  SCBBarcodeSymbologyCodabar,
    SCBBarcodeSymbologyNW7
};

typedef NS_ENUM(NSUInteger, SCBBarcodeWidth) {
    SCBBarcodeWidthMode1,
    SCBBarcodeWidthMode2,
    SCBBarcodeWidthMode3,
    SCBBarcodeWidthMode4,
    SCBBarcodeWidthMode5,
    SCBBarcodeWidthMode6,
    SCBBarcodeWidthMode7,
    SCBBarcodeWidthMode8,
    SCBBarcodeWidthMode9,
    SCBBarcodeWidthExtMode1,
    SCBBarcodeWidthExtMode2,
    SCBBarcodeWidthExtMode3,
    SCBBarcodeWidthExtMode4,
    SCBBarcodeWidthExtMode5,
    SCBBarcodeWidthExtMode6,
    SCBBarcodeWidthExtMode7,
    SCBBarcodeWidthExtMode8,
    SCBBarcodeWidthExtMode9
};

#pragma mark - Pdf417

typedef NS_ENUM(NSUInteger, SCBPdf417Level) {
    SCBPdf417LevelECC0,
    SCBPdf417LevelECC1,
    SCBPdf417LevelECC2,
    SCBPdf417LevelECC3,
    SCBPdf417LevelECC4,
    SCBPdf417LevelECC5,
    SCBPdf417LevelECC6,
    SCBPdf417LevelECC7,
    SCBPdf417LevelECC8
};

#pragma mark - QrCode

typedef NS_ENUM(NSUInteger, SCBQrCodeModel) {
    SCBQrCodeModelNo1,
    SCBQrCodeModelNo2
};

typedef NS_ENUM(NSUInteger, SCBQrCodeLevel) {
    SCBQrCodeLevelL,
    SCBQrCodeLevelM,
    SCBQrCodeLevelQ,
    SCBQrCodeLevelH
};

#pragma mark - Bitmap

typedef NS_ENUM(NSInteger, SCBBitmapConverterRotation) {
    SCBBitmapConverterRotationNormal,
    SCBBitmapConverterRotationRight90,
    SCBBitmapConverterRotationLeft90,
    SCBBitmapConverterRotationRotate180
};

#pragma mark - BlackMark

typedef NS_ENUM(NSInteger, SCBBlackMarkType) {
    SCBBlackMarkTypeInvalid,
    SCBBlackMarkTypeValid,
    SCBBlackMarkTypeValidWithDetection
};

#pragma mark - Printable Area

typedef NS_ENUM(NSInteger, SCBPrintableAreaType) {
    SCBPrintableAreaTypeStandard,
    SCBPrintableAreaTypeType1,
    SCBPrintableAreaTypeType2,
    SCBPrintableAreaTypeType3,
    SCBPrintableAreaTypeType4
};

#pragma mark - CJK Unified Ideograph Font

typedef NS_ENUM(NSInteger, SCBCjkUnifiedIdeographFont) {
    SCBCjkUnifiedIdeographFontJapanese           = 1,
    SCBCjkUnifiedIdeographFontSimplifiedChinese  = 2,
    SCBCjkUnifiedIdeographFontTraditionalChinese = 3,
    SCBCjkUnifiedIdeographFontHangul             = 4
};

@interface ISCBBuilder : NSObject

@property (nonatomic, readonly) NSMutableData *commands;

#pragma mark - Document

- (void)beginDocument;

- (void)endDocument;

#pragma mark - Initialization

- (void)appendInitialization:(SCBInitializationType)type;

#pragma mark - Generic

- (void)appendByte:(unsigned char)data;

- (void)appendData:(NSData *)otherData;

- (void)appendBytes:(const void *)bytes
             length:(NSUInteger)length;

- (void)appendRawByte:(unsigned char)data;

- (void)appendRawData:(NSData *)otherData;

- (void)appendRawBytes:(const void *)bytes
                length:(NSUInteger)length;

#pragma mark - FontStyle

- (void)appendFontStyle:(SCBFontStyleType)type;

#pragma mark - CodePage

- (void)appendCodePage:(SCBCodePageType)type;

#pragma mark - International

- (void)appendInternational:(SCBInternationalType)type;

#pragma mark - Feed

- (void)appendLineFeed;

- (void)appendDataWithLineFeed:(NSData *)otherData;

- (void)appendBytesWithLineFeed:(const void *)bytes
                         length:(NSUInteger)length;

- (void)appendLineFeed:(NSInteger)line;

- (void)appendDataWithLineFeed:(NSData *)otherData
                          line:(NSInteger)line;

- (void)appendBytesWithLineFeed:(const void *)bytes
                         length:(NSUInteger)length
                           line:(NSInteger)line;

- (void)appendUnitFeed:(NSInteger)unit;

- (void)appendDataWithUnitFeed:(NSData *)otherData
                          unit:(NSInteger)unit;

- (void)appendBytesWithUnitFeed:(const void *)bytes
                         length:(NSUInteger)length
                           unit:(NSInteger)unit;

#pragma mark - CharacterSpace

- (void)appendCharacterSpace:(NSInteger)space;

#pragma mark - LineSpace

- (void)appendLineSpace:(NSInteger)lineSpace;

#pragma mark - Emphasis

- (void)appendEmphasis:(BOOL)emphasis;

- (void)appendDataWithEmphasis:(NSData *)otherData;

- (void)appendBytesWithEmphasis:(const void *)bytes
                         length:(NSUInteger)length;

#pragma mark - Invert

- (void)appendInvert:(BOOL)invert;

- (void)appendDataWithInvert:(NSData *)otherData;

- (void)appendBytesWithInvert:(const void *)bytes
                       length:(NSUInteger)length;

#pragma mark - Multiple

- (void)appendMultiple:(NSInteger)width
                height:(NSInteger)height;

- (void)appendDataWithMultiple:(NSData *)otherData
                         width:(NSInteger)width
                        height:(NSInteger)height;

- (void)appendBytesWithMultiple:(const void *)bytes
                         length:(NSUInteger)length
                          width:(NSInteger)width
                         height:(NSInteger)height;

- (void)appendMultipleHeight:(NSInteger)height;

- (void)appendDataWithMultipleHeight:(NSData *)otherData
                              height:(NSInteger)height;

- (void)appendBytesWithMultipleHeight:(const void *)bytes
                               length:(NSUInteger)length
                               height:(NSInteger)height;

- (void)appendMultipleWidth:(NSInteger)width;

- (void)appendDataWithMultipleWidth:(NSData *)otherData
                              width:(NSInteger)width;

- (void)appendBytesWithMultipleWidth:(const void *)bytes
                              length:(NSUInteger)length
                               width:(NSInteger)width;

#pragma mark - UnderLine

- (void)appendUnderLine:(BOOL)underLine;

- (void)appendDataWithUnderLine:(NSData *)otherData;

- (void)appendBytesWithUnderLine:(const void *)bytes
                          length:(NSUInteger)length;

#pragma mark - Logo

- (void)appendLogo:(SCBLogoSize)size
            number:(NSInteger)number;

#pragma mark - AbsolutePosition

- (void)appendAbsolutePosition:(NSInteger)position;

- (void)appendDataWithAbsolutePosition:(NSData *)otherData
                              position:(NSInteger)position;

- (void)appendBytesWithAbsolutePosition:(const void *)bytes
                                 length:(NSUInteger)length
                               position:(NSInteger)position;

#pragma mark - Alignment

- (void)appendAlignment:(SCBAlignmentPosition)position;

- (void)appendDataWithAlignment:(NSData *)otherData
                       position:(SCBAlignmentPosition)position;

- (void)appendBytesWithAlignment:(const void *)bytes
                          length:(NSUInteger)length
                        position:(SCBAlignmentPosition)position;

#pragma mark - HorizontalTabPosition

- (void)appendHorizontalTabPosition:(NSArray<NSNumber *> *)positions;

#pragma mark - CutPaper

- (void)appendCutPaper:(SCBCutPaperAction)action;

#pragma mark - Peripheral

- (void)appendPeripheral:(SCBPeripheralChannel)channel;

- (void)appendPeripheral:(SCBPeripheralChannel)channel
                    time:(NSInteger)time;

#pragma mark - Sound

- (void)appendSound:(SCBSoundChannel)channel;

- (void)appendSound:(SCBSoundChannel)channel
             repeat:(NSInteger)repeat;

- (void)appendSound:(SCBSoundChannel)channel
             repeat:(NSInteger)repeat
          driveTime:(NSInteger)driveTime
          delayTime:(NSInteger)delayTime;


#pragma mark - Barcode

- (void)appendBarcodeData:(NSData *)otherData
                symbology:(SCBBarcodeSymbology)symbology
                    width:(SCBBarcodeWidth)width
                   height:(NSInteger)height
                      hri:(BOOL)hri;

- (void)appendBarcodeBytes:(const void *)bytes
                    length:(NSUInteger)length
                 symbology:(SCBBarcodeSymbology)symbology
                     width:(SCBBarcodeWidth)width
                    height:(NSInteger)height
                       hri:(BOOL)hri;

- (void)appendBarcodeDataWithAbsolutePosition:(NSData *)otherData
                                    symbology:(SCBBarcodeSymbology)symbology
                                        width:(SCBBarcodeWidth)width
                                       height:(NSInteger)height
                                          hri:(BOOL)hri
                                     position:(NSInteger)position;

- (void)appendBarcodeBytesWithAbsolutePosition:(const void *)bytes
                                        length:(NSUInteger)length
                                     symbology:(SCBBarcodeSymbology)symbology
                                         width:(SCBBarcodeWidth)width
                                        height:(NSInteger)height
                                           hri:(BOOL)hri
                                      position:(NSInteger)position;

- (void)appendBarcodeDataWithAlignment:(NSData *)otherData
                             symbology:(SCBBarcodeSymbology)symbology
                                 width:(SCBBarcodeWidth)width
                                height:(NSInteger)height
                                   hri:(BOOL)hri
                              position:(SCBAlignmentPosition)position;

- (void)appendBarcodeBytesWithAlignment:(const void *)bytes
                                 length:(NSUInteger)length
                              symbology:(SCBBarcodeSymbology)symbology
                                  width:(SCBBarcodeWidth)width
                                 height:(NSInteger)height
                                    hri:(BOOL)hri
                               position:(SCBAlignmentPosition)position;

#pragma mark - Pdf417

- (void)appendPdf417Data:(NSData *)otherData
                    line:(NSInteger)line
                  column:(NSInteger)column
                   level:(SCBPdf417Level)level
                  module:(NSInteger)module
                  aspect:(NSInteger)aspect;

- (void)appendPdf417Bytes:(const void *)bytes
                   length:(NSUInteger)length
                     line:(NSInteger)line
                   column:(NSInteger)column
                    level:(SCBPdf417Level)level
                   module:(NSInteger)module
                   aspect:(NSInteger)aspect;

- (void)appendPdf417DataWithAbsolutePosition:(NSData *)otherData
                                        line:(NSInteger)line
                                      column:(NSInteger)column
                                       level:(SCBPdf417Level)level
                                      module:(NSInteger)module
                                      aspect:(NSInteger)aspect
                                    position:(NSInteger)position;

- (void)appendPdf417BytesWithAbsolutePosition:(const void *)bytes
                                       length:(NSUInteger)length
                                         line:(NSInteger)line
                                       column:(NSInteger)column
                                        level:(SCBPdf417Level)level
                                       module:(NSInteger)module
                                       aspect:(NSInteger)aspect
                                     position:(NSInteger)position;

- (void)appendPdf417DataWithAlignment:(NSData *)otherData
                                 line:(NSInteger)line
                               column:(NSInteger)column
                                level:(SCBPdf417Level)level
                               module:(NSInteger)module
                               aspect:(NSInteger)aspect
                             position:(SCBAlignmentPosition)position;

- (void)appendPdf417BytesWithAlignment:(const void *)bytes
                                length:(NSUInteger)length
                                  line:(NSInteger)line
                                column:(NSInteger)column
                                 level:(SCBPdf417Level)level
                                module:(NSInteger)module
                                aspect:(NSInteger)aspect
                              position:(SCBAlignmentPosition)position;

#pragma mark - QrCode

- (void)appendQrCodeData:(NSData *)otherData
                   model:(SCBQrCodeModel)model
                   level:(SCBQrCodeLevel)level
                    cell:(NSInteger)cell;

- (void)appendQrCodeBytes:(const void *)bytes
                   length:(NSUInteger)length
                    model:(SCBQrCodeModel)model
                    level:(SCBQrCodeLevel)level
                     cell:(NSInteger)cell;

- (void)appendQrCodeDataWithAbsolutePosition:(NSData *)otherData
                                       model:(SCBQrCodeModel)model
                                       level:(SCBQrCodeLevel)level
                                        cell:(NSInteger)cell
                                    position:(NSInteger)position;

- (void)appendQrCodeBytesWithAbsolutePosition:(const void *)bytes
                                       length:(NSUInteger)length
                                        model:(SCBQrCodeModel)model
                                        level:(SCBQrCodeLevel)level
                                         cell:(NSInteger)cell
                                     position:(NSInteger)position;

- (void)appendQrCodeDataWithAlignment:(NSData *)otherData
                                model:(SCBQrCodeModel)model
                                level:(SCBQrCodeLevel)level
                                 cell:(NSInteger)cell
                             position:(SCBAlignmentPosition)position;

- (void)appendQrCodeBytesWithAlignment:(const void *)bytes
                                length:(NSUInteger)length
                                 model:(SCBQrCodeModel)model
                                 level:(SCBQrCodeLevel)level
                                  cell:(NSInteger)cell
                              position:(SCBAlignmentPosition)position;

#pragma mark - Bitmap

- (void)appendBitmap:(UIImage *)image
           diffusion:(BOOL)diffusion
               width:(NSInteger)width
           bothScale:(BOOL)bothScale
            rotation:(SCBBitmapConverterRotation)rotation;

- (void)appendBitmap:(UIImage *)image
           diffusion:(BOOL)diffusion
            rotation:(SCBBitmapConverterRotation)rotation;

- (void)appendBitmap:(UIImage *)image
           diffusion:(BOOL)diffusion
               width:(NSInteger)width
           bothScale:(BOOL)bothScale;

- (void)appendBitmap:(UIImage *)image
           diffusion:(BOOL)diffusion;

- (void)appendBitmapWithAbsolutePosition:(UIImage *)image
                               diffusion:(BOOL)diffusion
                                   width:(NSInteger)width
                               bothScale:(BOOL)bothScale
                                rotation:(SCBBitmapConverterRotation)rotation
                                position:(NSInteger)position;

- (void)appendBitmapWithAbsolutePosition:(UIImage *)image
                               diffusion:(BOOL)diffusion
                                rotation:(SCBBitmapConverterRotation)rotation
                                position:(NSInteger)position;

- (void)appendBitmapWithAbsolutePosition:(UIImage *)image
                               diffusion:(BOOL)diffusion
                                   width:(NSInteger)width
                               bothScale:(BOOL)bothScale
                                position:(NSInteger)position;

- (void)appendBitmapWithAbsolutePosition:(UIImage *)image
                               diffusion:(BOOL)diffusion
                                position:(NSInteger)position;

- (void)appendBitmapWithAlignment:(UIImage *)image
                        diffusion:(BOOL)diffusion
                            width:(NSInteger)width
                        bothScale:(BOOL)bothScale
                         rotation:(SCBBitmapConverterRotation)rotation
                         position:(SCBAlignmentPosition)position;

- (void)appendBitmapWithAlignment:(UIImage *)image
                        diffusion:(BOOL)diffusion
                         rotation:(SCBBitmapConverterRotation)rotation
                         position:(SCBAlignmentPosition)position;

- (void)appendBitmapWithAlignment:(UIImage *)image
                        diffusion:(BOOL)diffusion
                            width:(NSInteger)width
                        bothScale:(BOOL)bothScale
                         position:(SCBAlignmentPosition)position;

- (void)appendBitmapWithAlignment:(UIImage *)image
                        diffusion:(BOOL)diffusion
                         position:(SCBAlignmentPosition)position;

#pragma mark - BlackMark

- (void)appendBlackMark:(SCBBlackMarkType)type;

#pragma mark - Top Margin

- (void)appendTopMargin:(NSInteger)topMargin;

#pragma mark - Printable Area

- (void)appendPrintableArea:(SCBPrintableAreaType)type;

#pragma mark - CJK Unified Ideograph Font

- (void)appendCjkUnifiedIdeographFont:(NSArray<NSNumber *> *)fonts;

#pragma mark - PageMode

- (void)beginPageMode:(CGRect)rect
             rotation:(SCBBitmapConverterRotation)rotation;

- (void)endPageMode;

- (void)appendPageModeVerticalAbsolutePosition:(NSInteger)position;

- (void)appendPageModeRotation:(SCBBitmapConverterRotation)rotation;

@end
