/*
 * Utils_GPIO.h
 *
 *  Created on: 21/11/2023
 *      Author: Emmanuel
 */

#ifndef UTILS_GPIO_H_
#define UTILS_GPIO_H_

#include "DSP28x_Project.h"
#include "Utils_Registers.h"

#define GPIO_HIGH 1
#define GPIO_LOW 0
#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_PULLUP_ENABLE 0
#define GPIO_PULLUP_DISABLE 1
#define GPIO_PERIPHERAL_0 0
#define GPIO_PERIPHERAL_1 1
#define GPIO_PERIPHERAL_2 2
#define GPIO_PERIPHERAL_3 3
#define GPIO_QUALSEL_SYNC 0
#define GPIO_QUALSEL_3SAMPLES 1
#define GPIO_QUALSEL_6SAMPLES 2
#define GPIO_QUALSEL_ASYNC 3

#define pinToMux(pin) ((Uint32) pin/16)
#define pinToQual(pin) ((Uint32) pin/8)
#define pinToMaskOneBit(pin, value) ((Uint32) (value << (pin % 32)))
#define pinToMaskTwoBits(pin, value) ((Uint32) (value << (pin % 16)*2))
#define qualToMaskFourBits(qual, value) ((Uint32) (value << (qual % 4)*8))

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



int GPIOSetQualSamplingPeriod(Uint32 Qual, Uint32 Value){
    if(Value > 0xFF) return -1;

    volatile Uint32* RegisterAddress = qualToCtrlRegister(Qual);
    if(RegisterAddress == 0) return -1;

    writeRegister(RegisterAddress, qualToMaskFourBits(Qual, 0xFF), qualToMaskFourBits(Qual, Value), 1);

    return 0;
}

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

int GPIOToggle(Uint32 Pin){
    volatile Uint32* RegisterAddress = pinToToggleRegister(Pin);
    if(RegisterAddress == 0){
        return -1;
    }

    writeRegister(RegisterAddress, pinToMaskOneBit(Pin, 0b1), 0xFFFFFFFF, 1);

    return 0;
}

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

int GPIOSetupSimple(Uint32 Pin, Uint32 Direction){
    return GPIOSetup(Pin, GPIO_PERIPHERAL_0, Direction, GPIO_PULLUP_DISABLE, GPIO_QUALSEL_SYNC, 0);
}

#endif /* UTILS_GPIO_H_ */
