//
//  enum.h
//  StarIOPort
//
//  Created by u3237 on 2015/10/19.
//
//

#ifndef enum_h
#define enum_h

typedef enum _SMEmulation {
    SMEmulationUnknown = 0,
    SMEmulationStarLine,
    SMEmulationESCPOS
} SMEmulation;

typedef enum {
    SMConnectionResultSuccess = 0,
    SMConnectionResultFailure = -1,
    SMConnectionResultRejected = -2
} SMConnectionResult;

#endif
