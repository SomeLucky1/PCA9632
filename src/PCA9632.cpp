#include "Arduino.h"

#include "PCA9632.h"

/******************************* PUBLIC METHODS *******************************/
PCA9632::PCA9632() {
    
    _regRedPwm = REG_PWM0;
    _regGreenPwm = REG_PWM1;
    _regBluePwm = REG_PWM2;
    _regWhitePwm = REG_PWM3;
}

void PCA9632::begin() {

    _deviceAddres = RGB_ADDRESS;

    _wire = &Wire;
    _wire->begin();

    // clear/ reset registers
    writeReg(REG_MODE1, 0x0);
    writeReg(REG_MODE2, 0x0);
    // set default states
    setLdrStateAll(LDR_STATE_IND_GRP);
    setGroupControlMode(GROUP_CONTROL_MODE_DIMMING);
}

void PCA9632::setPwm(uint8_t regPwm, uint8_t pwm) {

    writeReg(regPwm, pwm);
}

void PCA9632::setCurrent(uint8_t pwm) {
// Values between 0x00:0x1F are shifted to 0x00:0xF0.  Only the 4 MSB are used. 
    writeReg(REG_GRPPWM, pwm<<3);
}

void PCA9632::setBlinking(uint8_t blinkPeriod, float onOffRatio) {

    int16_t ratio = onOffRatio * 256;

    if (ratio < 0) {
        ratio = 0;
    }
    else if (ratio > 255) {
        ratio = 255;
    }

    writeReg(REG_GRPFREQ, blinkPeriod);
    writeReg(REG_GRPPWM, (uint8_t) ratio);
}

void PCA9632::setColor(uint8_t r, uint8_t g, uint8_t b) {

        setRed(r);
        setGreen(g);
        setBlue(b);
}

void PCA9632::setRed(uint8_t r) {
    setPwm(_regRedPwm, r);
}

void PCA9632::setGreen(uint8_t g) {
    setPwm(_regGreenPwm, g);
}

void PCA9632::setBlue(uint8_t b) {
    setPwm(_regBluePwm, b);
}

void PCA9632::setWhite(uint8_t w) {
    setPwm(_regWhitePwm, w);
}

void PCA9632::setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {

    setColor(r, g, b);
    setPwm(_regWhitePwm, w);
}

void PCA9632::setLdrState(uint8_t state, uint8_t ldrBit) {

    uint8_t prevReg = readReg(REG_LEDOUT);
    uint8_t newReg;

    // first clear both bits of ldr
    newReg = prevReg & ~(0b11 << ldrBit);

    // second set new state to specified ldr
    newReg |= (state << ldrBit);

    writeReg(REG_LEDOUT, newReg);
}

void PCA9632::setLdrStateAll(uint8_t state) {

    uint8_t newReg = ( state << BIT_LDR3
                       | state << BIT_LDR2
                       | state << BIT_LDR1
                       | state << BIT_LDR0 );

    writeReg(REG_LEDOUT, newReg);
}

void PCA9632::setDrvState(uint8_t state) {

    uint8_t prevReg = readReg(REG_MODE2);
    uint8_t newReg;

    // first clear the OUTDRV bit
    newReg = prevReg & ~(1 << BIT_OUTDRV);

    // second set new state to specified drv
    newReg |= (state << BIT_OUTDRV);

    writeReg(REG_MODE2, newReg);
}

void PCA9632::setAutoIncrement(uint8_t option) {

    uint8_t newReg;

    switch (option) {

        case AI_ALL:
            newReg = (1 << BIT_AI2)
                   | (0 << BIT_AI1)
                   | (0 << BIT_AI0);
            break;

        case AI_IND:
            newReg = (1 << BIT_AI2)
                   | (1 << BIT_AI1)
                   | (0 << BIT_AI0);
            break;

        case AI_GBL:
            newReg = (1 << BIT_AI2)
                   | (0 << BIT_AI1)
                   | (1 << BIT_AI0);
            break;

        case AI_IND_GBL:
            newReg = (1 << BIT_AI2)
                   | (1 << BIT_AI1)
                   | (1 << BIT_AI0);
            break;

        case AI_DISABLED:
        default:
            newReg = (0 << BIT_AI2)
                   | (0 << BIT_AI1)
                   | (0 << BIT_AI0);
            break;
    }

    writeReg(REG_MODE1, newReg);
}

void PCA9632::setGroupControlMode(uint8_t mode) {

    uint8_t prevReg = readReg(REG_MODE2);

    switch (mode) {

        case GROUP_CONTROL_MODE_BLINKING:
            writeReg(REG_MODE2, prevReg | (1 << BIT_DMBLNK));
            break;

        case GROUP_CONTROL_MODE_DIMMING:
        default:
            writeReg(REG_MODE2, prevReg & ~(1 << BIT_DMBLNK));
            break;
    }
}

/****************************** PRIVATE METHODS *******************************/

void PCA9632::writeReg(uint8_t registerAddress, uint8_t data) {

    _wire->beginTransmission(_deviceAddres);
    _wire->write(registerAddress);
    _wire->write(data);
    _wire->endTransmission();
}

uint8_t PCA9632::readReg(uint8_t registerAddress) {

    _wire->beginTransmission(_deviceAddres);
    _wire->write(registerAddress);
    _wire->endTransmission();

    _wire->requestFrom(_deviceAddres, (uint8_t) 1);

    if (_wire->available() == 1) {
        return _wire->read();
    }

    return -1;
}
