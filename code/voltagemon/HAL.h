/* Automatically generated HAL from HAL.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2014-01-20 10:35:47 */

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

/* SS -> PB2 (Input, Initially Pullup On) */
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
#define SS_IsInactive()                          (SS_Get() == 0)
#define SS_IsActive()                            (SS_Get() != 0)
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

/* Sense01 -> PC0 (Input, Initially Pullup On, Active-Low) */
#define Sense01_BIT                              0
#define Sense01_PIN                              PINC
#define Sense01_PORT                             PORTC
#define Sense01_DDR                              DDRC
#define Sense01_SetPullupActive()                Sense01_PORT |= _BV(Sense01_BIT)
#define Sense01_SetPullupInactive()              Sense01_PORT &= ~_BV(Sense01_BIT)
#define Sense01_ModeInput()                      Sense01_DDR &= ~_BV(Sense01_BIT)
#define Sense01_IsInput()                        ((Sense01_DDR & _BV(Sense01_BIT)) == 0)
#define Sense01_Get()                            (Sense01_PIN & _BV(Sense01_BIT))
#define Sense01_GetBit()                         (Sense01_Get() >> Sense01_BIT)
#define Sense01_IsInactive()                     (Sense01_Get() != 0)
#define Sense01_IsActive()                       (Sense01_Get() == 0)
#define Sense01_Init()                           { Sense01_SetPullupActive(); Sense01_ModeInput(); }

/* Sense02 -> PC1 (Input, Initially Pullup On, Active-Low) */
#define Sense02_BIT                              1
#define Sense02_PIN                              PINC
#define Sense02_PORT                             PORTC
#define Sense02_DDR                              DDRC
#define Sense02_SetPullupActive()                Sense02_PORT |= _BV(Sense02_BIT)
#define Sense02_SetPullupInactive()              Sense02_PORT &= ~_BV(Sense02_BIT)
#define Sense02_ModeInput()                      Sense02_DDR &= ~_BV(Sense02_BIT)
#define Sense02_IsInput()                        ((Sense02_DDR & _BV(Sense02_BIT)) == 0)
#define Sense02_Get()                            (Sense02_PIN & _BV(Sense02_BIT))
#define Sense02_GetBit()                         (Sense02_Get() >> Sense02_BIT)
#define Sense02_IsInactive()                     (Sense02_Get() != 0)
#define Sense02_IsActive()                       (Sense02_Get() == 0)
#define Sense02_Init()                           { Sense02_SetPullupActive(); Sense02_ModeInput(); }

/* Sense03 -> PC2 (Input, Initially Pullup On, Active-Low) */
#define Sense03_BIT                              2
#define Sense03_PIN                              PINC
#define Sense03_PORT                             PORTC
#define Sense03_DDR                              DDRC
#define Sense03_SetPullupActive()                Sense03_PORT |= _BV(Sense03_BIT)
#define Sense03_SetPullupInactive()              Sense03_PORT &= ~_BV(Sense03_BIT)
#define Sense03_ModeInput()                      Sense03_DDR &= ~_BV(Sense03_BIT)
#define Sense03_IsInput()                        ((Sense03_DDR & _BV(Sense03_BIT)) == 0)
#define Sense03_Get()                            (Sense03_PIN & _BV(Sense03_BIT))
#define Sense03_GetBit()                         (Sense03_Get() >> Sense03_BIT)
#define Sense03_IsInactive()                     (Sense03_Get() != 0)
#define Sense03_IsActive()                       (Sense03_Get() == 0)
#define Sense03_Init()                           { Sense03_SetPullupActive(); Sense03_ModeInput(); }

