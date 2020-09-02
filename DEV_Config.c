/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-02-19
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"

void GPIO_Config(void)
{
    ESP_ERROR_CHECK(gpio_set_direction(EPD_BUSY_PIN,  INPUT));

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL << 26) | (1ULL << 27) | (1ULL << 13) | (1ULL << 14) | (1ULL << 15));
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));


    //gpio_set_direction(EPD_RST_PIN , OUTPUT);
    //gpio_set_direction(EPD_DC_PIN  , OUTPUT);

    //gpio_set_direction(EPD_SCK_PIN, OUTPUT);
    //gpio_set_direction(EPD_MOSI_PIN, OUTPUT);
    //gpio_set_direction(EPD_CS_PIN , OUTPUT);

    DEV_Digital_Write(EPD_CS_PIN , HIGH);
    DEV_Digital_Write(EPD_SCK_PIN, LOW);
}
/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{
	//gpio
	GPIO_Config();

	// spi
	// SPI.setDataMode(SPI_MODE0);
	// SPI.setBitOrder(MSBFIRST);
	// SPI.setClockDivider(SPI_CLOCK_DIV4);
	// SPI.begin();

	return 0;
}

/******************************************************************************
function:
			SPI read and write
******************************************************************************/
void DEV_SPI_WriteByte(UBYTE data)
{
    //SPI.beginTransaction(spi_settings);
    DEV_Digital_Write(EPD_CS_PIN, GPIO_PIN_RESET);

    for (int i = 0; i < 8; i++)
    {
        if ((data & 0x80) == 0) DEV_Digital_Write(EPD_MOSI_PIN, GPIO_PIN_RESET);
        else                    DEV_Digital_Write(EPD_MOSI_PIN, GPIO_PIN_SET);

        data <<= 1;
        DEV_Digital_Write(EPD_SCK_PIN, GPIO_PIN_SET);
        DEV_Digital_Write(EPD_SCK_PIN, GPIO_PIN_RESET);
    }

    //SPI.transfer(data);
    DEV_Digital_Write(EPD_CS_PIN, GPIO_PIN_SET);
    //SPI.endTransaction();
}
