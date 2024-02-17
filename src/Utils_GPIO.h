/**
 * @file Utils_GPIO.h
 * @author Emmanuel David Angarita Quintanilla (emmanueldavidaq@gmail.com)
 * @brief This file contains all functions to manipulate GPIOs.
 */

#ifndef UTILS_GPIO_H_
#define UTILS_GPIO_H_

#include "DSP28x_Project.h"
#include "Utils_Registers.h"

/**
 * \def GPIO_HIGH
 * @brief Represents high GPIO state.
 */

/**
 * \def GPIO_LOW
 * @brief Represents low GPIO state.
 */

#define GPIO_HIGH 1
#define GPIO_LOW 0

/**
 * \def GPIO_INPUT
 * @brief Represents input GPIO direction.
 */

/**
 * \def GPIO_OUTPUT
 * @brief Represents output GPIO direction.
 */

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

/**
 * \def GPIO_PULLUP_ENABLE
 * @brief Represents enabling GPIO pullup resistor.
 */

/**
 * \def GPIO_PULLUP_DISABLE
 * @brief Represents disabling GPIO pullup resistor.
 */

#define GPIO_PULLUP_ENABLE 0
#define GPIO_PULLUP_DISABLE 1

/**
 * \def GPIO_PERIPHERAL_0
 * @brief Represents the first GPIO peripheral.
 */

/**
 * \def GPIO_PERIPHERAL_1
 * @brief Represents the second GPIO peripheral.
 */

/**
 * \def GPIO_PERIPHERAL_2
 * @brief Represents the third GPIO peripheral.
 */

/**
 * \def GPIO_PERIPHERAL_3
 * @brief Represents the fourth GPIO peripheral.
 */

#define GPIO_PERIPHERAL_0 0
#define GPIO_PERIPHERAL_1 1
#define GPIO_PERIPHERAL_2 2
#define GPIO_PERIPHERAL_3 3

/**
 * \def GPIO_QUALSEL_SYNC
 * @brief Syncronize GPIO with SYSCLKOUT.
 */

/**
 * \def GPIO_QUALSEL_3SAMPLES
 * @brief GPIO qualification using 3 samples.
 */

/**
 * \def GPIO_QUALSEL_6SAMPLES
 * @brief GPIO qualification using 6 samples.
 */

/**
 * \def GPIO_QUALSEL_ASYNC
 * @brief Asynchronous GPIO.
 */

#define GPIO_QUALSEL_SYNC 0
#define GPIO_QUALSEL_3SAMPLES 1
#define GPIO_QUALSEL_6SAMPLES 2
#define GPIO_QUALSEL_ASYNC 3

/**
 * \def pinToMux(pin)
 * @brief Obtain the mux number of a pin.
 * @param pin The pin number.
 * @returns The mux number.
 */

#define pinToMux(pin) ((Uint32) pin/16)

/**
 * \def pinToQual(pin)
 * @brief Obtain the qual number of a pin.
 * @param pin The pin number.
 * @returns The qual number..
 */

#define pinToQual(pin) ((Uint32) pin/8)

/**
 * \def pinToMaskOneBit(pin, value)
 * @brief Obtain the resigter mask for a value of 1 bit of a given pin.
 * @param pin The pin number.
 * @param value The value to mask.
 * @returns The mask.
 */

#define pinToMaskOneBit(pin, value) ((Uint32) (value << (pin % 32)))

/**
 * \def pinToMaskTwoBits(pin, value)
 * @brief Obtain the resigter mask for a value of 2 bits of a given pin.
 * @param pin The pin number.
 * @param value The value to mask.
 * @returns The mask.
 */

#define pinToMaskTwoBits(pin, value) ((Uint32) (value << (pin % 16)*2))

/**
 * \def qualToMaskFourBits(qual, value)
 * @brief Obtain the resigter mask for a value of 4 bits of a given qual.
 * @param pin The qual number.
 * @param value The value to mask.
 * @returns The mask.
 */

#define qualToMaskFourBits(qual, value) ((Uint32) (value << (qual % 4)*8))

/**
 * @brief Get the pointer of the GPxCTRL of a given qual.
 * 
 * @param Qual The qual number.
 * @return The pointer to the corresponding GPxCTRL register.
 */

