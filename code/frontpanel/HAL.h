/* Automatically generated HAL from HAL.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2014-01-17 22:02:57 */

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

/* Mux_OE -> PB1 (Output, Initially Inactive, Active-Low) */
#define Mux_OE_BIT                               1
#define Mux_OE_PIN                               PINB
#define Mux_OE_PORT                              PORTB
#define Mux_OE_DDR                               DDRB
#define Mux_OE_ModeOutput()                      Mux_OE_DDR |= _BV(Mux_OE_BIT)
#define Mux_OE_IsOutput()                        ((Mux_OE_DDR & _BV(Mux_OE_BIT)) != 0)
#define Mux_OE_SetHIGH()                         Mux_OE_PORT |= _BV(Mux_OE_BIT)
#define Mux_OE_SetLOW()                          Mux_OE_PORT &= ~_BV(Mux_OE_BIT)
#define Mux_OE_Get()                             (Mux_OE_PIN & _BV(Mux_OE_BIT))
#define Mux_OE_SetInactive()                     Mux_OE_SetHIGH()
#define Mux_OE_SetActive()                       Mux_OE_SetLOW()
#define Mux_OE_Toggle()                          Mux_OE_PORT ^= _BV(Mux_OE_BIT)
#define Mux_OE_SetConditional(condition)         if (condition) Mux_OE_SetActive(); else Mux_OE_SetInactive()
#define Mux_OE_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Mux_OE_SetActive(); } else if (conditionoff) { Mux_OE_SetInactive(); } else if (conditiontoggle) { Mux_OE_Toggle(); }
#define Mux_OE_Pulse()                           { Mux_OE_SetActive(); Mux_OE_SetInactive(); }
#define Mux_OE_PulseNop()                        { Mux_OE_SetActive(); nop(); Mux_OE_SetInactive(); }
#define Mux_OE_IsInactive()                      (Mux_OE_Get() != 0)
#define Mux_OE_IsActive()                        (Mux_OE_Get() == 0)
#define Mux_OE_Init()                            { Mux_OE_SetInactive(); Mux_OE_ModeOutput(); }

/* Mux_Q7S -> PD0 (Input, Initially Pullup On) */
#define Mux_Q7S_BIT                              0
#define Mux_Q7S_PIN                              PIND
#define Mux_Q7S_PORT                             PORTD
#define Mux_Q7S_DDR                              DDRD
#define Mux_Q7S_SetPullupActive()                Mux_Q7S_PORT |= _BV(Mux_Q7S_BIT)
#define Mux_Q7S_SetPullupInactive()              Mux_Q7S_PORT &= ~_BV(Mux_Q7S_BIT)
#define Mux_Q7S_ModeInput()                      Mux_Q7S_DDR &= ~_BV(Mux_Q7S_BIT)
#define Mux_Q7S_IsInput()                        ((Mux_Q7S_DDR & _BV(Mux_Q7S_BIT)) == 0)
#define Mux_Q7S_Get()                            (Mux_Q7S_PIN & _BV(Mux_Q7S_BIT))
#define Mux_Q7S_GetBit()                         (Mux_Q7S_Get() >> Mux_Q7S_BIT)
#define Mux_Q7S_IsInactive()                     (Mux_Q7S_Get() == 0)
#define Mux_Q7S_IsActive()                       (Mux_Q7S_Get() != 0)
#define Mux_Q7S_Init()                           { Mux_Q7S_SetPullupActive(); Mux_Q7S_ModeInput(); }

