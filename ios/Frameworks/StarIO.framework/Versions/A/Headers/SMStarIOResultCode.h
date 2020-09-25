//
//  SMStarIOResultCode.h
//  StarIOPort
//
//  Created by *** on 2019/06/10.
//

#pragma once

static const NSErrorDomain SMStarIOResultCodeErrorDomain = @"jp.star-m.stario";

NS_ERROR_ENUM(SMStarIOResultCodeErrorDomain) {
    SMStarIOResultCodeSuccess        = 0,
    SMStarIOResultCodeFailedError    = -1,
    SMStarIOResultCodeInProcessError = -2,
    SMStarIOResultCodeInUseError     = -100,
};