volatile Uint32* qualToCtrlRegister(Uint32 Qual){
    volatile Uint32* Output = 0;
    if(Qual <= 3){
        Output = &GpioCtrlRegs.GPACTRL.all;
    }
    else if(Qual >= 4 && Qual <= 7){
        Output = &GpioCtrlRegs.GPBCTRL.all;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxSELx of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxSELx register.
 */

volatile Uint32* pinToQSelRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    switch (Mux){
        case 1:
            Output = &GpioCtrlRegs.GPAQSEL1.all;
        break;

        case 2:
            Output = &GpioCtrlRegs.GPAQSEL2.all;
        break;

        case 3:
            Output = &GpioCtrlRegs.GPBQSEL1.all;
        break;

        case 4:
            Output = &GpioCtrlRegs.GPBQSEL2.all;
        break;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxMUXx of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxMUXx register.
 */

volatile Uint32* pinToMuxRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    switch (Mux){
        case 1:
            Output = &GpioCtrlRegs.GPAMUX1.all;
        break;

        case 2:
            Output = &GpioCtrlRegs.GPAMUX2.all;
        break;

        case 3:
            Output = &GpioCtrlRegs.GPBMUX1.all;
        break;

        case 4:
            Output = &GpioCtrlRegs.GPBMUX2.all;
        break;

        case 5:
            Output = &GpioCtrlRegs.GPCMUX1.all;
        break;

        case 6:
            Output = &GpioCtrlRegs.GPCMUX2.all;
        break;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxDIR of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxDIR register.
 */

volatile Uint32* pinToDirRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    if(Mux == 0 || Mux == 1){
        Output = &GpioCtrlRegs.GPADIR.all;
    }
    else if(Mux == 2 || Mux == 3){
        Output = &GpioCtrlRegs.GPBDIR.all;
    }
    else if(Mux == 4 || Mux == 5){
        Output = &GpioCtrlRegs.GPCDIR.all;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxPUD of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxPUD register.
 */

volatile Uint32* pinToPullUpResistorRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    if(Mux == 0 || Mux == 1){
        Output = &GpioCtrlRegs.GPAPUD.all;
    }
    else if(Mux == 2 || Mux == 3){
        Output = &GpioCtrlRegs.GPBPUD.all;
    }
    else if(Mux == 4 || Mux == 5){
        Output = &GpioCtrlRegs.GPCPUD.all;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxDAT of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxDAT register.
 */

volatile Uint32* pinToDataRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    if(Mux == 0 || Mux == 1){
        Output = &GpioDataRegs.GPADAT.all;
    }
    else if(Mux == 2 || Mux == 3){
        Output = &GpioDataRegs.GPBDAT.all;
    }
    else if(Mux == 4 || Mux == 5){
        Output = &GpioDataRegs.GPCDAT.all;
    }

    return Output;
}

/**
 * @brief Get the pointer of the GPxTOGGLE of a given pin.
 * 
 * @param pin The pin number.
 * @return The pointer to the corresponding GPxTOGGLE register.
 */

volatile Uint32* pinToToggleRegister(Uint32 pin){
    volatile Uint32* Output = 0;
    Uint32 Mux = pinToMux(pin);
    if(Mux == 0 || Mux == 1){
        Output = &GpioDataRegs.GPATOGGLE.all;
    }
    else if(Mux == 2 || Mux == 3){
        Output = &GpioDataRegs.GPBTOGGLE.all;
    }
    else if(Mux == 4 || Mux == 5){
        Output = &GpioDataRegs.GPCTOGGLE.all;
    }

    return Output;
}

/**
 * @brief Set the qualification sampling period of a given qual, it only apllies if input qualification is activated.
 * @see GPIOSetPinQualificationSelect(Uint32 Pin, Uint32 Value)
 * @param Qual The qual number.
 * @param Value The value of the sampling period, it has to be between 0x00 and 0xFF.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetQualSamplingPeriod(Uint32 Qual, Uint32 Value){
    if(Value > 0xFF) return -1;

    volatile Uint32* RegisterAddress = qualToCtrlRegister(Qual);
    if(RegisterAddress == 0) return -1;

    writeRegister(RegisterAddress, qualToMaskFourBits(Qual, 0xFF), qualToMaskFourBits(Qual, Value), 1);

    return 0;
}

/**
 * @brief Set the qualification method of a given pin.
 * @see GPIO_QUALSEL_SYNC
 * @see GPIO_QUALSEL_3SAMPLES
 * @see GPIO_QUALSEL_6SAMPLES
 * @see GPIO_QUALSEL_ASYNC
 * @param Pin The pin number.
 * @param Value The value to set, it has to be between 0x0 and 0x3.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetPinQualificationSelect(Uint32 Pin, Uint32 Value){
    if(Value > 0b11){
        return -1;
    }

    volatile Uint32* RegisterAddress = pinToQSelRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskTwoBits(Pin, 0b11), pinToMaskTwoBits(Pin, Value), 1);

    return 0;
}

/**
 * @brief Set the pin peripheral through the multiplexer.
 * @see GPIO_PERIPHERAL_0
 * @see GPIO_PERIPHERAL_1
 * @see GPIO_PERIPHERAL_2
 * @see GPIO_PERIPHERAL_3
 * @param Pin The pin number.
 * @param Value The value of the peripheral to be selected, it has to be between 0x0 and 0x3.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetPinMux(Uint32 Pin, Uint32 Value){
    if(Value > 0b11){
        return -1;
    }

    volatile Uint32* RegisterAddress = pinToMuxRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskTwoBits(Pin, 0b11), pinToMaskTwoBits(Pin, Value), 1);

    return 0;
}

/**
 * @brief Set the pin direction.
 * @see GPIO_INPUT
 * @see GPIO_OUTPUT
 * @param Pin The pin number.
 * @param Value The value of the direction to be set, it has to be between 0x0 and 0x1.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetPinDirection(Uint32 Pin, Uint32 Value){
    if(Value > 0b1){
        return -1;
    }

    volatile Uint32* RegisterAddress = pinToDirRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1), pinToMaskOneBit(Pin, Value), 1);

    return 0;
}

/**
 * @brief Activates or deactivates the pin pullup resistor.
 * @see GPIO_PULLUP_ENABLE
 * @see GPIO_PULLUP_DISABLE
 * @param Pin The pin number.
 * @param Value The value of the configuration to be set, it has to be between 0x0 and 0x1.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetPinPullUpResistor(Uint32 Pin, Uint32 Value){
    if(Value > 0b1){
        return -1;
    }

    volatile Uint32* RegisterAddress = pinToPullUpResistorRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1), pinToMaskOneBit(Pin, Value), 1);

    return 0;
}

/**
 * @brief Set the pin output state.
 * @see GPIO_HIGH
 * @see GPIO_LOW
 * @param Pin The pin number.
 * @param Value The value of the output state to be set, it has to be between 0x0 and 0x1.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors. 
 */

int GPIOSetValue(Uint32 Pin, Uint32 Value){
    if(Value > 0b1){
        return -1;
    }

    volatile Uint32* RegisterAddress = pinToDataRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1), pinToMaskOneBit(Pin, Value), 1);

    return 0;
}

/**
 * @brief Get the pin state.
 * @see GPIO_HIGH
 * @see GPIO_LOW
 * @param Pin The pin number.
 * @return The pin state.
 */

int GPIOGetValue(Uint32 Pin){
    volatile Uint32* RegisterAddress = pinToDataRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    if(readRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1))){
        return 1;
    }
    else{
        return 0;
    }
}

/**
 * @brief Toggles the pin state.
 * @details If the pin state was GPIO_LOW, it will toogle to GPIO_HIGH and vice versa.
 * @param Pin The pin number.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors. 
 */

int GPIOToggle(Uint32 Pin){
    volatile Uint32* RegisterAddress = pinToToggleRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1), 0xFFFFFFFF, 1);

    return 0;
}

