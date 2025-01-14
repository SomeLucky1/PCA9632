#ifndef PCA9632_H
#define PCA9632_H

#define RGB_ADDRESS (0x62)

#include <Wire.h>

// Register definitions (page 11, table 7)
#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_PWM0        0x02
#define REG_PWM1        0x03
#define REG_PWM2        0x04
#define REG_PWM3        0x05
#define REG_GRPPWM      0x06
#define REG_GRPFREQ     0x07
#define REG_LEDOUT      0x08
#define REG_SUBADR1     0x09
#define REG_SUBADR2     0x0A
#define REG_SUBADR3     0x0B
#define REG_ALLCALLADR  0x0C

// Bits in REG_MODE1 (page 12, table 8)
#define BIT_AI2     7
#define BIT_AI1     6
#define BIT_AI0     5
#define BIT_SLEEP   4
#define BIT_SUB1    3
#define BIT_SUB2    2
#define BIT_SUB3    1
#define BIT_ALLCALL 0

// Bits in REG_MODE2 (page 12-13, table 9)
#define BIT_DMBLNK  5
#define BIT_INVRT   4
#define BIT_OCH     3
#define BIT_OUTDRV  2
#define BIT_OUTNE1  1
#define BIT_OUTNE0  0

// Bits in REG_LEDOUT (page 14, table 13)
#define BIT_LDR3    6
#define BIT_LDR2    4
#define BIT_LDR1    2
#define BIT_LDR0    0
#define OUTDRV_OPEN_DRAIN 0
#define OUTDRV_TOTEM_POLE 1
#define LDR_STATE_OFF       0x00
#define LDR_STATE_ON        0x01
#define LDR_STATE_IND       0x02
#define LDR_STATE_IND_GRP   0x03

// Auto-Increment options (page 10, table 6)
#define AI_DISABLED 0
#define AI_ALL      1
#define AI_IND      2
#define AI_GBL      3
#define AI_IND_GBL  4
#define GROUP_CONTROL_MODE_BLINKING 0
#define GROUP_CONTROL_MODE_DIMMING  1

// Frequency of 24 Hz is used
#define BLINKING_PERIOD_125_MS  3   // ((1 / 24 Hz) * 3 cycles)
#define BLINKING_PERIOD_250_MS  6   // ((1 / 24 Hz) * 6 cycles)
#define BLINKING_PERIOD_500_MS  12  // ((1 / 24 Hz) * 12 cycles)
#define BLINKING_PERIOD_1_S     24  // ((1 / 24 Hz) * 24 cycles)
#define BLINKING_PERIOD_MAX     255 // 10.73 s
#define BLINKING_RATIO_BALANCED 0.5

class PCA9632 {

public:
    PCA9632();
    void begin();
    void setPwm(uint8_t regPwm, uint8_t pwm);
    void setCurrent(uint8_t pwm);
    void setBlinking(uint8_t blinkPeriod, float onOffRatio);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setRed(uint8_t r);
    void setGreen(uint8_t g);
    void setBlue(uint8_t b);
    void setWhite(uint8_t w);
    void setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    void setDrvState(uint8_t state);
    void setLdrState(uint8_t state, uint8_t ldrBit);
    void setLdrStateAll(uint8_t state);
    void setAutoIncrement(uint8_t option);
    void setGroupControlMode(uint8_t mode);

private:
    void writeReg(uint8_t registerAddress, uint8_t data);
    uint8_t readReg(uint8_t registerAddress);
    uint8_t _deviceAddres;
    uint8_t _regRedPwm, _regGreenPwm, _regBluePwm, _regWhitePwm;
    uint8_t _storedRegLedout;
    TwoWire *_wire;
};

#endif //PCA9632_H
