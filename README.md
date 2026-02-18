# Soldered BMV080 Arduino library

[![Make docs and publish to GitHub Pages](https://github.com/SolderedElectronics/Soldered-BMV080-Arduino-Library/actions/workflows/make_docs.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-BMV080-Arduino-Library/actions/workflows/make_docs.yml)
[![Arduino Library Manager Compatibility](https://github.com/SolderedElectronics/Soldered-BMV080-Arduino-Library/actions/workflows/arduino_lint.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-BMV080-Arduino-Library/actions/workflows/arduino_lint.yml)

| ![Soldered BMV080 Particulate Matter Sensor Breakout](https://upload.wikimedia.org/wikipedia/commons/8/8f/Example_image.svg) |
| :------------------------------------------------------------------------------------: |
|                      [Soldered BMV080 Particulate Matter Sensor Breakout](https://www.solde.red/333373)                      |

## Product Overview

The BMV080 is an ultra-compact particulate matter (PM) sensor from Bosch Sensortec that measures air quality by detecting PM1, PM2.5, and PM10 particles. This sensor uses innovative laser-based technology with integrated photodiodes to measure particle concentrations directly in free space, without requiring an intrusive fan.

**Key Features:**
- **Ultra-small form factor**: Measures merely 4.2mm x 3.5mm x 3.1mm (W x L x H)
- **Fan-less design**: No moving parts, making it ideal for battery-powered applications
- **Multi-size particle detection**: Measures PM1, PM2.5, and PM10 concentrations
- **I2C interface**: Simple communication via standard I2C protocol
- **Obstruction detection**: Built-in detection for sensor blockage
- **Configurable measurement modes**: Continuous or duty-cycled operation

This Arduino library provides an easy-to-use interface for the BMV080 sensor, allowing you to read air quality data, configure sensor parameters, and monitor sensor status with just a few simple function calls.

# ⚠️Important note!

This library relies on the Bosch BMV080 SDK, which isn't included in the library. To properly use this library it is needed to download the Bosch SDK available [here](https://www.bosch-sensortec.com/software-tools/software/previous-sdk-bmv-080-versions/).

After downloading and extracting the Bosch BMV080 SDK, you need to copy the required header files and precompiled static libraries to the appropriate locations in this library. The static libraries are platform-specific, so you'll need to copy the files for your target platform.

From the Bosch SDK, copy the following files to the specified library locations:

| Bosch SDK File | Soldered BMV080 Arduino Library Directory |
|--|--|
| `api/inc/bmv080.h` | `src/BMV080Wrapper/bmv080.h` |
| `api/inc/bmv080_defs.h` | `src/BMV080Wrapper/bmv080_defs.h` |
| `api/lib/xtensa_esp32/xtensa_esp32_elf_gcc/release/lib_bmv080.a` | `src/esp32/lib_bmv080.a` |
| `api/lib/xtensa_esp32/xtensa_esp32_elf_gcc/release/lib_postProcessor.a` | `src/esp32/lib_postProcessor.a` |
| `api/lib/xtensa_esp32s2/xtensa_esp32s2_elf_gcc/release/lib_bmv080.a` | `src/esp32s2/lib_bmv080.a` |
| `api/lib/xtensa_esp32s2/xtensa_esp32s2_elf_gcc/release/lib_postProcessor.a` | `src/esp32s2/lib_postProcessor.a` |
| `api/lib/xtensa_esp32s3/xtensa_esp32s3_elf_gcc/release/lib_bmv080.a` | `src/esp32s3/lib_bmv080.a` |
| `api/lib/xtensa_esp32s3/xtensa_esp32s3_elf_gcc/release/lib_postProcessor.a` | `src/esp32s3/lib_postProcessor.a` |
| `api/lib/riscv_rv32imc/riscv_none_elf_gcc/release/lib_bmv080.a` | `src/esp32c6/lib_bmv080.a` |
| `api/lib/riscv_rv32imc/riscv_none_elf_gcc/release/lib_postProcessor.a` | `src/esp32c6/lib_postProcessor.a` |
| `api/lib/arm_cortex_m0plus/arm_none_eabi_gcc/release/lib_bmv080.a` | `src/cortex-m0plus/lib_bmv080.a` |
| `api/lib/arm_cortex_m0plus/arm_none_eabi_gcc/release/lib_postProcessor.a` | `src/cortex-m0plus/lib_postProcessor.a` |
| `api/lib/arm_cortex_m33/arm_none_eabi_gcc/release/lib_bmv080.a` | `src/cortex-m33/lib_bmv080.a` |
| `api/lib/arm_cortex_m33/arm_none_eabi_gcc/release/lib_postProcessor.a` | `src/cortex-m33/lib_postProcessor.a` |
| `api/lib/arm_cortex_m4/arm_none_eabi_gcc/release/lib_bmv080.a` | `src/cortex-m4/lib_bmv080.a` |
| `api/lib/arm_cortex_m4/arm_none_eabi_gcc/release/lib_postProcessor.a` | `src/cortex-m4/lib_postProcessor.a` |
| `api/lib/arm_cortex_m4f/arm_none_eabi_gcc/release/lib_bmv080.a` | `src/cortex-m4f/lib_bmv080.a` |
| `api/lib/arm_cortex_m4f/arm_none_eabi_gcc/release/lib_postProcessor.a` | `src/cortex-m4f/lib_postProcessor.a` |


### Repository Contents

- **/src** - source files for the library (.h & .cpp)
- **/examples** - examples for using the library
- **_other_** - _keywords_ file highlights function words in your IDE, _library.properties_ enables implementation with Arduino Library Manager.

### Hardware design

You can find hardware design for this board in the Soldered BMV080 Particulate Matter Sensor Breakout hardware repository.

### Documentation

Access Arduino library documentation [here](https://SolderedElectronics.github.io/Soldered-BMV080-Arduino-Library/).

- Tutorial for using the NAZIV PROIZVODA board
- Installing an Arduino library

### About Soldered

<img src="https://raw.githubusercontent.com/SolderedElectronics/Soldered-BMV080-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Community & Technical support](https://soldered.com/community)

### Original source

​
This library is possible thanks to original [SparkFun Air Quality PM1/PM2.5/PM10 Sensor - BMV080 (Qwiic)](https://github.com/sparkfun/SparkFun_BMV080_Arduino_Library?tab=readme-ov-file) library. Thank you, SparkFun.

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