/**
 * @brief Quick general setup of a given pin.
 * @see GPIOSetQualSamplingPeriod(Uint32 Qual, Uint32 Value)
 * @see GPIOSetPinQualificationSelect(Uint32 Pin, Uint32 Value)
 * @see GPIOSetPinMux(Uint32 Pin, Uint32 Value)
 * @see GPIOSetPinDirection(Uint32 Pin, Uint32 Value)
 * @see GPIOSetPinPullUpResistor(Uint32 Pin, Uint32 Value)
 * @param Pin The pin number.
 * @param Peripheral The value of the peripheral to be selected, it has to be between 0x0 and 0x3.
 * @param Direction The value of the direction to be set, it has to be between 0x0 and 0x1.
 * @param PullUpResistor The value of the configuration to be set, it has to be between 0x0 and 0x1.
 * @param QualSelect The value to set, it has to be between 0x0 and 0x3.
 * @param SamplingPeriod The value of the sampling period, it has to be between 0x00 and 0xFF.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.
 */

int GPIOSetup(Uint32 Pin, Uint32 Peripheral, Uint32 Direction, Uint32 PullUpResistor, Uint32 QualSelect, Uint32 SamplingPeriod){
    int error = 0;
    Uint32 Qual = pinToQual(Pin);

    error = GPIOSetPinMux(Pin, Peripheral);
    if(error){
        return -1;
    }

    error = GPIOSetPinDirection(Pin, Direction);
    if(error){
        return -1;
    }

    error = GPIOSetPinPullUpResistor(Pin, PullUpResistor);
    if(error){
        return -1;
    }

    error = GPIOSetPinQualificationSelect(Pin, QualSelect);
    if(error){
        return -1;
    }

    error = GPIOSetQualSamplingPeriod(Qual, SamplingPeriod);
    if(error){
        return -1;
    }

    return 0;
}

/**
 * @brief Quick setup of a simple input/output pin
 * @details This function configures a simple input/output pin with the following assumptions:
 *  - It uses the first peripheral (GPIO).
 *  - It disables the pull up resistor.
 *  - It syncronizes with SYSCLKOUT.
 *  - It has a sampling qualification period of one period of SYSCLKOUT.
 * 
 * @see GPIOSetPinDirection(Uint32 Pin, Uint32 Value)
 * @param Pin The pin number.
 * @param Direction The value of the direction to be set, it has to be between 0x0 and 0x1.
 * @return The exit code, if it returns 0, the function terminated succesfully, if instead returns -1 the function terminated with errors.  
 */

int GPIOSetupSimple(Uint32 Pin, Uint32 Direction){
    return GPIOSetup(Pin, GPIO_PERIPHERAL_0, Direction, GPIO_PULLUP_DISABLE, GPIO_QUALSEL_SYNC, 0);
}

#endif /* UTILS_GPIO_H_ */
