/* Automatically generated HAL from HAL.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2014-01-22 23:48:12 */

#ifndef __HAL_H__
#define __HAL_H__

#include <avr/io.h>

#define nop()                                    __asm__ __volatile__("nop")

/* SignalIRQ -> PB0 (Output, Initially Inactive) */
#define SignalIRQ_BIT                            0
#define SignalIRQ_PIN                            PINB
#define SignalIRQ_PORT                           PORTB
#define SignalIRQ_DDR                            DDRB
#define SignalIRQ_ModeOutput()                   SignalIRQ_DDR |= _BV(SignalIRQ_BIT)
#define SignalIRQ_IsOutput()                     ((SignalIRQ_DDR & _BV(SignalIRQ_BIT)) != 0)
#define SignalIRQ_SetHIGH()                      SignalIRQ_PORT |= _BV(SignalIRQ_BIT)
#define SignalIRQ_SetLOW()                       SignalIRQ_PORT &= ~_BV(SignalIRQ_BIT)
#define SignalIRQ_Get()                          (SignalIRQ_PIN & _BV(SignalIRQ_BIT))
#define SignalIRQ_SetInactive()                  SignalIRQ_SetLOW()
#define SignalIRQ_SetActive()                    SignalIRQ_SetHIGH()
#define SignalIRQ_Toggle()                       SignalIRQ_PORT ^= _BV(SignalIRQ_BIT)
#define SignalIRQ_SetConditional(condition)      if (condition) SignalIRQ_SetActive(); else SignalIRQ_SetInactive()
#define SignalIRQ_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { SignalIRQ_SetActive(); } else if (conditionoff) { SignalIRQ_SetInactive(); } else if (conditiontoggle) { SignalIRQ_Toggle(); }
#define SignalIRQ_Pulse()                        { SignalIRQ_SetActive(); SignalIRQ_SetInactive(); }
#define SignalIRQ_PulseNop()                     { SignalIRQ_SetActive(); nop(); SignalIRQ_SetInactive(); }
#define SignalIRQ_IsInactive()                   (SignalIRQ_Get() == 0)
#define SignalIRQ_IsActive()                     (SignalIRQ_Get() != 0)
#define SignalIRQ_Init()                         { SignalIRQ_SetInactive(); SignalIRQ_ModeOutput(); }

/* MISO -> PB4 (Output, Initially Inactive) */
#define MISO_BIT                                 4
#define MISO_PIN                                 PINB
#define MISO_PORT                                PORTB
#define MISO_DDR                                 DDRB
#define MISO_ModeOutput()                        MISO_DDR |= _BV(MISO_BIT)
#define MISO_IsOutput()                          ((MISO_DDR & _BV(MISO_BIT)) != 0)
#define MISO_SetHIGH()                           MISO_PORT |= _BV(MISO_BIT)
#define MISO_SetLOW()                            MISO_PORT &= ~_BV(MISO_BIT)
#define MISO_Get()                               (MISO_PIN & _BV(MISO_BIT))
#define MISO_SetInactive()                       MISO_SetLOW()
#define MISO_SetActive()                         MISO_SetHIGH()
#define MISO_Toggle()                            MISO_PORT ^= _BV(MISO_BIT)
#define MISO_SetConditional(condition)           if (condition) MISO_SetActive(); else MISO_SetInactive()
#define MISO_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { MISO_SetActive(); } else if (conditionoff) { MISO_SetInactive(); } else if (conditiontoggle) { MISO_Toggle(); }
#define MISO_Pulse()                             { MISO_SetActive(); MISO_SetInactive(); }
#define MISO_PulseNop()                          { MISO_SetActive(); nop(); MISO_SetInactive(); }
#define MISO_IsInactive()                        (MISO_Get() == 0)
#define MISO_IsActive()                          (MISO_Get() != 0)
#define MISO_Init()                              { MISO_SetInactive(); MISO_ModeOutput(); }

