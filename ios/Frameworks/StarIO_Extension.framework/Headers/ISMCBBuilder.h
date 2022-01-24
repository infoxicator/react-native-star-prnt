//
//  ISMCBBuilder.h
//  StarIO_Extension
//
//  Copyright (c) 2018 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SMSoundSetting;

#pragma mark - SoundStorageArea

typedef NS_ENUM(NSInteger, SMCBSoundStorageArea) {
    SMCBSoundStorageArea1 = 0x00,
    SMCBSoundStorageArea2 = 0x01
};

#pragma mark - Member

@interface ISMCBBuilder: NSObject

@property NSMutableData * _Nonnull commands;

- (void)appendSoundWithSetting:(nullable SMSoundSetting *)setting
                         error:(NSError * _Nullable * _Nullable)error;

- (void)appendSoundWithSound:(nonnull NSData *)data
                     setting:(nullable SMSoundSetting *)setting
                       error:(NSError * _Nullable * _Nullable)error;
@end

