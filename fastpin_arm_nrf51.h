#ifndef __FASTPIN_ARM_NRF51_H
#define __FASTPIN_ARM_NRF51_H

#if defined(NRF51)
/// Template definition for teensy 3.0 style ARM pins, providing direct access to the various GPIO registers.  Note that this
/// uses the full port GPIO registers.  In theory, in some way, bit-band register access -should- be faster, however I have found
/// that something about the way gcc does register allocation results in the bit-band code being slower.  It will need more fine tuning.
/// The registers are data output, set output, clear output, toggle output, input, and direction
template<uint8_t PIN, uint32_t _MASK> class _ARMPIN {
public:
  typedef volatile uint32_t * port_ptr_t;
  typedef uint32_t port_t;

typedef struct {                                    /*!< GPIO Structure                                                        */
  __I  uint32_t  RESERVED0[321];
  __IO uint32_t  OUT;                               /*!< Write GPIO port.                                                      */
  __IO uint32_t  OUTSET;                            /*!< Set individual bits in GPIO port.                                     */
  __IO uint32_t  OUTCLR;                            /*!< Clear individual bits in GPIO port.                                   */
  __I  uint32_t  IN;                                /*!< Read GPIO port.                                                       */
  __IO uint32_t  DIR;                               /*!< Direction of GPIO pins.                                               */
  __IO uint32_t  DIRSET;                            /*!< DIR set register.                                                     */
  __IO uint32_t  DIRCLR;                            /*!< DIR clear register.                                                   */
  __I  uint32_t  RESERVED1[120];
  __IO uint32_t  PIN_CNF[32];                       /*!< Configuration of GPIO pins.                                           */
} NRF_GPIO_Type;


  inline static void setOutput() { NRF_GPIO->DIRSET = _MASK; }
  inline static void setInput() { NRF_GPIO->DIRCLR = _MASK; }

  inline static void hi() __attribute__ ((always_inline)) { NRF_GPIO->OUTSET = _MASK; }
  inline static void lo() __attribute__ ((always_inline)) { NRF_GPIO->OUTCLR = _MASK; }
  inline static void set(register port_t val) __attribute__ ((always_inline)) { NRF_GPIO->OUT = val; }

  inline static void strobe() __attribute__ ((always_inline)) { toggle(); toggle(); }

  inline static void toggle() __attribute__ ((always_inline)) { NRF_GPIO->OUT ^= _MASK; }

  inline static void hi(register port_ptr_t port) __attribute__ ((always_inline)) { hi(); }
  inline static void lo(register port_ptr_t port) __attribute__ ((always_inline)) { lo(); }
  inline static void fastset(register port_ptr_t port, register port_t val) __attribute__ ((always_inline)) { *port = val; }

  inline static port_t hival() __attribute__ ((always_inline)) { return NRF_GPIO->OUT | _MASK; }
  inline static port_t loval() __attribute__ ((always_inline)) { return NRF_GPIO->OUT & ~_MASK; }
  inline static port_ptr_t port() __attribute__ ((always_inline)) { return &NRF_GPIO->OUT; }
  inline static port_t mask() __attribute__ ((always_inline)) { return _MASK; }
};

#define _DEFPIN_ARM(PIN) template<> class FastPin<PIN> : public _ARMPIN<PIN, 1 << PIN> {};

// Actual pin definitions
#define MAX_PIN 31
_DEFPIN_ARM(0); _DEFPIN_ARM(1); _DEFPIN_ARM(2); _DEFPIN_ARM(3);
_DEFPIN_ARM(4); _DEFPIN_ARM(5); _DEFPIN_ARM(6); _DEFPIN_ARM(7);
_DEFPIN_ARM(8); _DEFPIN_ARM(9); _DEFPIN_ARM(10); _DEFPIN_ARM(11);
_DEFPIN_ARM(12); _DEFPIN_ARM(13); _DEFPIN_ARM(14); _DEFPIN_ARM(15);
_DEFPIN_ARM(16); _DEFPIN_ARM(17); _DEFPIN_ARM(18); _DEFPIN_ARM(19);
_DEFPIN_ARM(20); _DEFPIN_ARM(21); _DEFPIN_ARM(22); _DEFPIN_ARM(23);
_DEFPIN_ARM(24); _DEFPIN_ARM(25); _DEFPIN_ARM(26); _DEFPIN_ARM(27);
_DEFPIN_ARM(28); _DEFPIN_ARM(29); _DEFPIN_ARM(30); _DEFPIN_ARM(31);

#define HAS_HARDWARE_PIN_SUPPORT

#endif

#endif