/* MOSI -> PB3 (Input, Initially Pullup On) */
#define MOSI_BIT                                 3
#define MOSI_PIN                                 PINB
#define MOSI_PORT                                PORTB
#define MOSI_DDR                                 DDRB
#define MOSI_SetPullupActive()                   MOSI_PORT |= _BV(MOSI_BIT)
#define MOSI_SetPullupInactive()                 MOSI_PORT &= ~_BV(MOSI_BIT)
#define MOSI_ModeInput()                         MOSI_DDR &= ~_BV(MOSI_BIT)
#define MOSI_IsInput()                           ((MOSI_DDR & _BV(MOSI_BIT)) == 0)
#define MOSI_Get()                               (MOSI_PIN & _BV(MOSI_BIT))
#define MOSI_GetBit()                            (MOSI_Get() >> MOSI_BIT)
#define MOSI_IsInactive()                        (MOSI_Get() == 0)
#define MOSI_IsActive()                          (MOSI_Get() != 0)
#define MOSI_Init()                              { MOSI_SetPullupActive(); MOSI_ModeInput(); }

/* SS -> PB2 (Input, Initially Pullup On, Active-Low) */
#define SS_BIT                                   2
#define SS_PIN                                   PINB
#define SS_PORT                                  PORTB
#define SS_DDR                                   DDRB
#define SS_SetPullupActive()                     SS_PORT |= _BV(SS_BIT)
#define SS_SetPullupInactive()                   SS_PORT &= ~_BV(SS_BIT)
#define SS_ModeInput()                           SS_DDR &= ~_BV(SS_BIT)
#define SS_IsInput()                             ((SS_DDR & _BV(SS_BIT)) == 0)
#define SS_Get()                                 (SS_PIN & _BV(SS_BIT))
#define SS_GetBit()                              (SS_Get() >> SS_BIT)
#define SS_IsInactive()                          (SS_Get() != 0)
#define SS_IsActive()                            (SS_Get() == 0)
#define SS_Init()                                { SS_SetPullupActive(); SS_ModeInput(); }

/* SCK -> PB5 (Input, Initially Pullup On) */
#define SCK_BIT                                  5
#define SCK_PIN                                  PINB
#define SCK_PORT                                 PORTB
#define SCK_DDR                                  DDRB
#define SCK_SetPullupActive()                    SCK_PORT |= _BV(SCK_BIT)
#define SCK_SetPullupInactive()                  SCK_PORT &= ~_BV(SCK_BIT)
#define SCK_ModeInput()                          SCK_DDR &= ~_BV(SCK_BIT)
#define SCK_IsInput()                            ((SCK_DDR & _BV(SCK_BIT)) == 0)
#define SCK_Get()                                (SCK_PIN & _BV(SCK_BIT))
#define SCK_GetBit()                             (SCK_Get() >> SCK_BIT)
#define SCK_IsInactive()                         (SCK_Get() == 0)
#define SCK_IsActive()                           (SCK_Get() != 0)
#define SCK_Init()                               { SCK_SetPullupActive(); SCK_ModeInput(); }

/* LEDYellow -> PD6 (Output, Initially Inactive) */
#define LEDYellow_BIT                            6
#define LEDYellow_PIN                            PIND
#define LEDYellow_PORT                           PORTD
#define LEDYellow_DDR                            DDRD
#define LEDYellow_ModeOutput()                   LEDYellow_DDR |= _BV(LEDYellow_BIT)
#define LEDYellow_IsOutput()                     ((LEDYellow_DDR & _BV(LEDYellow_BIT)) != 0)
#define LEDYellow_SetHIGH()                      LEDYellow_PORT |= _BV(LEDYellow_BIT)
#define LEDYellow_SetLOW()                       LEDYellow_PORT &= ~_BV(LEDYellow_BIT)
#define LEDYellow_Get()                          (LEDYellow_PIN & _BV(LEDYellow_BIT))
#define LEDYellow_SetInactive()                  LEDYellow_SetLOW()
#define LEDYellow_SetActive()                    LEDYellow_SetHIGH()
#define LEDYellow_Toggle()                       LEDYellow_PORT ^= _BV(LEDYellow_BIT)
#define LEDYellow_SetConditional(condition)      if (condition) LEDYellow_SetActive(); else LEDYellow_SetInactive()
#define LEDYellow_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { LEDYellow_SetActive(); } else if (conditionoff) { LEDYellow_SetInactive(); } else if (conditiontoggle) { LEDYellow_Toggle(); }
#define LEDYellow_Pulse()                        { LEDYellow_SetActive(); LEDYellow_SetInactive(); }
#define LEDYellow_PulseNop()                     { LEDYellow_SetActive(); nop(); LEDYellow_SetInactive(); }
#define LEDYellow_IsInactive()                   (LEDYellow_Get() == 0)
#define LEDYellow_IsActive()                     (LEDYellow_Get() != 0)
#define LEDYellow_Init()                         { LEDYellow_SetInactive(); LEDYellow_ModeOutput(); }