/* Sense04 -> PC3 (Input, Initially Pullup On, Active-Low) */
#define Sense04_BIT                              3
#define Sense04_PIN                              PINC
#define Sense04_PORT                             PORTC
#define Sense04_DDR                              DDRC
#define Sense04_SetPullupActive()                Sense04_PORT |= _BV(Sense04_BIT)
#define Sense04_SetPullupInactive()              Sense04_PORT &= ~_BV(Sense04_BIT)
#define Sense04_ModeInput()                      Sense04_DDR &= ~_BV(Sense04_BIT)
#define Sense04_IsInput()                        ((Sense04_DDR & _BV(Sense04_BIT)) == 0)
#define Sense04_Get()                            (Sense04_PIN & _BV(Sense04_BIT))
#define Sense04_GetBit()                         (Sense04_Get() >> Sense04_BIT)
#define Sense04_IsInactive()                     (Sense04_Get() != 0)
#define Sense04_IsActive()                       (Sense04_Get() == 0)
#define Sense04_Init()                           { Sense04_SetPullupActive(); Sense04_ModeInput(); }

/* Sense05 -> PC4 (Input, Initially Pullup On, Active-Low) */
#define Sense05_BIT                              4
#define Sense05_PIN                              PINC
#define Sense05_PORT                             PORTC
#define Sense05_DDR                              DDRC
#define Sense05_SetPullupActive()                Sense05_PORT |= _BV(Sense05_BIT)
#define Sense05_SetPullupInactive()              Sense05_PORT &= ~_BV(Sense05_BIT)
#define Sense05_ModeInput()                      Sense05_DDR &= ~_BV(Sense05_BIT)
#define Sense05_IsInput()                        ((Sense05_DDR & _BV(Sense05_BIT)) == 0)
#define Sense05_Get()                            (Sense05_PIN & _BV(Sense05_BIT))
#define Sense05_GetBit()                         (Sense05_Get() >> Sense05_BIT)
#define Sense05_IsInactive()                     (Sense05_Get() != 0)
#define Sense05_IsActive()                       (Sense05_Get() == 0)
#define Sense05_Init()                           { Sense05_SetPullupActive(); Sense05_ModeInput(); }

/* Sense06 -> PC5 (Input, Initially Pullup On, Active-Low) */
#define Sense06_BIT                              5
#define Sense06_PIN                              PINC
#define Sense06_PORT                             PORTC
#define Sense06_DDR                              DDRC
#define Sense06_SetPullupActive()                Sense06_PORT |= _BV(Sense06_BIT)
#define Sense06_SetPullupInactive()              Sense06_PORT &= ~_BV(Sense06_BIT)
#define Sense06_ModeInput()                      Sense06_DDR &= ~_BV(Sense06_BIT)
#define Sense06_IsInput()                        ((Sense06_DDR & _BV(Sense06_BIT)) == 0)
#define Sense06_Get()                            (Sense06_PIN & _BV(Sense06_BIT))
#define Sense06_GetBit()                         (Sense06_Get() >> Sense06_BIT)
#define Sense06_IsInactive()                     (Sense06_Get() != 0)
#define Sense06_IsActive()                       (Sense06_Get() == 0)
#define Sense06_Init()                           { Sense06_SetPullupActive(); Sense06_ModeInput(); }

/* Sense07 -> PD0 (Input, Initially Pullup On, Active-Low) */
#define Sense07_BIT                              0
#define Sense07_PIN                              PIND
#define Sense07_PORT                             PORTD
#define Sense07_DDR                              DDRD
#define Sense07_SetPullupActive()                Sense07_PORT |= _BV(Sense07_BIT)
#define Sense07_SetPullupInactive()              Sense07_PORT &= ~_BV(Sense07_BIT)
#define Sense07_ModeInput()                      Sense07_DDR &= ~_BV(Sense07_BIT)
#define Sense07_IsInput()                        ((Sense07_DDR & _BV(Sense07_BIT)) == 0)
#define Sense07_Get()                            (Sense07_PIN & _BV(Sense07_BIT))
#define Sense07_GetBit()                         (Sense07_Get() >> Sense07_BIT)
#define Sense07_IsInactive()                     (Sense07_Get() != 0)
#define Sense07_IsActive()                       (Sense07_Get() == 0)
#define Sense07_Init()                           { Sense07_SetPullupActive(); Sense07_ModeInput(); }

