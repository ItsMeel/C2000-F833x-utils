/*
 * Utils_Registers.h
 *
 *  Created on: 2/02/2024
 *      Author: 000428315
 */

#ifndef UTILS_REGISTERS_H_
#define UTILS_REGISTERS_H_

#include "DSP28x_Project.h"

volatile Uint32 readRegister(volatile Uint32* RegisterAddress, Uint32 Mask){
    return *RegisterAddress & Mask;
}

int writeRegister(volatile Uint32* RegisterAddress, Uint32 Mask, Uint32 Value, Uint32 Protected){
    if (Protected){
        EALLOW;
    }

    *RegisterAddress = (*RegisterAddress & ~Mask) | (Value & Mask);

    if (Protected){
        EDIS;
    }
    return 0;
}

int toggleRegister(volatile Uint32* RegisterAddress, Uint32 Mask, Uint32 Protected){
    if (Protected){
        EALLOW;
    }

    *RegisterAddress = (*RegisterAddress & ~Mask) | (~(*RegisterAddress) & Mask);

    if (Protected){
        EDIS;
    }
    return 0;
}


#endif /* UTILS_REGISTERS_H_ */