/* LEDGreen -> PD7 (Output, Initially Inactive) */
#define LEDGreen_BIT                             7
#define LEDGreen_PIN                             PIND
#define LEDGreen_PORT                            PORTD
#define LEDGreen_DDR                             DDRD
#define LEDGreen_ModeOutput()                    LEDGreen_DDR |= _BV(LEDGreen_BIT)
#define LEDGreen_IsOutput()                      ((LEDGreen_DDR & _BV(LEDGreen_BIT)) != 0)
#define LEDGreen_SetHIGH()                       LEDGreen_PORT |= _BV(LEDGreen_BIT)
#define LEDGreen_SetLOW()                        LEDGreen_PORT &= ~_BV(LEDGreen_BIT)
#define LEDGreen_Get()                           (LEDGreen_PIN & _BV(LEDGreen_BIT))
#define LEDGreen_SetInactive()                   LEDGreen_SetLOW()
#define LEDGreen_SetActive()                     LEDGreen_SetHIGH()
#define LEDGreen_Toggle()                        LEDGreen_PORT ^= _BV(LEDGreen_BIT)
#define LEDGreen_SetConditional(condition)       if (condition) LEDGreen_SetActive(); else LEDGreen_SetInactive()
#define LEDGreen_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { LEDGreen_SetActive(); } else if (conditionoff) { LEDGreen_SetInactive(); } else if (conditiontoggle) { LEDGreen_Toggle(); }
#define LEDGreen_Pulse()                         { LEDGreen_SetActive(); LEDGreen_SetInactive(); }
#define LEDGreen_PulseNop()                      { LEDGreen_SetActive(); nop(); LEDGreen_SetInactive(); }
#define LEDGreen_IsInactive()                    (LEDGreen_Get() == 0)
#define LEDGreen_IsActive()                      (LEDGreen_Get() != 0)
#define LEDGreen_Init()                          { LEDGreen_SetInactive(); LEDGreen_ModeOutput(); }

/* Debug -> PD5 (Output, Initially Inactive) */
#define Debug_BIT                                5
#define Debug_PIN                                PIND
#define Debug_PORT                               PORTD
#define Debug_DDR                                DDRD
#define Debug_ModeOutput()                       Debug_DDR |= _BV(Debug_BIT)
#define Debug_IsOutput()                         ((Debug_DDR & _BV(Debug_BIT)) != 0)
#define Debug_SetHIGH()                          Debug_PORT |= _BV(Debug_BIT)
#define Debug_SetLOW()                           Debug_PORT &= ~_BV(Debug_BIT)
#define Debug_Get()                              (Debug_PIN & _BV(Debug_BIT))
#define Debug_SetInactive()                      Debug_SetLOW()
#define Debug_SetActive()                        Debug_SetHIGH()
#define Debug_Toggle()                           Debug_PORT ^= _BV(Debug_BIT)
#define Debug_SetConditional(condition)          if (condition) Debug_SetActive(); else Debug_SetInactive()
#define Debug_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Debug_SetActive(); } else if (conditionoff) { Debug_SetInactive(); } else if (conditiontoggle) { Debug_Toggle(); }
#define Debug_Pulse()                            { Debug_SetActive(); Debug_SetInactive(); }
#define Debug_PulseNop()                         { Debug_SetActive(); nop(); Debug_SetInactive(); }
#define Debug_IsInactive()                       (Debug_Get() == 0)
#define Debug_IsActive()                         (Debug_Get() != 0)
#define Debug_Init()                             { Debug_SetInactive(); Debug_ModeOutput(); }

#define initHAL() {\
		SignalIRQ_Init();\
		MISO_Init();\
		MOSI_Init();\
		SS_Init();\
		SCK_Init();\
		LEDYellow_Init();\
		LEDGreen_Init();\
		Debug_Init();\
}

#endif
