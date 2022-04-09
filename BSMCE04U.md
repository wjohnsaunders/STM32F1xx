# Converting Bitsensor BSMCE04U montion board to grblHAL

## Board Overview

![BSMCE04U board](/bsmce04u/BSMCE04U_board.jpg "BSMCE04U board")

Top left the board has 4 opto-isolated outputs feeding a ULN2003A chip. This chip can sink enough current to the ground (DCM connection) to directly drive relays. The outputs required a 24V source (24V connection) to operate.

Top center the board has 4 opto-isolated inputs. When the input is shorted to ground, the LED in the opto-isolator is turned on and the input activates. The inputs require a 24V source to operate.

Top right the board contains the PWN driven analogue spindle speed control. The AVI connection is connected to 10V, and ACM connection is connected to ground, from the VFD controller. PWM is then used to create a voltage between 0V and 10V on the 10V connection top the VFD controller.

Center right is a HC541 octal buffer that is used to drive 5V compatible signals for stepper drivers. The is also a 5V and GND connections to be used for the stepper controllers. The board supports 4 axis.

The connector on the bottom right is for a simple 8 button pendant, which is not supported in grblHAL. However pins 3 and 4 can be used to operate the hold and cycle start functions.

Bottom center is the microcontroller, STM32F103RC, running at 72MHz from an 8MHz crystal.There is also a red LED that will flash with grblHAL is functional.

Bottom left is the 3.3V voltage regulator and USB connector.

## grblHAL Input/Output Function Assignment

grblHAL requires functionality to be assigned specific inputs and outputs. I have tried to closly match recommendations for wiring of the board.

### Inputs

IN1 is assigned for an X limit switch

IN2 is assigned for an Y limit switch

IN3 is assigned for an Z limit switch

IN4 is assigned for a probe

### Outputs

OUT1 is assigned to control spindle direction

OUT2 is assigned to control spindle start/stop

OUT3 is assigned to control flood coolant

OUT4 is assigned to control mist coolant

### Stepper Control

The direction and pulse pins work as expected. However there is the option of compiling the code for 3 axis mode. In that case the AD output has been re-assigned as the stepper driver enable signal, and the AP output is not functional at this time.

## Programming the board with a JTAG probe

Between the micro and the USB connector you will notice 2 test points on the board. Luckily these make the SWDIO and SWCLK pins available, and allow us to re-program the board. The other signals required for SWD are ground and target voltage, which are available from the 3.3V LDO voltage regulator.

### Hardware SWD Connection

Using a fine tip soldering iron, apply some flux and then apply some solder to each of the points (you may use flux core solder instead). Next tin the ends of the wires, and finally solder them to the appropriate points. Try to do this quickly to limit the amount of heat applied to the board.

Use a zip-tie to provide some strain relief to the wires, as the test-point pads can easily be damaged.

![BSMCE04U solder SWD connections](/bsmce04u/BSMCE04U_SWD_solder.jpg "BSMCE04U solder SWD connections")

Finally you need to connect the SWD signals to a JTAG probe.

Referring to the following picture, the target voltage is on pin 1, then there are 2 unused pins before SWDIO and SWCLK. The ground signal is on pin 4, which is the second pin along the bottom row.

For other probes with the standard 20-pin IDC connector, reference the connector notch which should be near tge SWCLK signal. For probes that don't use 20-pin IDC, refer to the manual for the location of the necessary signals.

![JTAG device SWD connections](/bsmce04u/BSMCE04U_SWD_connections.jpg "JTAG device SWD connections")

### Copmpiling

Select the "Release F103RC" configuration and build the software by pressing the build button (hammer icon). Press the run button (play icon) which will connect to the JTAG probe and upload the software to the device. The red LED should start flashing if it was successful.

Note: As supplied the microcontroller is in a locked state. This is a form of copy protection to prevent reading the existing firmware from the card. The first time you connect the probe, you will need to use the probe utility to perform a complete chip erase. This erase will completely remove the existing firmware and unlock the device. You will no longer be able to use the board with Mach3 after this step. However it will now be ready to take the new grblHAL firmware.

## Design Information

### Microcontroller Information

STM32F103RCT6 in LQFP64 package. It contains 256K of FLASH and 48K of SRAM. It is using an 8MHz crystal for the high speed external clock.

### Pin Assignments

#### External Connectors

| Pin | Connection |
| -- | -- |
| PC6 | OUT1 |
| PC7 | OUT2 |
| PC8 | OUT3 |
| PC9 | OUT4 |
| PB12 | IN1 |
| PB13 | IN2 |
| PB14 | IN3 |
| PB15 | IN4 |
| PB0 | XD |
| PB1 | XP |
| PC4 | YD |
| PC5 | YP |
| PA6 | ZD |
| PA7 | ZP |
| PA3 | AD |
| PA5 | AP |
| PA8 | 10V (PWM) |

#### Expansion Connector

| Connector | Pin  | Function |
| --------- | ---- | -------- |
| Pin 1     | –    | 5V       |
| Pin 2     | –    | GND      |
| Pin 3     | PB8  | X+ button on pendant |
| Pin 4     | PB9  | X- button on pendant |
| Pin 5     | PB6  | Y+ button on pendant |
| Pin 6     | PB7  | Y- button on pendant |
| Pin 7     | PB4  | Z+ button on pendant |
| Pin 8     | PB3  | Z- button on pendant |
| Pin 9     | PD2  | A+ button on pendant |
| Pin 10    | PC12 | A- button on pendant |

#### Internal Functions

| Pin | Connection |
| -- | -- |
| PC2 | LED (active high) |
| PC11 | USB ID resistor (active low) |
| PB10 | HC541 gate (active low) |