/* Sense08 -> PD1 (Input, Initially Pullup On, Active-Low) */
#define Sense08_BIT                              1
#define Sense08_PIN                              PIND
#define Sense08_PORT                             PORTD
#define Sense08_DDR                              DDRD
#define Sense08_SetPullupActive()                Sense08_PORT |= _BV(Sense08_BIT)
#define Sense08_SetPullupInactive()              Sense08_PORT &= ~_BV(Sense08_BIT)
#define Sense08_ModeInput()                      Sense08_DDR &= ~_BV(Sense08_BIT)
#define Sense08_IsInput()                        ((Sense08_DDR & _BV(Sense08_BIT)) == 0)
#define Sense08_Get()                            (Sense08_PIN & _BV(Sense08_BIT))
#define Sense08_GetBit()                         (Sense08_Get() >> Sense08_BIT)
#define Sense08_IsInactive()                     (Sense08_Get() != 0)
#define Sense08_IsActive()                       (Sense08_Get() == 0)
#define Sense08_Init()                           { Sense08_SetPullupActive(); Sense08_ModeInput(); }

/* Sense09 -> PD2 (Input, Initially Pullup On, Active-Low) */
#define Sense09_BIT                              2
#define Sense09_PIN                              PIND
#define Sense09_PORT                             PORTD
#define Sense09_DDR                              DDRD
#define Sense09_SetPullupActive()                Sense09_PORT |= _BV(Sense09_BIT)
#define Sense09_SetPullupInactive()              Sense09_PORT &= ~_BV(Sense09_BIT)
#define Sense09_ModeInput()                      Sense09_DDR &= ~_BV(Sense09_BIT)
#define Sense09_IsInput()                        ((Sense09_DDR & _BV(Sense09_BIT)) == 0)
#define Sense09_Get()                            (Sense09_PIN & _BV(Sense09_BIT))
#define Sense09_GetBit()                         (Sense09_Get() >> Sense09_BIT)
#define Sense09_IsInactive()                     (Sense09_Get() != 0)
#define Sense09_IsActive()                       (Sense09_Get() == 0)
#define Sense09_Init()                           { Sense09_SetPullupActive(); Sense09_ModeInput(); }

/* Sense10 -> PD3 (Input, Initially Pullup On, Active-Low) */
#define Sense10_BIT                              3
#define Sense10_PIN                              PIND
#define Sense10_PORT                             PORTD
#define Sense10_DDR                              DDRD
#define Sense10_SetPullupActive()                Sense10_PORT |= _BV(Sense10_BIT)
#define Sense10_SetPullupInactive()              Sense10_PORT &= ~_BV(Sense10_BIT)
#define Sense10_ModeInput()                      Sense10_DDR &= ~_BV(Sense10_BIT)
#define Sense10_IsInput()                        ((Sense10_DDR & _BV(Sense10_BIT)) == 0)
#define Sense10_Get()                            (Sense10_PIN & _BV(Sense10_BIT))
#define Sense10_GetBit()                         (Sense10_Get() >> Sense10_BIT)
#define Sense10_IsInactive()                     (Sense10_Get() != 0)
#define Sense10_IsActive()                       (Sense10_Get() == 0)
#define Sense10_Init()                           { Sense10_SetPullupActive(); Sense10_ModeInput(); }

/* Sense11 -> PD4 (Input, Initially Pullup On, Active-Low) */
#define Sense11_BIT                              4
#define Sense11_PIN                              PIND
#define Sense11_PORT                             PORTD
#define Sense11_DDR                              DDRD
#define Sense11_SetPullupActive()                Sense11_PORT |= _BV(Sense11_BIT)
#define Sense11_SetPullupInactive()              Sense11_PORT &= ~_BV(Sense11_BIT)
#define Sense11_ModeInput()                      Sense11_DDR &= ~_BV(Sense11_BIT)
#define Sense11_IsInput()                        ((Sense11_DDR & _BV(Sense11_BIT)) == 0)
#define Sense11_Get()                            (Sense11_PIN & _BV(Sense11_BIT))
#define Sense11_GetBit()                         (Sense11_Get() >> Sense11_BIT)
#define Sense11_IsInactive()                     (Sense11_Get() != 0)
#define Sense11_IsActive()                       (Sense11_Get() == 0)
#define Sense11_Init()                           { Sense11_SetPullupActive(); Sense11_ModeInput(); }

