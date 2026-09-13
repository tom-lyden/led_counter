# STM32F401RE LED Counter

A small bare-metal STM32F401RE project used to build and validate a minimal embedded software stack without STM32 HAL or Cube-generated startup code.

The application currently drives three external LEDs as a binary counter using a timer based on SysTick.

## Project Goals

This project serves as a test application for:

* Custom STM32F401RE startup code
* Custom linker script
* Custom bare-metal HAL
* SysTick-based timing
* Simple reusable utility modules
* Board-specific hardware definitions
* Reproducible ARM cross-compilation using CMake

## Architecture

The project is split into several layers:

* `src/` — application code
* `include/` — board-specific definitions
* `platform/` — startup code and linker script
* `utils/` — reusable application-independent utilities
* `f401_re_hal` — external bare-metal HAL dependency fetched through CMake

## Platform Layer

The platform layer contains the minimum code required to boot the STM32F401RE without generated startup files.

### Startup

`stm32f4xx_startup.c` provides:

* Cortex-M4 vector table
* Initial stack pointer
* Reset handler
* `.data` initialization from Flash to SRAM
* `.bss` zero initialization
* Default exception handlers using weak aliases

The generated release assembly is checked to ensure the startup initialization loops are not replaced with runtime `memcpy` or `memset` calls.

### Linker Script

`stm32f4xx_flash.ld` defines:

* 512 KB Flash beginning at `0x08000000`
* 96 KB SRAM beginning at `0x20000000`
* `.text`, `.rodata`, `.data`, and `.bss` placement
* `.data` load address in Flash
* stack reservation
* linker-time detection of static RAM / stack overlap

## HAL

The project uses the external [`f401_re_hal`](https://github.com/tom-lyden/f401_re_hal) repository through CMake `FetchContent`.

The current application uses:

* GPIO
* RCC
* SysTick

## Timer Utility

The timer module provides a simple non-blocking timer abstraction based on an injected tick source.

It currently uses `SysTick_GetTick()` but is independent of SysTick itself and can use any compatible tick source.

## Current Application

The current application:

1. Configures SysTick.
2. Configures three GPIO outputs.
3. Uses a non-blocking timer.
4. Displays an incrementing binary counter on three LEDs.

The project has been tested on an STM32 Nucleo-F401RE with external LEDs.

## Build

The project uses:

* CMake
* Ninja
* `arm-none-eabi-gcc`

Shared build presets are provided through `CMakePresets.json`.

The ARM GCC toolchain must be available in the system `PATH`.

## Status

Current milestone:

* [x] Custom linker script
* [x] Custom startup and vector table
* [x] External HAL integration
* [x] SysTick timing
* [x] Non-blocking timer utility
* [x] LED binary counter
* [ ] GPIO button input
* [ ] Button-controlled counter