/* Mux_DS -> PD5 (Output, Initially Inactive) */
#define Mux_DS_BIT                               5
#define Mux_DS_PIN                               PIND
#define Mux_DS_PORT                              PORTD
#define Mux_DS_DDR                               DDRD
#define Mux_DS_ModeOutput()                      Mux_DS_DDR |= _BV(Mux_DS_BIT)
#define Mux_DS_IsOutput()                        ((Mux_DS_DDR & _BV(Mux_DS_BIT)) != 0)
#define Mux_DS_SetHIGH()                         Mux_DS_PORT |= _BV(Mux_DS_BIT)
#define Mux_DS_SetLOW()                          Mux_DS_PORT &= ~_BV(Mux_DS_BIT)
#define Mux_DS_Get()                             (Mux_DS_PIN & _BV(Mux_DS_BIT))
#define Mux_DS_SetInactive()                     Mux_DS_SetLOW()
#define Mux_DS_SetActive()                       Mux_DS_SetHIGH()
#define Mux_DS_Toggle()                          Mux_DS_PORT ^= _BV(Mux_DS_BIT)
#define Mux_DS_SetConditional(condition)         if (condition) Mux_DS_SetActive(); else Mux_DS_SetInactive()
#define Mux_DS_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Mux_DS_SetActive(); } else if (conditionoff) { Mux_DS_SetInactive(); } else if (conditiontoggle) { Mux_DS_Toggle(); }
#define Mux_DS_Pulse()                           { Mux_DS_SetActive(); Mux_DS_SetInactive(); }
#define Mux_DS_PulseNop()                        { Mux_DS_SetActive(); nop(); Mux_DS_SetInactive(); }
#define Mux_DS_IsInactive()                      (Mux_DS_Get() == 0)
#define Mux_DS_IsActive()                        (Mux_DS_Get() != 0)
#define Mux_DS_Init()                            { Mux_DS_SetInactive(); Mux_DS_ModeOutput(); }

/* Mux_STCP -> PD6 (Output, Initially Inactive) */
#define Mux_STCP_BIT                             6
#define Mux_STCP_PIN                             PIND
#define Mux_STCP_PORT                            PORTD
#define Mux_STCP_DDR                             DDRD
#define Mux_STCP_ModeOutput()                    Mux_STCP_DDR |= _BV(Mux_STCP_BIT)
#define Mux_STCP_IsOutput()                      ((Mux_STCP_DDR & _BV(Mux_STCP_BIT)) != 0)
#define Mux_STCP_SetHIGH()                       Mux_STCP_PORT |= _BV(Mux_STCP_BIT)
#define Mux_STCP_SetLOW()                        Mux_STCP_PORT &= ~_BV(Mux_STCP_BIT)
#define Mux_STCP_Get()                           (Mux_STCP_PIN & _BV(Mux_STCP_BIT))
#define Mux_STCP_SetInactive()                   Mux_STCP_SetLOW()
#define Mux_STCP_SetActive()                     Mux_STCP_SetHIGH()
#define Mux_STCP_Toggle()                        Mux_STCP_PORT ^= _BV(Mux_STCP_BIT)
#define Mux_STCP_SetConditional(condition)       if (condition) Mux_STCP_SetActive(); else Mux_STCP_SetInactive()
#define Mux_STCP_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Mux_STCP_SetActive(); } else if (conditionoff) { Mux_STCP_SetInactive(); } else if (conditiontoggle) { Mux_STCP_Toggle(); }
#define Mux_STCP_Pulse()                         { Mux_STCP_SetActive(); Mux_STCP_SetInactive(); }
#define Mux_STCP_PulseNop()                      { Mux_STCP_SetActive(); nop(); Mux_STCP_SetInactive(); }
#define Mux_STCP_IsInactive()                    (Mux_STCP_Get() == 0)
#define Mux_STCP_IsActive()                      (Mux_STCP_Get() != 0)
#define Mux_STCP_Init()                          { Mux_STCP_SetInactive(); Mux_STCP_ModeOutput(); }