/* Sense12 -> PD5 (Input, Initially Pullup On, Active-Low) */
#define Sense12_BIT                              5
#define Sense12_PIN                              PIND
#define Sense12_PORT                             PORTD
#define Sense12_DDR                              DDRD
#define Sense12_SetPullupActive()                Sense12_PORT |= _BV(Sense12_BIT)
#define Sense12_SetPullupInactive()              Sense12_PORT &= ~_BV(Sense12_BIT)
#define Sense12_ModeInput()                      Sense12_DDR &= ~_BV(Sense12_BIT)
#define Sense12_IsInput()                        ((Sense12_DDR & _BV(Sense12_BIT)) == 0)
#define Sense12_Get()                            (Sense12_PIN & _BV(Sense12_BIT))
#define Sense12_GetBit()                         (Sense12_Get() >> Sense12_BIT)
#define Sense12_IsInactive()                     (Sense12_Get() != 0)
#define Sense12_IsActive()                       (Sense12_Get() == 0)
#define Sense12_Init()                           { Sense12_SetPullupActive(); Sense12_ModeInput(); }

/* LEDRed -> PD6 (Output, Initially Inactive) */
#define LEDRed_BIT                               6
#define LEDRed_PIN                               PIND
#define LEDRed_PORT                              PORTD
#define LEDRed_DDR                               DDRD
#define LEDRed_ModeOutput()                      LEDRed_DDR |= _BV(LEDRed_BIT)
#define LEDRed_IsOutput()                        ((LEDRed_DDR & _BV(LEDRed_BIT)) != 0)
#define LEDRed_SetHIGH()                         LEDRed_PORT |= _BV(LEDRed_BIT)
#define LEDRed_SetLOW()                          LEDRed_PORT &= ~_BV(LEDRed_BIT)
#define LEDRed_Get()                             (LEDRed_PIN & _BV(LEDRed_BIT))
#define LEDRed_SetInactive()                     LEDRed_SetLOW()
#define LEDRed_SetActive()                       LEDRed_SetHIGH()
#define LEDRed_Toggle()                          LEDRed_PORT ^= _BV(LEDRed_BIT)
#define LEDRed_SetConditional(condition)         if (condition) LEDRed_SetActive(); else LEDRed_SetInactive()
#define LEDRed_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { LEDRed_SetActive(); } else if (conditionoff) { LEDRed_SetInactive(); } else if (conditiontoggle) { LEDRed_Toggle(); }
#define LEDRed_Pulse()                           { LEDRed_SetActive(); LEDRed_SetInactive(); }
#define LEDRed_PulseNop()                        { LEDRed_SetActive(); nop(); LEDRed_SetInactive(); }
#define LEDRed_IsInactive()                      (LEDRed_Get() == 0)
#define LEDRed_IsActive()                        (LEDRed_Get() != 0)
#define LEDRed_Init()                            { LEDRed_SetInactive(); LEDRed_ModeOutput(); }

#define initHAL() {\
		SignalIRQ_Init();\
		MISO_Init();\
		MOSI_Init();\
		SS_Init();\
		SCK_Init();\
		Sense01_Init();\
		Sense02_Init();\
		Sense03_Init();\
		Sense04_Init();\
		Sense05_Init();\
		Sense06_Init();\
		Sense07_Init();\
		Sense08_Init();\
		Sense09_Init();\
		Sense10_Init();\
		Sense11_Init();\
		Sense12_Init();\
		LEDRed_Init();\
}

#endif
