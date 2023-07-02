/*
 * Copyright (C) 2020 Hendrik van Essen
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "Arduino.h"
#include "PCA9632.h"

#define RGB_ADDRESS (0x62)

PCA9632 pca9632;

void setup() {
    Serial.begin(115200);
    pca9632.begin();
    pca9632.setColor(255, 255, 255);
}

void loop() {

    delay(1000);

    // 1. individual dimming (setColor() uses setPwm() internally)
    pca9632.setColor(255, 255, 255);
    delay(500);

    pca9632.setColor(255, 0, 0);
    delay(500);

    pca9632.setColor(0, 255, 0);
    delay(500);

    pca9632.setColor(0, 0, 255);
    delay(500);

    // 2. group dimming
    pca9632.setColor(255, 255, 255);
    pca9632.setLdrStateAll(LDR_STATE_IND_GRP);

    for (int pwm = 255; pwm >= 0; pwm--) {
        pca9632.setCurrent(pwm);
        delay(20);
    }
    delay(1000);

    // 3. changing ldr state
    pca9632.setCurrent(32);
    pca9632.setColor(255, 255, 255);
    pca9632.setLdrState(LDR_STATE_OFF, BIT_LDR1);
    // color should be magenta
    delay(500);

    pca9632.setCurrent(0);
    pca9632.setColor(0, 0, 0);
    pca9632.setLdrState(LDR_STATE_ON, BIT_LDR1);
    // color should be green
    delay(500);

    pca9632.setCurrent(255);
    pca9632.setColor(255, 128, 0);
    pca9632.setLdrState(LDR_STATE_IND, BIT_LDR1);
    // color should be orange
    delay(500);

    pca9632.setCurrent(0);
    pca9632.setColor(255, 255, 255);
    pca9632.setLdrState(LDR_STATE_IND_GRP, BIT_LDR1);
    // should be no color at all
    delay(500);

    // 4. test blinking
    pca9632.setCurrent(255);
    pca9632.setColor(255, 255, 255);
    pca9632.setGroupControlMode(GROUP_CONTROL_MODE_BLINKING);
    pca9632.setBlinking(BLINKING_PERIOD_1_S, BLINKING_RATIO_BALANCED);
    delay(10000);
    pca9632.setGroupControlMode(GROUP_CONTROL_MODE_DIMMING);