/* Mux_SHCP -> PD7 (Output, Initially Inactive) */
#define Mux_SHCP_BIT                             7
#define Mux_SHCP_PIN                             PIND
#define Mux_SHCP_PORT                            PORTD
#define Mux_SHCP_DDR                             DDRD
#define Mux_SHCP_ModeOutput()                    Mux_SHCP_DDR |= _BV(Mux_SHCP_BIT)
#define Mux_SHCP_IsOutput()                      ((Mux_SHCP_DDR & _BV(Mux_SHCP_BIT)) != 0)
#define Mux_SHCP_SetHIGH()                       Mux_SHCP_PORT |= _BV(Mux_SHCP_BIT)
#define Mux_SHCP_SetLOW()                        Mux_SHCP_PORT &= ~_BV(Mux_SHCP_BIT)
#define Mux_SHCP_Get()                           (Mux_SHCP_PIN & _BV(Mux_SHCP_BIT))
#define Mux_SHCP_SetInactive()                   Mux_SHCP_SetLOW()
#define Mux_SHCP_SetActive()                     Mux_SHCP_SetHIGH()
#define Mux_SHCP_Toggle()                        Mux_SHCP_PORT ^= _BV(Mux_SHCP_BIT)
#define Mux_SHCP_SetConditional(condition)       if (condition) Mux_SHCP_SetActive(); else Mux_SHCP_SetInactive()
#define Mux_SHCP_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Mux_SHCP_SetActive(); } else if (conditionoff) { Mux_SHCP_SetInactive(); } else if (conditiontoggle) { Mux_SHCP_Toggle(); }
#define Mux_SHCP_Pulse()                         { Mux_SHCP_SetActive(); Mux_SHCP_SetInactive(); }
#define Mux_SHCP_PulseNop()                      { Mux_SHCP_SetActive(); nop(); Mux_SHCP_SetInactive(); }
#define Mux_SHCP_IsInactive()                    (Mux_SHCP_Get() == 0)
#define Mux_SHCP_IsActive()                      (Mux_SHCP_Get() != 0)
#define Mux_SHCP_Init()                          { Mux_SHCP_SetInactive(); Mux_SHCP_ModeOutput(); }

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

/* Key_Deadman -> PC5 (Input, Initially Pullup On, Active-Low) */
#define Key_Deadman_BIT                          5
#define Key_Deadman_PIN                          PINC
#define Key_Deadman_PORT                         PORTC
#define Key_Deadman_DDR                          DDRC
#define Key_Deadman_SetPullupActive()            Key_Deadman_PORT |= _BV(Key_Deadman_BIT)
#define Key_Deadman_SetPullupInactive()          Key_Deadman_PORT &= ~_BV(Key_Deadman_BIT)
#define Key_Deadman_ModeInput()                  Key_Deadman_DDR &= ~_BV(Key_Deadman_BIT)
#define Key_Deadman_IsInput()                    ((Key_Deadman_DDR & _BV(Key_Deadman_BIT)) == 0)
#define Key_Deadman_Get()                        (Key_Deadman_PIN & _BV(Key_Deadman_BIT))
#define Key_Deadman_GetBit()                     (Key_Deadman_Get() >> Key_Deadman_BIT)
#define Key_Deadman_IsInactive()                 (Key_Deadman_Get() != 0)
#define Key_Deadman_IsActive()                   (Key_Deadman_Get() == 0)
#define Key_Deadman_Init()                       { Key_Deadman_SetPullupActive(); Key_Deadman_ModeInput(); }

/* Key_AutoXfrm -> PC4 (Input, Initially Pullup On, Active-Low) */
#define Key_AutoXfrm_BIT                         4
#define Key_AutoXfrm_PIN                         PINC
#define Key_AutoXfrm_PORT                        PORTC
#define Key_AutoXfrm_DDR                         DDRC
#define Key_AutoXfrm_SetPullupActive()           Key_AutoXfrm_PORT |= _BV(Key_AutoXfrm_BIT)
#define Key_AutoXfrm_SetPullupInactive()         Key_AutoXfrm_PORT &= ~_BV(Key_AutoXfrm_BIT)
#define Key_AutoXfrm_ModeInput()                 Key_AutoXfrm_DDR &= ~_BV(Key_AutoXfrm_BIT)
#define Key_AutoXfrm_IsInput()                   ((Key_AutoXfrm_DDR & _BV(Key_AutoXfrm_BIT)) == 0)
#define Key_AutoXfrm_Get()                       (Key_AutoXfrm_PIN & _BV(Key_AutoXfrm_BIT))
#define Key_AutoXfrm_GetBit()                    (Key_AutoXfrm_Get() >> Key_AutoXfrm_BIT)
#define Key_AutoXfrm_IsInactive()                (Key_AutoXfrm_Get() != 0)
#define Key_AutoXfrm_IsActive()                  (Key_AutoXfrm_Get() == 0)
#define Key_AutoXfrm_Init()                      { Key_AutoXfrm_SetPullupActive(); Key_AutoXfrm_ModeInput(); }

