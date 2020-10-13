# l_rr - usefull stuff for embedded
A bunch of usefull stuff for embedded projects. Although there is no requirements for any particular hardware (in most cases), it has been tested mostly on stm32.

The pack contains several nice implementations that can be taken and adopted to almost any embedded project.

## Features

* A driver for EEPROM 24LC256. Can be used for other chips from this family (though untested).

* EEPROM emulator for stm32f103

* A driver for HD44780 device (16x2 LCD alphanumeric display)

* Temperature sensors: lm35, KTY8x, NTC10k

* Math utils (linear interpolation, error correction)

* USART logger

* Test harness for stm32f103. Can be used to test embedded code on x86.

## Notes

* Under development. New modules come when needed.

* No backward compatibility guaranteed.

* The leading target is the stm32 family.

## License

Copyright (c) 2020 Rafal Rowniak rrowniak.com
