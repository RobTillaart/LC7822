
[![Arduino CI](https://github.com/RobTillaart/LC7822/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/LC7822/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/LC7822.svg)](https://github.com/RobTillaart/LC7822/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/LC7822/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/LC7822.svg?maxAge=3600)](https://github.com/RobTillaart/LC7822/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/LC7822.svg)](https://registry.platformio.org/libraries/robtillaart/LC7822)


# LC7822

Arduino library for the LC7822 8 channel analogue switch.


## Description

**Experimental**

This library is to use the LC7821/22/23 with an Arduino.

The LC782X series are typical used in audio applications as every
switch is implemented twice a.k.a. stereo.

The library allows to set the switches individually or set all 
switches in one call. 
Furthermore the library caches the current state of the switches. 
This allows to read back the state of the switches either as a
bit mask or read them individually (from cache).

The library has derived classes for the LC7821 and LC7823 as 
these are pretty similar in how to control them. 
The difference is the address used, and the internal setup of the switches. 
Check the datasheet for the details.

The library is not tested with hardware yet.

Note the LC782x devices are relative old and may seem obsolete,
however they are still available online.

Feedback, as always, is welcome.


### Mode operandi

The library has two modi operandi. 

The first mode operandi is if the **sPin** has a hardwired connection, 
meaning the device has a hard coded / wired address. 
Then the sPin does not need to be set in the constructor (or set to 255).
The user must set the address in the **begin(address)** call so
the device uses the correct address to communicate.
This mode is used if the library needs to control only one device,
or two devices that share the data, clock and ce pins.
See example **LC7822_two_device.ino**

The second mode operandi is used when there are more than two
devices that share the data, clock and ce pins. Every device needs 
to have an unique **sPin** which works as a select pin as it changes
the active address of the device. See section about address below.
By setting all **sPins** to LOW and only one to HIGH one of the devices 
is selected. 
In this scenario the **begin()** function must be called **without** 
an address. The library takes care of the addressing.
See example **LC7822_multi.ino**


### Notes about hardware

The LC7822 et al, can work with relative high voltages, up to 20Volts.
They can be controlled directly with an Arduino as 5V is within specification.
However it is adviced to add an appropriate optocoupler and invertor
when voltages above the 5V are used with this device.

Be sure to read the datasheet.


### Addresses

|   Type   |  S  |  A0  |  A1  |  A2  |  A3  |  DEC  |   HEX  |
|:--------:|:---:|:----:|:----:|:----:|:----:|:-----:|:------:|
|  LC7821  |  L  |  0   |  1   |  0   |  1   |    5  |  0x05  |
|  LC7821  |  H  |  1   |  1   |  0   |  1   |   13  |  0x0D  |
|  LC7822  |  L  |  0   |  0   |  1   |  1   |    3  |  0x03  |
|  LC7822  |  H  |  1   |  0   |  1   |  1   |   11  |  0x0B  |
|  LC7823  |  L  |  0   |  1   |  1   |  1   |    7  |  0x07  |
|  LC7823  |  H  |  1   |  1   |  1   |  1   |   15  |  0x0F  |


### Details switches LC7821

The LC7821 has three Left Commons (LCOMx) and three Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.

LCOM1 can be connected to L1, L2, L3 and L4.  
LCOM2 can be connected to L5 and L6.  
LCOM3 can be connected to L7 and L8.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |   X  |   X  |      |      |      |      |
|  LCOM2   |      |      |      |      |   X  |   X  |      |      |
|  LCOM3   |      |      |      |      |      |      |   X  |   X  |


### Details switches LC7822

The LC7822 has three Left Commons (LCOMx) and three Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.

LCOM1 can be connected to L1, L2 and L3.  
LCOM2 can be connected to L4, L5 and L6.  
LCOM3 can be connected to L7 and L8.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |   X  |      |      |      |      |      |
|  LCOM2   |      |      |      |   X  |   X  |   X  |      |      |
|  LCOM3   |      |      |      |      |      |      |   X  |   X  |


### Details switches LC7823

The LC7823 has four Left Commons (LCOMx) and four Right Commons (RCOMx).
These are symmetrical and are switched simultaneously.
Note: it has only 7 switches.

LCOM1 can be connected to L1 and L2.  
LCOM2 can be connected to L3 and L4.  
LCOM3 can be connected to L5 and L6.  
LCOM4 can be connected to L7.  
Note: L8 is not used.  

|  COMMON  |  L1  |  L2  |  L3  |  L4  |  L5  |  L6  |  L7  |  L8  |
|:--------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|  LCOM1   |   X  |   X  |      |      |      |      |      |      |
|  LCOM2   |      |      |   X  |   X  |      |      |      |      |
|  LCOM3   |      |      |      |      |   X  |   X  |      |      |
|  LCOM4   |      |      |      |      |      |      |   X  |      |


### Related

Thread that triggered the development of the library.

- https://forum.arduino.cc/t/legacy-analogue-switch-controll-serial-commands/1419824/125

Datasheet

- https://www.haje.nl/pub/pdf/electronica/halfgeleiders/lc7821_lc7822_lc7823.pdf
- https://www.haje.nl/product_info.php/products_id/22222  (LC7821)


## Interface LC7822

```cpp
#include "LC7822.h"
```

### Constructor

- **LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin = 255, uint8_t resetPin = 255)** Constructor, set pins needed.
- **bool begin(uint8_t address = 0x0B)** Initializes the IO pins, sets the address (0x0B or 0x03)
- **bool reset()** resets the device, returns false if reset Pin is not defined.
- **uint8_t getAddress()** returns cached address (debugging).


### Switches

- **bool setAll(uint8_t value)** mask to set all switches in one call.
- **uint8_t getAll()** get bit mask of all swicthes.
- **bool setSwitch(uint8_t sw, bool val)** set one switch.
- **bool getSwitch(uint8_t sw)** get state of single switch.


### Tune timing

- **void setMicroDelay(uint8_t udel)** set pulse delay.
- **uint8_t getMicroDelay()** return set value


## Interface LC7821

- **bool begin(uint8_t address = 0x0D)** Initializes the IO pins, sets the address, only 0x0D or 0x05 are valid.


## Interface LC7823

- **bool begin(uint8_t address = 0x0F)** Initializes the IO pins, sets the address, only 0x0F or 0x07 are valid.


## Reset



## Future

#### Must

- improve documentation
- get hardware to test
- test reset() polarity.

#### Should

- add examples
  - performance sketch
  - array sketch

#### Could

- add error handling
- add defaults for some parameters?
- check address ranges (how for all)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


