//
//  SMFileLogger.h
//  StarIOPort
//
//  Created by u3415 on 2018/09/14.
//

#import "SMLogger.h"

@interface SMFileLogger : SMLogger

@property(class, nonatomic, readonly, nonnull) SMFileLogger *sharedInstance NS_SWIFT_NAME(shared);

@property(nonatomic) NSUInteger maxLogSize;

@property(nonatomic, readonly, nonnull) NSString *logDirectoryPath;

@end
