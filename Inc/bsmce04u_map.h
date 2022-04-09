/*
  bsmce04u_map.h - driver code for STM32F103RC ARM processors

  Part of grblHAL

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

#if N_ABC_MOTORS > 1 || N_GANGED
#error "Axis configuration is not supported!"
#endif

#if N_AXIS == 4
#define BOARD_NAME "Bitsensor BSMCE04U-PP 4-axis"
#else
#define BOARD_NAME "Bitsensor BSMCE04U-PP"
#endif
#define BOARD_INFO "STM32F103RC"

#define BOARD_END_OF_FLASH      0x8003FFFF

// USB speed detect resistor needs GPIO driven low
#define HAS_POST_USB_INIT
#define USB_ENABLE_PORT         GPIOC
#define USB_ENABLE_PIN          11
#define USB_ENABLE_STATE        0

#define HAS_BOARD_INIT
#define HC541_ENABLE_PORT       GPIOB
#define HC541_ENABLE_PIN        10

// Flash LED to show running.
#define BLINK_LED_PORT          GPIOC
#define BLINK_LED_PIN           2

// Define step pulse output pins.
#define X_STEP_PORT             GPIOB
#define X_STEP_PIN              1
#define Y_STEP_PORT             GPIOC
#define Y_STEP_PIN              5
#define Z_STEP_PORT             GPIOA
#define Z_STEP_PIN              7
#define STEP_OUTMODE            GPIO_BITBAND

// Define step direction output pins.
#define X_DIRECTION_PORT        GPIOB
#define X_DIRECTION_PIN         0
#define Y_DIRECTION_PORT        GPIOC
#define Y_DIRECTION_PIN         4
#define Z_DIRECTION_PORT        GPIOA
#define Z_DIRECTION_PIN         6
#define DIRECTION_OUTMODE       GPIO_BITBAND

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS == 1
#define M3_AVAILABLE
#define M3_STEP_PORT            GPIOA
#define M3_STEP_PIN             5
#define M3_DIRECTION_PORT       GPIOA
#define M3_DIRECTION_PIN        3
#endif

// Define stepper driver enable/disable output pin.
#if N_ABC_MOTORS == 0
#define STEPPERS_ENABLE_PORT    GPIOA
#define STEPPERS_ENABLE_PIN     3       // Use AD for stepper enable in 3-axis mode
#endif

// Define homing/hard limit switch input pins.
// IN1 PB12 (used for X limit)
// IN2 PB13 (used for Y limit)
// IN3 PB14 (used for Z limit)
// IN4 PB15 (used for probe - compatible with Mach3 usage)
#define LIMIT_PORT              GPIOB
#define X_LIMIT_PIN             12
#define Y_LIMIT_PIN             13
#define Z_LIMIT_PIN             14
#define LIMIT_INMODE            GPIO_SHIFT12

// Define probe switch input pin.
#define PROBE_PORT              GPIOB
#define PROBE_PIN               15

// Define spindle enable and spindle direction output pins.
// OUT1 PC6 (use for spindle direction)
// OUT2 PC7 (use for spindle start/stop - compatible with Mach3 usage)
// OUT3 PC8 (use for coolant flood)
// OUT4 PC9 (use for coolant mist)
#define SPINDLE_ENABLE_PORT     GPIOC
#define SPINDLE_ENABLE_PIN      7
#define SPINDLE_DIRECTION_PORT  GPIOC
#define SPINDLE_DIRECTION_PIN   6

// Define spindle PWM output pin.
#define SPINDLE_PWM_PORT        GPIOA
#define SPINDLE_PWM_PIN         8

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PORT      GPIOC
#define COOLANT_FLOOD_PIN       8
#define COOLANT_MIST_PORT       GPIOC
#define COOLANT_MIST_PIN        9

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define CONTROL_PORT            GPIOB
#define FEED_HOLD_PIN           8       // X+ button on simple pendant
#define CYCLE_START_PIN         9       // X- button on simple pendant
#define RESET_PORT              GPIOC
#define RESET_PIN               10      // unconnected pin - so no reset functionality
#ifdef ENABLE_SAFETY_DOOR_INPUT_PIN
#define SAFETY_DOOR_PORT        GPIO?
#define SAFETY_DOOR_PIN         ?
#endif
#define CONTROL_INMODE          GPIO_BITBAND

/**/
