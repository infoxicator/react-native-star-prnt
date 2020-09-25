//
//  Lock.h
//  StarIOPort
//
//  Created by satsuki on 2014/07/16.
//
//

#import <Foundation/Foundation.h>

@interface Lock : NSObject {
    NSLock* lockArray;
}

+ (Lock*)sharedManager;

- (void)lock;
- (void)unlock;
@end
