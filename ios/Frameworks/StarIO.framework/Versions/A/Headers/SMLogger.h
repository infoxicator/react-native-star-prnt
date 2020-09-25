//
//  SMLogger.h
//  StarIOPort
//
//  Created by u3415 on 2018/09/14.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, SMLogLevel) {
    SMLogLevelDefault
};

@interface SMLogger : NSObject

@property (nonatomic) SMLogLevel logLevel;

@property(nonatomic, readonly) BOOL isLogging;

- (void)logString:(nonnull NSString *)string NS_SWIFT_NAME(log(_:));

- (void)start;

- (void)stop;

@end
