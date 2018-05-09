
#if __has_include("RCTBridgeModule.h")
#import "RCTBridgeModule.h"
#else
#import <React/RCTBridgeModule.h>
#endif
#import <StarIO/SMPort.h>
#import <StarIO_Extension/StarIoExt.h>
#import <StarIO_Extension/StarIoExtManager.h>
#import "Communication.h"

@interface RNStarPrnt : NSObject <RCTBridgeModule>

@end
  
