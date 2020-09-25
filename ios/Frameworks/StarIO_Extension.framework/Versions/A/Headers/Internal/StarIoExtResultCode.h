//
//  StarIoExtResultCode.h
//  StarIO_Extension
//
//  Copyright © 2018年 Star Micronics. All rights reserved.
//

#pragma once

static const NSErrorDomain SMResultCodeErrorDomain = @"jp.star-m.stario_extension";

NS_ERROR_ENUM(SMResultCodeErrorDomain) {
    SMResultCodeFailedError        = -1,
    SMResultCodeInProcessError     = -2,
    SMResultCodeFormatError        = -3,
    SMResultCodeArgumentOutOfRange = -4,
    SMResultCodeInvalidArgument    = -5,
    SMResultCodeInvalidOperation   = -6,
    SMResultCodeInUseError         = -100,
};