/* Key_IsoXfrm -> PC3 (Input, Initially Pullup On, Active-Low) */
#define Key_IsoXfrm_BIT                          3
#define Key_IsoXfrm_PIN                          PINC
#define Key_IsoXfrm_PORT                         PORTC
#define Key_IsoXfrm_DDR                          DDRC
#define Key_IsoXfrm_SetPullupActive()            Key_IsoXfrm_PORT |= _BV(Key_IsoXfrm_BIT)
#define Key_IsoXfrm_SetPullupInactive()          Key_IsoXfrm_PORT &= ~_BV(Key_IsoXfrm_BIT)
#define Key_IsoXfrm_ModeInput()                  Key_IsoXfrm_DDR &= ~_BV(Key_IsoXfrm_BIT)
#define Key_IsoXfrm_IsInput()                    ((Key_IsoXfrm_DDR & _BV(Key_IsoXfrm_BIT)) == 0)
#define Key_IsoXfrm_Get()                        (Key_IsoXfrm_PIN & _BV(Key_IsoXfrm_BIT))
#define Key_IsoXfrm_GetBit()                     (Key_IsoXfrm_Get() >> Key_IsoXfrm_BIT)
#define Key_IsoXfrm_IsInactive()                 (Key_IsoXfrm_Get() != 0)
#define Key_IsoXfrm_IsActive()                   (Key_IsoXfrm_Get() == 0)
#define Key_IsoXfrm_Init()                       { Key_IsoXfrm_SetPullupActive(); Key_IsoXfrm_ModeInput(); }

/* Key_Output -> PC2 (Input, Initially Pullup On, Active-Low) */
#define Key_Output_BIT                           2
#define Key_Output_PIN                           PINC
#define Key_Output_PORT                          PORTC
#define Key_Output_DDR                           DDRC
#define Key_Output_SetPullupActive()             Key_Output_PORT |= _BV(Key_Output_BIT)
#define Key_Output_SetPullupInactive()           Key_Output_PORT &= ~_BV(Key_Output_BIT)
#define Key_Output_ModeInput()                   Key_Output_DDR &= ~_BV(Key_Output_BIT)
#define Key_Output_IsInput()                     ((Key_Output_DDR & _BV(Key_Output_BIT)) == 0)
#define Key_Output_Get()                         (Key_Output_PIN & _BV(Key_Output_BIT))
#define Key_Output_GetBit()                      (Key_Output_Get() >> Key_Output_BIT)
#define Key_Output_IsInactive()                  (Key_Output_Get() != 0)
#define Key_Output_IsActive()                    (Key_Output_Get() == 0)
#define Key_Output_Init()                        { Key_Output_SetPullupActive(); Key_Output_ModeInput(); }

#define initHAL() {\
		SignalIRQ_Init();\
		Mux_OE_Init();\
		Mux_Q7S_Init();\
		Mux_DS_Init();\
		Mux_STCP_Init();\
		Mux_SHCP_Init();\
		MISO_Init();\
		MOSI_Init();\
		SS_Init();\
		SCK_Init();\
		Key_Deadman_Init();\
		Key_AutoXfrm_Init();\
		Key_IsoXfrm_Init();\
		Key_Output_Init();\
}

#endif
