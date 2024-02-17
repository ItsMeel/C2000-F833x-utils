/**
 * @file Utils_Registers.h
 * @author Emmanuel David Angarita Quintanilla (emmanueldavidaq@gmail.com)
 * @brief This file contains all functions to write and read registers.
 */


#ifndef UTILS_REGISTERS_H_
#define UTILS_REGISTERS_H_

#include "DSP28x_Project.h"

/**
 * @brief Read the value of a register through a mask.
 * 
 * @param RegisterAddress The register address to be read.
 * @param Mask The mask
 * @return The masked register value.
 */

volatile Uint32 readRegister(volatile Uint32* RegisterAddress, Uint32 Mask){
    return *RegisterAddress & Mask;
}

/**
 * @brief Write a masked value to a register.
 * 
 * @param RegisterAddress The register address to be written.
 * @param Mask The mask.
 * @param Value The value.
 * @param Protected Indicate the use of EALLOW and EDIS, this should be set to True for protected registers.
 * @return Always returns 0.
 */

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

/**
 * @brief Toogle the bits of a register indicated by a mask.
 * 
 * @param RegisterAddress The register address.
 * @param Mask The mask.
 * @param Protected Indicate the use of EALLOW and EDIS, this should be set to True for protected registers.
 * @return Always returns 0.
 */

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
