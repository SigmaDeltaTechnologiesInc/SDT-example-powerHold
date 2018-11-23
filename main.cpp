/* SDT-example-pmic-led
 * 
 * Copyright (c) 2018 Sigma Delta Technologies Inc.
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"
#include "MAX77650.h"

/* Serial */
#define BAUDRATE        9600
Serial serial_pc(USBTX, USBRX, BAUDRATE);

/* DigitalOut */
#define LED_ON          0
#define LED_OFF         1
DigitalOut do_ledBlue(LED_BLUE, LED_OFF);
DigitalOut do_max77650_PHLD(UART1_CTS, 1);        // pin 바꿔야됨

/* PMIC(MAX77650) */
I2C i2c_pmic(I2C2_SDA, I2C2_SCL);
MAX77650 max77650(i2c_pmic);        // hold pin input 가능



int main(void)
{
    serial_pc.printf("< Sigma Delta Technologies Inc. >\n\r");

    do_max77650_PHLD = 1;

    // Prepare the PMIC LEDs
    max77650.setLED0_FS(1);          // 0 ~ 3
    max77650.setLED0_INV(0);         // 0 ~ 1
    max77650.setLED0_BRT(0);         // 0 ~ 31
    max77650.setLED0_Period(15);     // 0 ~ 15
    max77650.setLED0_Duty(15);       // 0 ~ 15

    max77650.setLED1_FS(1);          // 0 ~ 3
    max77650.setLED1_INV(0);         // 0 ~ 1
    max77650.setLED1_BRT(0);         // 0 ~ 31
    max77650.setLED1_Period(15);     // 0 ~ 15
    max77650.setLED1_Duty(15);       // 0 ~ 15

    max77650.setLED2_FS(1);          // 0 ~ 3
    max77650.setLED2_INV(0);         // 0 ~ 1
    max77650.setLED2_BRT(0);         // 0 ~ 31
    max77650.setLED2_Period(15);     // 0 ~ 15
    max77650.setLED2_Duty(15);       // 0 ~ 15

    max77650.setLED_MSTR(1);          // 0 ~ 1

    int i = 0;
    while(true) {
        serial_pc.printf("LED Toggle\n");
        do_ledBlue = !do_ledBlue;
        wait(1);                // 1sec

        // Cycle MAX32620FTHR LED's
        for(i=0; i<32; i++) {
            max77650.setLED0_BRT(i);
            max77650.setLED1_BRT(0);
            max77650.setLED2_BRT(0);
            wait(0.05);
        }

        for(i=0; i<32; i++) {
            max77650.setLED0_BRT(0);
            max77650.setLED1_BRT(i);
            max77650.setLED2_BRT(0);
            wait(0.05);
        }

        for(i=0; i<32; i++) {
            max77650.setLED0_BRT(0);
            max77650.setLED1_BRT(0);
            max77650.setLED2_BRT(i);
            wait(0.05);
        }

        do_max77650_PHLD = 0;
    }
}
