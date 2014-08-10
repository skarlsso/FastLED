#ifndef __INC_LED_SYSDEFS_H
#define __INC_LED_SYSDEFS_H

// Nordic bluetooth+M0 chip
#if defined(NRF51)
#define FASTLED_ARM
#define F_CPU 16000000
#include <stdint.h>
#include "nrf51.h"
#include "core_cm0.h"
typedef volatile uint32_t RoReg;
typedef volatile uint32_t RwReg;
typedef uint32_t prog_uint32_t;
typedef uint8_t boolean;
#define PROGMEM
#define NO_PROGMEM
#define NEED_CXX_BITS

#define cli()  __disable_irq();
#define sei() __enable_irq();

// Teensy 3/3.1 chips
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
#define FASTLED_TEENSY3
#define FASTLED_ARM
#if (F_CPU == 96000000)
#define CLK_DBL 1
#endif
// Arduino due
#elif defined(__SAM3X8E__)
#define FASTLED_ARM
#define FASTLED_DUE
// everything else
#else
#define FASTLED_AVR
#endif

#ifndef CLK_DBL
#define CLK_DBL 0
#endif

#if defined(FASTLED_AVR) || defined(FASTLED_TEENSY3)
#include <avr/io.h>
#include <avr/interrupt.h> // for cli/se definitions

// Define the rgister types
#if defined(ARDUINO) // && ARDUINO < 150
typedef volatile       uint8_t RoReg; /**< Read only 8-bit register (volatile const unsigned int) */
typedef volatile       uint8_t RwReg; /**< Read-Write 8-bit register (volatile unsigned int) */
#endif

#elif defined(FASTLED_DUE)
// reuseing/abusing cli/sei defs for due
#define cli()  __disable_irq(); __disable_fault_irq();
#define sei() __enable_irq(); __enable_fault_irq();

#endif


#if defined(ARDUINO)
// Arduino.h needed for convinience functions digitalPinToPort/BitMask/portOutputRegister and the pinMode methods.
#include<Arduino.h>
#endif

// Scaling macro choice
#if defined(LIB8_ATTINY)
#  define INLINE_SCALE(B, SCALE) delaycycles<3>()
#  warning "No hardware multiply, inline brightness scaling disabled"
#else
#   define INLINE_SCALE(B, SCALE) B = scale8_video(B, SCALE)
#endif

#endif
