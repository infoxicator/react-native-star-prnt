//
//  StarIoExt.h
//  StarIO_Extension
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ISCBBuilder.h"
#import "ISDCBBuilder.h"
#import "ISSCBBuilder.h"

#import "ISCPConnectParser.h"

#import "ISSCPWeightParser.h"

typedef NS_ENUM(NSInteger, StarIoExtEmulation) {     // Don't insert!
    StarIoExtEmulationNone = 0,
    StarIoExtEmulationStarPRNT,
    StarIoExtEmulationStarLine,
    StarIoExtEmulationStarGraphic,
    StarIoExtEmulationEscPos,
    StarIoExtEmulationEscPosMobile,
    StarIoExtEmulationStarDotImpact,
    StarIoExtEmulationStarPRNTL
};

typedef NS_ENUM(NSInteger, StarIoExtCharacterCode) {     // Don't insert!
    StarIoExtCharacterCodeNone = 0,
    StarIoExtCharacterCodeStandard,
    StarIoExtCharacterCodeJapanese,
    StarIoExtCharacterCodeSimplifiedChinese,
    StarIoExtCharacterCodeTraditionalChinese
};

typedef NS_ENUM(NSInteger, StarIoExtBcrModel) {     // Don't insert!
    StarIoExtBcrModelNone = 0,
    StarIoExtBcrModelPOP1
};

typedef NS_ENUM(NSInteger, StarIoExtDisplayModel) {     // Don't insert!
    StarIoExtDisplayModelNone = 0,
    StarIoExtDisplayModelSCD222
};

typedef NS_ENUM(NSInteger, StarIoExtScaleModel) {     // Don't insert!
    StarIoExtScaleModelNone = 0,
    StarIoExtScaleModelAPS10,
    StarIoExtScaleModelAPS12,
    StarIoExtScaleModelAPS20
};

@interface StarIoExt : NSObject

#pragma mark - Generic

+ (NSString *)description;

#pragma mark - Builder

+ (ISCBBuilder *)createCommandBuilder:(StarIoExtEmulation)emulation;

+ (ISDCBBuilder *)createDisplayCommandBuilder:(StarIoExtDisplayModel)model;

+ (ISSCBBuilder *)createScaleCommandBuilder:(StarIoExtScaleModel)model;

#pragma mark - Parser

+ (ISCPConnectParser *)createBcrConnectParser:(StarIoExtBcrModel)model;

+ (ISCPConnectParser *)createDisplayConnectParser:(StarIoExtDisplayModel)model;

+ (ISCPConnectParser *)createScaleConnectParser:(StarIoExtScaleModel)model;

+ (ISSCPWeightParser *)createScaleWeightParser:(StarIoExtScaleModel)model;

@end
