# PCA9632 driver for Arduino

This library was developed and tested on an STM32F411 with a PCA9632DP1 controller,
but should work for every other board as well.


## API overview:
```cpp
    /**
     * Constructor for PCA9632.
     */
    PCA9632();

    /**
     * Initialization.
     */
    void begin();

    /**
     * Set individual PWM signal for a given channel.
     */
    void setPwm(uint8_t regPwm, uint8_t pwm);

    /**
     * Set group brightness PWM for all channels. Accepts 32 values 0x00:0x1F.
     */
    void setCurrent(uint8_t pwm);

    /**
     * Set up values for blinking mode. Blinking mode needs to be activated
     * manually by calling setGroupControlMode(GROUP_CONTROL_MODE_BLINKING).
     *
     * @param blinkPeriod   Period for one blink (turning off and on)
     * @param onOffRatio    Value between 0.0 and 1.0, where e.g. a value of
     *                      0.25 means 1/4 of the time the LEDs are on and
     *                      3/4 of the time the LEDs are off
     */
    void setBlinking(uint8_t blinkPeriod, float onOffRatio);

    /**
    * Set PWM values for Color.
    */
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    /**
    * Set PWM values for Red.
    */
    void setRed(uint8_t r);

    /**
    * Set PWM values for Green.
    */
    void setGreen(uint8_t g);

    /**
    * Set PWM values for Blue.
    */
    void setBlue(uint8_t b);

    /**
    * Set PWM values for White.
    */
    void setWhite(uint8_t w);

    /**
    * Set PWM values for RGBW.
    */
    void setRGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    /**
    * Set the global driver output type for a given channel. There are two types:
    *   - OUTDRV_OPEN_DRAIN
    *   - OUTDRV_TOTEM_POLE
    */
    void setDrvState(uint8_t state);

    /**
    * Set the LED driver output state for a given channel. There are four states:
    *   - LDR_STATE_OFF
    *   - LDR_STATE_ON
    *   - LDR_STATE_IND
    *   - LDR_STATE_IND_GRP
    *
    * @param ldrBit Lower bit of LDR* (see BIT_LDR*)
    */
    void setLdrState(uint8_t state, uint8_t ldrBit);

    /**
    * Set the LED driver output state for all channels. There are four states:
    *   - LDR_STATE_OFF
    *   - LDR_STATE_ON
    *   - LDR_STATE_IND
    *   - LDR_STATE_IND_GRP
    */
    void setLdrStateAll(uint8_t state);

    /**
    * Set an option for auto increment. There are five options:
    *   - AI_DISABLED
    *   - AI_ALL
    *   - AI_IND
    *   - AI_GBL
    *   - AI_IND_GBL
    */
    void setAutoIncrement(uint8_t option);

    /**
    * Set the group control mode. There are two modes:
    *   - GROUP_CONTROL_MODE_BLINKING
    *   - GROUP_CONTROL_MODE_DIMMING
    */
    void setGroupControlMode(uint8_t mode);
```

There is an application called `ApiExample` in `examples`, where you can have a
look how the API works and how it's intended to be used.
