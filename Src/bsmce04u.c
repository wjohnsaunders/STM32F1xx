/*

  bsmce04u.c - driver code for STM32F103RC ARM processors

  Part of grblHAL

  Copyright (c) 2021 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "driver.h"

void post_usb_init (void)
{
    GPIO_InitTypeDef GPIO_Init = {
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Pin = 1 << USB_ENABLE_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP
    };
    HAL_GPIO_Init(USB_ENABLE_PORT, &GPIO_Init);

    BITBAND_PERI(USB_ENABLE_PORT->ODR, USB_ENABLE_PIN) = USB_ENABLE_STATE;
}
