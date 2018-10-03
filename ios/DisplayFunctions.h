//
//  DisplayFunctions.h
//  ObjectiveC SDK
//
//  Created by Yuji on 2016/**/**.
//  Copyright © 2016年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StarIO_Extension/StarIoExt.h>

@interface DisplayFunctions : NSObject

+ (void)appendClearScreen:(ISDCBBuilder *)builder;

+ (void)appendTextPattern:(ISDCBBuilder *)builder number:(int)number;

+ (void)appendGraphicPattern:(ISDCBBuilder *)builder number:(int)number;

+ (void)appendCharacterSet:(ISDCBBuilder *)builder internationalType:(SDCBInternationalType)internationalType codePageType:(SDCBCodePageType)codePageType;

+ (void)appendTurnOn:(ISDCBBuilder *)builder turnOn:(BOOL)turnOn;

+ (void)appendCursorMode:(ISDCBBuilder *)builder cursorMode:(SDCBCursorMode)cursorMode;

+ (void)appendContrastMode:(ISDCBBuilder *)builder contrastMode:(SDCBContrastMode)contrastMode;

+ (void)appendUserDefinedCharacter:(ISDCBBuilder *)builder set:(BOOL)set;

@end
