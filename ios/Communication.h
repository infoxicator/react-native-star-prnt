//
//  Communication.h
//  ObjectiveC SDK
//
//  Created by Yuji on 2015/**/**.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StarIO/SMPort.h>

#import <StarIO_Extension/ISCPParser.h>

typedef void (^SendCompletionHandler)(BOOL result, NSString *title, NSString *message);

typedef void (^RequestStatusCompletionHandler)(BOOL result, NSString *title, NSString *message, BOOL connect);

@interface Communication : NSObject

+ (BOOL)sendCommands:(NSData *)commands
                port:(SMPort *)port
   completionHandler:(SendCompletionHandler)completionHandler;

+ (BOOL)sendCommandsDoNotCheckCondition:(NSData *)commands
                                   port:(SMPort *)port
                      completionHandler:(SendCompletionHandler)completionHandler;

+ (BOOL)parseDoNotCheckCondition:(ISCPParser *)parser
                            port:(SMPort *)port
               completionHandler:(SendCompletionHandler)completionHandler;

+ (BOOL)sendCommands:(NSData *)commands
            portName:(NSString *)portName
        portSettings:(NSString *)portSettings
             timeout:(NSInteger)timeout
   completionHandler:(SendCompletionHandler)completionHandler;

+ (BOOL)sendCommandsDoNotCheckCondition:(NSData *)commands
                               portName:(NSString *)portName
                           portSettings:(NSString *)portSettings
                                timeout:(NSInteger)timeout
                      completionHandler:(SendCompletionHandler)completionHandler;

+ (void)connectBluetooth:(SendCompletionHandler)completionHandler;

+ (BOOL)disconnectBluetooth:(NSString *)modelName
                   portName:(NSString *)portName
               portSettings:(NSString *)portSettings
                    timeout:(NSInteger)timeout
          completionHandler:(SendCompletionHandler)completionHandler;

+ (BOOL)confirmSerialNumber:(NSString *)portName
               portSettings:(NSString *)portSettings
                    timeout:(NSInteger)timeout
          completionHandler:(SendCompletionHandler)completionHandler;

@end
