//
//  ISDCBBuilder.h
//  StarIO_Extension
//
//  Created by Yuji on 2017/**/**.
//  Copyright © 2017年 Star Micronics. All rights reserved.
//

#import <UIKit/UIKit.h>

#pragma mark - International

typedef NS_ENUM(NSInteger, SDCBInternationalType) {
    SDCBInternationalTypeUSA          = 0x00,
    SDCBInternationalTypeFrance       = 0x01,
    SDCBInternationalTypeGermany      = 0x02,
    SDCBInternationalTypeUK           = 0x03,
    SDCBInternationalTypeDenmark      = 0x04,
    SDCBInternationalTypeSweden       = 0x05,
    SDCBInternationalTypeItaly        = 0x06,
    SDCBInternationalTypeSpain        = 0x07,
    SDCBInternationalTypeJapan        = 0x08,
    SDCBInternationalTypeNorway       = 0x09,
    SDCBInternationalTypeDenmark2     = 0x0a,
    SDCBInternationalTypeSpain2       = 0x0b,
    SDCBInternationalTypeLatinAmerica = 0x0c,
    SDCBInternationalTypeKorea        = 0x0d
};

#pragma mark - CodePage

typedef NS_ENUM(NSInteger, SDCBCodePageType) {
    SDCBCodePageTypeCP437              = 0x00,
    SDCBCodePageTypeKatakana           = 0x01,
    SDCBCodePageTypeCP850              = 0x02,
    SDCBCodePageTypeCP860              = 0x03,
    SDCBCodePageTypeCP863              = 0x04,
    SDCBCodePageTypeCP865              = 0x05,
    SDCBCodePageTypeCP1252             = 0x06,
    SDCBCodePageTypeCP866              = 0x07,
    SDCBCodePageTypeCP852              = 0x08,
    SDCBCodePageTypeCP858              = 0x09,
    SDCBCodePageTypeJapanese           = 0x0a,
    SDCBCodePageTypeSimplifiedChinese  = 0x0b,
    SDCBCodePageTypeTraditionalChinese = 0x0c,
    SDCBCodePageTypeHangul             = 0x0d
};

#pragma mark - Cursor

typedef NS_ENUM(NSInteger, SDCBCursorMode) {
    SDCBCursorModeOff   = 0x00,
    SDCBCursorModeBlink = 0x01,
    SDCBCursorModeOn    = 0x02
};

#pragma mark - Contrast

typedef NS_ENUM(NSInteger, SDCBContrastMode) {
    SDCBContrastModeMinus3  = 0x00,
    SDCBContrastModeMinus2  = 0x01,
    SDCBContrastModeMinus1  = 0x02,
    SDCBContrastModeDefault = 0x03,
    SDCBContrastModePlus1   = 0x04,
    SDCBContrastModePlus2   = 0x05,
    SDCBContrastModePlus3   = 0x06
};

#pragma mark - Member

@interface ISDCBBuilder : NSObject

@property (nonatomic, readonly) NSMutableData *commands;
@property (nonatomic, readonly) NSMutableData *passThroughCommands;

- (void)appendByte:(unsigned char)data;

- (void)appendData:(NSData *)otherData;

- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;

- (void)appendBackSpace;

- (void)appendHorizontalTab;

- (void)appendLineFeed;

- (void)appendCarriageReturn;

- (void)appendBitmap:(UIImage *)image diffusion:(BOOL)diffusion;

- (void)appendInternational:(SDCBInternationalType)type;

- (void)appendCodePage:(SDCBCodePageType)type;

- (void)appendDeleteToEndOfLine;

- (void)appendClearScreen;

- (void)appendHomePosition;

- (void)appendTurnOn:(BOOL)turnOn;

- (void)appendSpecifiedPosition:(int)x y:(int)y;

- (void)appendCursorMode:(SDCBCursorMode)cursorMode;

- (void)appendContrastMode:(SDCBContrastMode)contrastMode;

- (void)appendUserDefinedCharacter:(int)index code:(int)code font:(unsigned char *)font;

- (void)appendUserDefinedDbcsCharacter:(int)index code:(int)code font:(unsigned char *)font;

@end
