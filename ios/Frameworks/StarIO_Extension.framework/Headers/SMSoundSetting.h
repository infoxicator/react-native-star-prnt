//
//  SoundSetting.h
//  StarIO_Extension
//
//  Copyright (c) 2018 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ISMCBBuilder.h"

#pragma mark - SMSoundSettingVolume

typedef NS_ENUM(NSInteger, SMSoundSettingVolume) {
    SMSoundSettingVolumeOff = -2,
    SMSoundSettingVolumeMin = -3,
    SMSoundSettingVolumeMax = -4
};

#pragma mark - Member

@interface SMSoundSetting : NSObject

@property (nonatomic) SMCBSoundStorageArea soundStorageArea;

@property (nonatomic) NSInteger soundNumber;

@property (nonatomic) NSInteger volume;

@property (nonatomic) NSInteger count;

@property (nonatomic) NSInteger delay;

@property (nonatomic) NSInteger interval;

@end
