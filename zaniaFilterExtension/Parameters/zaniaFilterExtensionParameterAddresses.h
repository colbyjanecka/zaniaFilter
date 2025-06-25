//
//  zaniaFilterExtensionParameterAddresses.h
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

#pragma once

#include <AudioToolbox/AUParameters.h>

typedef NS_ENUM(AUParameterAddress, zaniaFilterExtensionParameterAddress) {
    gain = 0,
    attack,
    pan,
    cutoff,
    resonance,
    temp
};

