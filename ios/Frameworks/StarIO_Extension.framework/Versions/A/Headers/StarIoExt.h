//
//  StarIoExt.h
//  StarIO_Extension
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Internal/StarIoExtResultCode.h"

#import "ISCBBuilder.h"
#import "ISDCBBuilder.h"
#import "ISMCBBuilder.h"

#import "ISCPConnectParser.h"

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
    StarIoExtBcrModelPOP1,
    StarIoExtBcrModelDS9208
};

typedef NS_ENUM(NSInteger, StarIoExtDisplayModel) {     // Don't insert!
    StarIoExtDisplayModelNone = 0,
    StarIoExtDisplayModelSCD222
};

typedef NS_ENUM(NSUInteger, StarIoExtMelodySpeakerModel) {     // Don't insert!
    StarIoExtMelodySpeakerModelNone = 0,
    StarIoExtMelodySpeakerModelMCS10,
    StarIoExtMelodySpeakerModelFVP10
};

@interface StarIoExt : NSObject

#pragma mark - Generic

+ (NSString *)description;

#pragma mark - Builder

+ (ISCBBuilder *)createCommandBuilder:(StarIoExtEmulation)emulation;

+ (ISDCBBuilder *)createDisplayCommandBuilder:(StarIoExtDisplayModel)model;

+ (ISMCBBuilder *)createMelodySpeakerCommandBuilder:(StarIoExtMelodySpeakerModel)model;

#pragma mark - Parser

+ (ISCPConnectParser *)createBcrConnectParser:(StarIoExtBcrModel)model;

+ (ISCPConnectParser *)createDisplayConnectParser:(StarIoExtDisplayModel)model;

+ (ISCPConnectParser *)createMelodySpeakerConnectParser:(StarIoExtMelodySpeakerModel)model
                                                  error:(NSError **)error;

@end
