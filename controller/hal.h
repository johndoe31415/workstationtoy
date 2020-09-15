/* Automatically generated HAL from hal.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2020-08-30 14:11:08 */

#ifndef __HAL_H__
#define __HAL_H__

#include <avr/io.h>

#define nop()                                    __asm__ __volatile__("nop")

/* RS232_RX -> PD2 (Input, Initially Pullup On) */
#define RS232_RX_BIT                             2
#define RS232_RX_PIN                             PIND
#define RS232_RX_PORT                            PORTD
#define RS232_RX_DDR                             DDRD
#define RS232_RX_SetPullupActive()               RS232_RX_PORT |= _BV(RS232_RX_BIT)
#define RS232_RX_SetPullupInactive()             RS232_RX_PORT &= ~_BV(RS232_RX_BIT)
#define RS232_RX_ModeInput()                     RS232_RX_DDR &= ~_BV(RS232_RX_BIT)
#define RS232_RX_IsInput()                       ((RS232_RX_DDR & _BV(RS232_RX_BIT)) == 0)
#define RS232_RX_Get()                           (RS232_RX_PIN & _BV(RS232_RX_BIT))
#define RS232_RX_GetBit()                        (RS232_RX_Get() >> RS232_RX_BIT)
#define RS232_RX_IsInactive()                    (RS232_RX_Get() == 0)
#define RS232_RX_IsActive()                      (RS232_RX_Get() != 0)
#define RS232_RX_Init()                          { RS232_RX_SetPullupActive(); RS232_RX_ModeInput(); }

/* RS232_TX -> PD3 (Output, Initially Inactive, Active-Low) */
#define RS232_TX_BIT                             3
#define RS232_TX_PIN                             PIND
#define RS232_TX_PORT                            PORTD
#define RS232_TX_DDR                             DDRD
#define RS232_TX_ModeOutput()                    RS232_TX_DDR |= _BV(RS232_TX_BIT)
#define RS232_TX_IsOutput()                      ((RS232_TX_DDR & _BV(RS232_TX_BIT)) != 0)
#define RS232_TX_SetHIGH()                       RS232_TX_PORT |= _BV(RS232_TX_BIT)
#define RS232_TX_SetLOW()                        RS232_TX_PORT &= ~_BV(RS232_TX_BIT)
#define RS232_TX_Get()                           (RS232_TX_PIN & _BV(RS232_TX_BIT))
#define RS232_TX_SetInactive()                   RS232_TX_SetHIGH()
#define RS232_TX_SetActive()                     RS232_TX_SetLOW()
#define RS232_TX_Toggle()                        RS232_TX_PORT ^= _BV(RS232_TX_BIT)
#define RS232_TX_SetConditional(condition)       if (condition) RS232_TX_SetActive(); else RS232_TX_SetInactive()
#define RS232_TX_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { RS232_TX_SetActive(); } else if (conditionoff) { RS232_TX_SetInactive(); } else if (conditiontoggle) { RS232_TX_Toggle(); }
#define RS232_TX_Pulse()                         { RS232_TX_SetActive(); RS232_TX_SetInactive(); }
#define RS232_TX_PulseNop()                      { RS232_TX_SetActive(); nop(); RS232_TX_SetInactive(); }
#define RS232_TX_IsInactive()                    (RS232_TX_Get() != 0)
#define RS232_TX_IsActive()                      (RS232_TX_Get() == 0)
#define RS232_TX_Init()                          { RS232_TX_SetInactive(); RS232_TX_ModeOutput(); }

/* SCK -> PB1 (Output, Initially Inactive) */
#define SCK_BIT                                  1
#define SCK_PIN                                  PINB
#define SCK_PORT                                 PORTB
#define SCK_DDR                                  DDRB
#define SCK_ModeOutput()                         SCK_DDR |= _BV(SCK_BIT)
#define SCK_IsOutput()                           ((SCK_DDR & _BV(SCK_BIT)) != 0)
#define SCK_SetHIGH()                            SCK_PORT |= _BV(SCK_BIT)
#define SCK_SetLOW()                             SCK_PORT &= ~_BV(SCK_BIT)
#define SCK_Get()                                (SCK_PIN & _BV(SCK_BIT))
#define SCK_SetInactive()                        SCK_SetLOW()
#define SCK_SetActive()                          SCK_SetHIGH()
#define SCK_Toggle()                             SCK_PORT ^= _BV(SCK_BIT)
#define SCK_SetConditional(condition)            if (condition) SCK_SetActive(); else SCK_SetInactive()
#define SCK_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { SCK_SetActive(); } else if (conditionoff) { SCK_SetInactive(); } else if (conditiontoggle) { SCK_Toggle(); }
#define SCK_Pulse()                              { SCK_SetActive(); SCK_SetInactive(); }
#define SCK_PulseNop()                           { SCK_SetActive(); nop(); SCK_SetInactive(); }
#define SCK_IsInactive()                         (SCK_Get() == 0)
#define SCK_IsActive()                           (SCK_Get() != 0)
#define SCK_Init()                               { SCK_SetInactive(); SCK_ModeOutput(); }

/* MOSI -> PB2 (Output, Initially Inactive) */
#define MOSI_BIT                                 2
#define MOSI_PIN                                 PINB
#define MOSI_PORT                                PORTB
#define MOSI_DDR                                 DDRB
#define MOSI_ModeOutput()                        MOSI_DDR |= _BV(MOSI_BIT)
#define MOSI_IsOutput()                          ((MOSI_DDR & _BV(MOSI_BIT)) != 0)
#define MOSI_SetHIGH()                           MOSI_PORT |= _BV(MOSI_BIT)
#define MOSI_SetLOW()                            MOSI_PORT &= ~_BV(MOSI_BIT)
#define MOSI_Get()                               (MOSI_PIN & _BV(MOSI_BIT))
#define MOSI_SetInactive()                       MOSI_SetLOW()
#define MOSI_SetActive()                         MOSI_SetHIGH()
#define MOSI_Toggle()                            MOSI_PORT ^= _BV(MOSI_BIT)
#define MOSI_SetConditional(condition)           if (condition) MOSI_SetActive(); else MOSI_SetInactive()
#define MOSI_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { MOSI_SetActive(); } else if (conditionoff) { MOSI_SetInactive(); } else if (conditiontoggle) { MOSI_Toggle(); }
#define MOSI_Pulse()                             { MOSI_SetActive(); MOSI_SetInactive(); }
#define MOSI_PulseNop()                          { MOSI_SetActive(); nop(); MOSI_SetInactive(); }
#define MOSI_IsInactive()                        (MOSI_Get() == 0)
#define MOSI_IsActive()                          (MOSI_Get() != 0)
#define MOSI_Init()                              { MOSI_SetInactive(); MOSI_ModeOutput(); }

/* MISO -> PB3 (Input, Initially Pullup On) */
#define MISO_BIT                                 3
#define MISO_PIN                                 PINB
#define MISO_PORT                                PORTB
#define MISO_DDR                                 DDRB
#define MISO_SetPullupActive()                   MISO_PORT |= _BV(MISO_BIT)
#define MISO_SetPullupInactive()                 MISO_PORT &= ~_BV(MISO_BIT)
#define MISO_ModeInput()                         MISO_DDR &= ~_BV(MISO_BIT)
#define MISO_IsInput()                           ((MISO_DDR & _BV(MISO_BIT)) == 0)
#define MISO_Get()                               (MISO_PIN & _BV(MISO_BIT))
#define MISO_GetBit()                            (MISO_Get() >> MISO_BIT)
#define MISO_IsInactive()                        (MISO_Get() == 0)
#define MISO_IsActive()                          (MISO_Get() != 0)
#define MISO_Init()                              { MISO_SetPullupActive(); MISO_ModeInput(); }

/* Frontpanel_SS -> PB0 (Output, Initially Inactive, Active-Low) */
#define Frontpanel_SS_BIT                        0
#define Frontpanel_SS_PIN                        PINB
#define Frontpanel_SS_PORT                       PORTB
#define Frontpanel_SS_DDR                        DDRB
#define Frontpanel_SS_ModeOutput()               Frontpanel_SS_DDR |= _BV(Frontpanel_SS_BIT)
#define Frontpanel_SS_IsOutput()                 ((Frontpanel_SS_DDR & _BV(Frontpanel_SS_BIT)) != 0)
#define Frontpanel_SS_SetHIGH()                  Frontpanel_SS_PORT |= _BV(Frontpanel_SS_BIT)
#define Frontpanel_SS_SetLOW()                   Frontpanel_SS_PORT &= ~_BV(Frontpanel_SS_BIT)
#define Frontpanel_SS_Get()                      (Frontpanel_SS_PIN & _BV(Frontpanel_SS_BIT))
#define Frontpanel_SS_SetInactive()              Frontpanel_SS_SetHIGH()
#define Frontpanel_SS_SetActive()                Frontpanel_SS_SetLOW()
#define Frontpanel_SS_Toggle()                   Frontpanel_SS_PORT ^= _BV(Frontpanel_SS_BIT)
#define Frontpanel_SS_SetConditional(condition)  if (condition) Frontpanel_SS_SetActive(); else Frontpanel_SS_SetInactive()
#define Frontpanel_SS_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Frontpanel_SS_SetActive(); } else if (conditionoff) { Frontpanel_SS_SetInactive(); } else if (conditiontoggle) { Frontpanel_SS_Toggle(); }
#define Frontpanel_SS_Pulse()                    { Frontpanel_SS_SetActive(); Frontpanel_SS_SetInactive(); }
#define Frontpanel_SS_PulseNop()                 { Frontpanel_SS_SetActive(); nop(); Frontpanel_SS_SetInactive(); }
#define Frontpanel_SS_IsInactive()               (Frontpanel_SS_Get() != 0)
#define Frontpanel_SS_IsActive()                 (Frontpanel_SS_Get() == 0)
#define Frontpanel_SS_Init()                     { Frontpanel_SS_SetInactive(); Frontpanel_SS_ModeOutput(); }

/* Frontpanel_RESET -> PD6 (Output, Initially Inactive, Active-Low) */
#define Frontpanel_RESET_BIT                     6
#define Frontpanel_RESET_PIN                     PIND
#define Frontpanel_RESET_PORT                    PORTD
#define Frontpanel_RESET_DDR                     DDRD
#define Frontpanel_RESET_ModeOutput()            Frontpanel_RESET_DDR |= _BV(Frontpanel_RESET_BIT)
#define Frontpanel_RESET_IsOutput()              ((Frontpanel_RESET_DDR & _BV(Frontpanel_RESET_BIT)) != 0)
#define Frontpanel_RESET_SetHIGH()               Frontpanel_RESET_PORT |= _BV(Frontpanel_RESET_BIT)
#define Frontpanel_RESET_SetLOW()                Frontpanel_RESET_PORT &= ~_BV(Frontpanel_RESET_BIT)
#define Frontpanel_RESET_Get()                   (Frontpanel_RESET_PIN & _BV(Frontpanel_RESET_BIT))
#define Frontpanel_RESET_SetInactive()           Frontpanel_RESET_SetHIGH()
#define Frontpanel_RESET_SetActive()             Frontpanel_RESET_SetLOW()
#define Frontpanel_RESET_Toggle()                Frontpanel_RESET_PORT ^= _BV(Frontpanel_RESET_BIT)
#define Frontpanel_RESET_SetConditional(condition) if (condition) Frontpanel_RESET_SetActive(); else Frontpanel_RESET_SetInactive()
#define Frontpanel_RESET_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Frontpanel_RESET_SetActive(); } else if (conditionoff) { Frontpanel_RESET_SetInactive(); } else if (conditiontoggle) { Frontpanel_RESET_Toggle(); }
#define Frontpanel_RESET_Pulse()                 { Frontpanel_RESET_SetActive(); Frontpanel_RESET_SetInactive(); }
#define Frontpanel_RESET_PulseNop()              { Frontpanel_RESET_SetActive(); nop(); Frontpanel_RESET_SetInactive(); }
#define Frontpanel_RESET_IsInactive()            (Frontpanel_RESET_Get() != 0)
#define Frontpanel_RESET_IsActive()              (Frontpanel_RESET_Get() == 0)
#define Frontpanel_RESET_Init()                  { Frontpanel_RESET_SetInactive(); Frontpanel_RESET_ModeOutput(); }

/* Frontpanel_IRQ -> PD7 (Input, Initially Pullup On) */
#define Frontpanel_IRQ_BIT                       7
#define Frontpanel_IRQ_PIN                       PIND
#define Frontpanel_IRQ_PORT                      PORTD
#define Frontpanel_IRQ_DDR                       DDRD
#define Frontpanel_IRQ_SetPullupActive()         Frontpanel_IRQ_PORT |= _BV(Frontpanel_IRQ_BIT)
#define Frontpanel_IRQ_SetPullupInactive()       Frontpanel_IRQ_PORT &= ~_BV(Frontpanel_IRQ_BIT)
#define Frontpanel_IRQ_ModeInput()               Frontpanel_IRQ_DDR &= ~_BV(Frontpanel_IRQ_BIT)
#define Frontpanel_IRQ_IsInput()                 ((Frontpanel_IRQ_DDR & _BV(Frontpanel_IRQ_BIT)) == 0)
#define Frontpanel_IRQ_Get()                     (Frontpanel_IRQ_PIN & _BV(Frontpanel_IRQ_BIT))
#define Frontpanel_IRQ_GetBit()                  (Frontpanel_IRQ_Get() >> Frontpanel_IRQ_BIT)
#define Frontpanel_IRQ_IsInactive()              (Frontpanel_IRQ_Get() == 0)
#define Frontpanel_IRQ_IsActive()                (Frontpanel_IRQ_Get() != 0)
#define Frontpanel_IRQ_Init()                    { Frontpanel_IRQ_SetPullupActive(); Frontpanel_IRQ_ModeInput(); }

/* Debug1 -> PF1 (Output, Initially Inactive) */
#define Debug1_BIT                               1
#define Debug1_PIN                               PINF
#define Debug1_PORT                              PORTF
#define Debug1_DDR                               DDRF
#define Debug1_ModeOutput()                      Debug1_DDR |= _BV(Debug1_BIT)
#define Debug1_IsOutput()                        ((Debug1_DDR & _BV(Debug1_BIT)) != 0)
#define Debug1_SetHIGH()                         Debug1_PORT |= _BV(Debug1_BIT)
#define Debug1_SetLOW()                          Debug1_PORT &= ~_BV(Debug1_BIT)
#define Debug1_Get()                             (Debug1_PIN & _BV(Debug1_BIT))
#define Debug1_SetInactive()                     Debug1_SetLOW()
#define Debug1_SetActive()                       Debug1_SetHIGH()
#define Debug1_Toggle()                          Debug1_PORT ^= _BV(Debug1_BIT)
#define Debug1_SetConditional(condition)         if (condition) Debug1_SetActive(); else Debug1_SetInactive()
#define Debug1_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Debug1_SetActive(); } else if (conditionoff) { Debug1_SetInactive(); } else if (conditiontoggle) { Debug1_Toggle(); }
#define Debug1_Pulse()                           { Debug1_SetActive(); Debug1_SetInactive(); }
#define Debug1_PulseNop()                        { Debug1_SetActive(); nop(); Debug1_SetInactive(); }
#define Debug1_IsInactive()                      (Debug1_Get() == 0)
#define Debug1_IsActive()                        (Debug1_Get() != 0)
#define Debug1_Init()                            { Debug1_SetInactive(); Debug1_ModeOutput(); }

/* Debug2 -> PF2 (Output, Initially Inactive) */
#define Debug2_BIT                               2
#define Debug2_PIN                               PINF
#define Debug2_PORT                              PORTF
#define Debug2_DDR                               DDRF
#define Debug2_ModeOutput()                      Debug2_DDR |= _BV(Debug2_BIT)
#define Debug2_IsOutput()                        ((Debug2_DDR & _BV(Debug2_BIT)) != 0)
#define Debug2_SetHIGH()                         Debug2_PORT |= _BV(Debug2_BIT)
#define Debug2_SetLOW()                          Debug2_PORT &= ~_BV(Debug2_BIT)
#define Debug2_Get()                             (Debug2_PIN & _BV(Debug2_BIT))
#define Debug2_SetInactive()                     Debug2_SetLOW()
#define Debug2_SetActive()                       Debug2_SetHIGH()
#define Debug2_Toggle()                          Debug2_PORT ^= _BV(Debug2_BIT)
#define Debug2_SetConditional(condition)         if (condition) Debug2_SetActive(); else Debug2_SetInactive()
#define Debug2_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Debug2_SetActive(); } else if (conditionoff) { Debug2_SetInactive(); } else if (conditiontoggle) { Debug2_Toggle(); }
#define Debug2_Pulse()                           { Debug2_SetActive(); Debug2_SetInactive(); }
#define Debug2_PulseNop()                        { Debug2_SetActive(); nop(); Debug2_SetInactive(); }
#define Debug2_IsInactive()                      (Debug2_Get() == 0)
#define Debug2_IsActive()                        (Debug2_Get() != 0)
#define Debug2_Init()                            { Debug2_SetInactive(); Debug2_ModeOutput(); }

/* Rel1 -> PA3 (Output, Initially Inactive) */
#define Rel1_BIT                                 3
#define Rel1_PIN                                 PINA
#define Rel1_PORT                                PORTA
#define Rel1_DDR                                 DDRA
#define Rel1_ModeOutput()                        Rel1_DDR |= _BV(Rel1_BIT)
#define Rel1_IsOutput()                          ((Rel1_DDR & _BV(Rel1_BIT)) != 0)
#define Rel1_SetHIGH()                           Rel1_PORT |= _BV(Rel1_BIT)
#define Rel1_SetLOW()                            Rel1_PORT &= ~_BV(Rel1_BIT)
#define Rel1_Get()                               (Rel1_PIN & _BV(Rel1_BIT))
#define Rel1_SetInactive()                       Rel1_SetLOW()
#define Rel1_SetActive()                         Rel1_SetHIGH()
#define Rel1_Toggle()                            Rel1_PORT ^= _BV(Rel1_BIT)
#define Rel1_SetConditional(condition)           if (condition) Rel1_SetActive(); else Rel1_SetInactive()
#define Rel1_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel1_SetActive(); } else if (conditionoff) { Rel1_SetInactive(); } else if (conditiontoggle) { Rel1_Toggle(); }
#define Rel1_Pulse()                             { Rel1_SetActive(); Rel1_SetInactive(); }
#define Rel1_PulseNop()                          { Rel1_SetActive(); nop(); Rel1_SetInactive(); }
#define Rel1_IsInactive()                        (Rel1_Get() == 0)
#define Rel1_IsActive()                          (Rel1_Get() != 0)
#define Rel1_Init()                              { Rel1_SetInactive(); Rel1_ModeOutput(); }

/* Rel2 -> PA4 (Output, Initially Inactive) */
#define Rel2_BIT                                 4
#define Rel2_PIN                                 PINA
#define Rel2_PORT                                PORTA
#define Rel2_DDR                                 DDRA
#define Rel2_ModeOutput()                        Rel2_DDR |= _BV(Rel2_BIT)
#define Rel2_IsOutput()                          ((Rel2_DDR & _BV(Rel2_BIT)) != 0)
#define Rel2_SetHIGH()                           Rel2_PORT |= _BV(Rel2_BIT)
#define Rel2_SetLOW()                            Rel2_PORT &= ~_BV(Rel2_BIT)
#define Rel2_Get()                               (Rel2_PIN & _BV(Rel2_BIT))
#define Rel2_SetInactive()                       Rel2_SetLOW()
#define Rel2_SetActive()                         Rel2_SetHIGH()
#define Rel2_Toggle()                            Rel2_PORT ^= _BV(Rel2_BIT)
#define Rel2_SetConditional(condition)           if (condition) Rel2_SetActive(); else Rel2_SetInactive()
#define Rel2_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel2_SetActive(); } else if (conditionoff) { Rel2_SetInactive(); } else if (conditiontoggle) { Rel2_Toggle(); }
#define Rel2_Pulse()                             { Rel2_SetActive(); Rel2_SetInactive(); }
#define Rel2_PulseNop()                          { Rel2_SetActive(); nop(); Rel2_SetInactive(); }
#define Rel2_IsInactive()                        (Rel2_Get() == 0)
#define Rel2_IsActive()                          (Rel2_Get() != 0)
#define Rel2_Init()                              { Rel2_SetInactive(); Rel2_ModeOutput(); }

/* Rel3 -> PA5 (Output, Initially Inactive) */
#define Rel3_BIT                                 5
#define Rel3_PIN                                 PINA
#define Rel3_PORT                                PORTA
#define Rel3_DDR                                 DDRA
#define Rel3_ModeOutput()                        Rel3_DDR |= _BV(Rel3_BIT)
#define Rel3_IsOutput()                          ((Rel3_DDR & _BV(Rel3_BIT)) != 0)
#define Rel3_SetHIGH()                           Rel3_PORT |= _BV(Rel3_BIT)
#define Rel3_SetLOW()                            Rel3_PORT &= ~_BV(Rel3_BIT)
#define Rel3_Get()                               (Rel3_PIN & _BV(Rel3_BIT))
#define Rel3_SetInactive()                       Rel3_SetLOW()
#define Rel3_SetActive()                         Rel3_SetHIGH()
#define Rel3_Toggle()                            Rel3_PORT ^= _BV(Rel3_BIT)
#define Rel3_SetConditional(condition)           if (condition) Rel3_SetActive(); else Rel3_SetInactive()
#define Rel3_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel3_SetActive(); } else if (conditionoff) { Rel3_SetInactive(); } else if (conditiontoggle) { Rel3_Toggle(); }
#define Rel3_Pulse()                             { Rel3_SetActive(); Rel3_SetInactive(); }
#define Rel3_PulseNop()                          { Rel3_SetActive(); nop(); Rel3_SetInactive(); }
#define Rel3_IsInactive()                        (Rel3_Get() == 0)
#define Rel3_IsActive()                          (Rel3_Get() != 0)
#define Rel3_Init()                              { Rel3_SetInactive(); Rel3_ModeOutput(); }

/* Rel4 -> PA6 (Output, Initially Inactive) */
#define Rel4_BIT                                 6
#define Rel4_PIN                                 PINA
#define Rel4_PORT                                PORTA
#define Rel4_DDR                                 DDRA
#define Rel4_ModeOutput()                        Rel4_DDR |= _BV(Rel4_BIT)
#define Rel4_IsOutput()                          ((Rel4_DDR & _BV(Rel4_BIT)) != 0)
#define Rel4_SetHIGH()                           Rel4_PORT |= _BV(Rel4_BIT)
#define Rel4_SetLOW()                            Rel4_PORT &= ~_BV(Rel4_BIT)
#define Rel4_Get()                               (Rel4_PIN & _BV(Rel4_BIT))
#define Rel4_SetInactive()                       Rel4_SetLOW()
#define Rel4_SetActive()                         Rel4_SetHIGH()
#define Rel4_Toggle()                            Rel4_PORT ^= _BV(Rel4_BIT)
#define Rel4_SetConditional(condition)           if (condition) Rel4_SetActive(); else Rel4_SetInactive()
#define Rel4_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel4_SetActive(); } else if (conditionoff) { Rel4_SetInactive(); } else if (conditiontoggle) { Rel4_Toggle(); }
#define Rel4_Pulse()                             { Rel4_SetActive(); Rel4_SetInactive(); }
#define Rel4_PulseNop()                          { Rel4_SetActive(); nop(); Rel4_SetInactive(); }
#define Rel4_IsInactive()                        (Rel4_Get() == 0)
#define Rel4_IsActive()                          (Rel4_Get() != 0)
#define Rel4_Init()                              { Rel4_SetInactive(); Rel4_ModeOutput(); }

/* Rel5 -> PA7 (Output, Initially Inactive) */
#define Rel5_BIT                                 7
#define Rel5_PIN                                 PINA
#define Rel5_PORT                                PORTA
#define Rel5_DDR                                 DDRA
#define Rel5_ModeOutput()                        Rel5_DDR |= _BV(Rel5_BIT)
#define Rel5_IsOutput()                          ((Rel5_DDR & _BV(Rel5_BIT)) != 0)
#define Rel5_SetHIGH()                           Rel5_PORT |= _BV(Rel5_BIT)
#define Rel5_SetLOW()                            Rel5_PORT &= ~_BV(Rel5_BIT)
#define Rel5_Get()                               (Rel5_PIN & _BV(Rel5_BIT))
#define Rel5_SetInactive()                       Rel5_SetLOW()
#define Rel5_SetActive()                         Rel5_SetHIGH()
#define Rel5_Toggle()                            Rel5_PORT ^= _BV(Rel5_BIT)
#define Rel5_SetConditional(condition)           if (condition) Rel5_SetActive(); else Rel5_SetInactive()
#define Rel5_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel5_SetActive(); } else if (conditionoff) { Rel5_SetInactive(); } else if (conditiontoggle) { Rel5_Toggle(); }
#define Rel5_Pulse()                             { Rel5_SetActive(); Rel5_SetInactive(); }
#define Rel5_PulseNop()                          { Rel5_SetActive(); nop(); Rel5_SetInactive(); }
#define Rel5_IsInactive()                        (Rel5_Get() == 0)
#define Rel5_IsActive()                          (Rel5_Get() != 0)
#define Rel5_Init()                              { Rel5_SetInactive(); Rel5_ModeOutput(); }

/* Rel6 -> PG2 (Output, Initially Inactive) */
#define Rel6_BIT                                 2
#define Rel6_PIN                                 PING
#define Rel6_PORT                                PORTG
#define Rel6_DDR                                 DDRG
#define Rel6_ModeOutput()                        Rel6_DDR |= _BV(Rel6_BIT)
#define Rel6_IsOutput()                          ((Rel6_DDR & _BV(Rel6_BIT)) != 0)
#define Rel6_SetHIGH()                           Rel6_PORT |= _BV(Rel6_BIT)
#define Rel6_SetLOW()                            Rel6_PORT &= ~_BV(Rel6_BIT)
#define Rel6_Get()                               (Rel6_PIN & _BV(Rel6_BIT))
#define Rel6_SetInactive()                       Rel6_SetLOW()
#define Rel6_SetActive()                         Rel6_SetHIGH()
#define Rel6_Toggle()                            Rel6_PORT ^= _BV(Rel6_BIT)
#define Rel6_SetConditional(condition)           if (condition) Rel6_SetActive(); else Rel6_SetInactive()
#define Rel6_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel6_SetActive(); } else if (conditionoff) { Rel6_SetInactive(); } else if (conditiontoggle) { Rel6_Toggle(); }
#define Rel6_Pulse()                             { Rel6_SetActive(); Rel6_SetInactive(); }
#define Rel6_PulseNop()                          { Rel6_SetActive(); nop(); Rel6_SetInactive(); }
#define Rel6_IsInactive()                        (Rel6_Get() == 0)
#define Rel6_IsActive()                          (Rel6_Get() != 0)
#define Rel6_Init()                              { Rel6_SetInactive(); Rel6_ModeOutput(); }

/* Rel7 -> PC7 (Output, Initially Inactive) */
#define Rel7_BIT                                 7
#define Rel7_PIN                                 PINC
#define Rel7_PORT                                PORTC
#define Rel7_DDR                                 DDRC
#define Rel7_ModeOutput()                        Rel7_DDR |= _BV(Rel7_BIT)
#define Rel7_IsOutput()                          ((Rel7_DDR & _BV(Rel7_BIT)) != 0)
#define Rel7_SetHIGH()                           Rel7_PORT |= _BV(Rel7_BIT)
#define Rel7_SetLOW()                            Rel7_PORT &= ~_BV(Rel7_BIT)
#define Rel7_Get()                               (Rel7_PIN & _BV(Rel7_BIT))
#define Rel7_SetInactive()                       Rel7_SetLOW()
#define Rel7_SetActive()                         Rel7_SetHIGH()
#define Rel7_Toggle()                            Rel7_PORT ^= _BV(Rel7_BIT)
#define Rel7_SetConditional(condition)           if (condition) Rel7_SetActive(); else Rel7_SetInactive()
#define Rel7_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel7_SetActive(); } else if (conditionoff) { Rel7_SetInactive(); } else if (conditiontoggle) { Rel7_Toggle(); }
#define Rel7_Pulse()                             { Rel7_SetActive(); Rel7_SetInactive(); }
#define Rel7_PulseNop()                          { Rel7_SetActive(); nop(); Rel7_SetInactive(); }
#define Rel7_IsInactive()                        (Rel7_Get() == 0)
#define Rel7_IsActive()                          (Rel7_Get() != 0)
#define Rel7_Init()                              { Rel7_SetInactive(); Rel7_ModeOutput(); }

/* Rel8 -> PC6 (Output, Initially Inactive) */
#define Rel8_BIT                                 6
#define Rel8_PIN                                 PINC
#define Rel8_PORT                                PORTC
#define Rel8_DDR                                 DDRC
#define Rel8_ModeOutput()                        Rel8_DDR |= _BV(Rel8_BIT)
#define Rel8_IsOutput()                          ((Rel8_DDR & _BV(Rel8_BIT)) != 0)
#define Rel8_SetHIGH()                           Rel8_PORT |= _BV(Rel8_BIT)
#define Rel8_SetLOW()                            Rel8_PORT &= ~_BV(Rel8_BIT)
#define Rel8_Get()                               (Rel8_PIN & _BV(Rel8_BIT))
#define Rel8_SetInactive()                       Rel8_SetLOW()
#define Rel8_SetActive()                         Rel8_SetHIGH()
#define Rel8_Toggle()                            Rel8_PORT ^= _BV(Rel8_BIT)
#define Rel8_SetConditional(condition)           if (condition) Rel8_SetActive(); else Rel8_SetInactive()
#define Rel8_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel8_SetActive(); } else if (conditionoff) { Rel8_SetInactive(); } else if (conditiontoggle) { Rel8_Toggle(); }
#define Rel8_Pulse()                             { Rel8_SetActive(); Rel8_SetInactive(); }
#define Rel8_PulseNop()                          { Rel8_SetActive(); nop(); Rel8_SetInactive(); }
#define Rel8_IsInactive()                        (Rel8_Get() == 0)
#define Rel8_IsActive()                          (Rel8_Get() != 0)
#define Rel8_Init()                              { Rel8_SetInactive(); Rel8_ModeOutput(); }

/* Rel9 -> PC5 (Output, Initially Inactive) */
#define Rel9_BIT                                 5
#define Rel9_PIN                                 PINC
#define Rel9_PORT                                PORTC
#define Rel9_DDR                                 DDRC
#define Rel9_ModeOutput()                        Rel9_DDR |= _BV(Rel9_BIT)
#define Rel9_IsOutput()                          ((Rel9_DDR & _BV(Rel9_BIT)) != 0)
#define Rel9_SetHIGH()                           Rel9_PORT |= _BV(Rel9_BIT)
#define Rel9_SetLOW()                            Rel9_PORT &= ~_BV(Rel9_BIT)
#define Rel9_Get()                               (Rel9_PIN & _BV(Rel9_BIT))
#define Rel9_SetInactive()                       Rel9_SetLOW()
#define Rel9_SetActive()                         Rel9_SetHIGH()
#define Rel9_Toggle()                            Rel9_PORT ^= _BV(Rel9_BIT)
#define Rel9_SetConditional(condition)           if (condition) Rel9_SetActive(); else Rel9_SetInactive()
#define Rel9_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel9_SetActive(); } else if (conditionoff) { Rel9_SetInactive(); } else if (conditiontoggle) { Rel9_Toggle(); }
#define Rel9_Pulse()                             { Rel9_SetActive(); Rel9_SetInactive(); }
#define Rel9_PulseNop()                          { Rel9_SetActive(); nop(); Rel9_SetInactive(); }
#define Rel9_IsInactive()                        (Rel9_Get() == 0)
#define Rel9_IsActive()                          (Rel9_Get() != 0)
#define Rel9_Init()                              { Rel9_SetInactive(); Rel9_ModeOutput(); }

/* Rel10 -> PC4 (Output, Initially Inactive) */
#define Rel10_BIT                                4
#define Rel10_PIN                                PINC
#define Rel10_PORT                               PORTC
#define Rel10_DDR                                DDRC
#define Rel10_ModeOutput()                       Rel10_DDR |= _BV(Rel10_BIT)
#define Rel10_IsOutput()                         ((Rel10_DDR & _BV(Rel10_BIT)) != 0)
#define Rel10_SetHIGH()                          Rel10_PORT |= _BV(Rel10_BIT)
#define Rel10_SetLOW()                           Rel10_PORT &= ~_BV(Rel10_BIT)
#define Rel10_Get()                              (Rel10_PIN & _BV(Rel10_BIT))
#define Rel10_SetInactive()                      Rel10_SetLOW()
#define Rel10_SetActive()                        Rel10_SetHIGH()
#define Rel10_Toggle()                           Rel10_PORT ^= _BV(Rel10_BIT)
#define Rel10_SetConditional(condition)          if (condition) Rel10_SetActive(); else Rel10_SetInactive()
#define Rel10_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel10_SetActive(); } else if (conditionoff) { Rel10_SetInactive(); } else if (conditiontoggle) { Rel10_Toggle(); }
#define Rel10_Pulse()                            { Rel10_SetActive(); Rel10_SetInactive(); }
#define Rel10_PulseNop()                         { Rel10_SetActive(); nop(); Rel10_SetInactive(); }
#define Rel10_IsInactive()                       (Rel10_Get() == 0)
#define Rel10_IsActive()                         (Rel10_Get() != 0)
#define Rel10_Init()                             { Rel10_SetInactive(); Rel10_ModeOutput(); }

/* Rel11 -> PC3 (Output, Initially Inactive) */
#define Rel11_BIT                                3
#define Rel11_PIN                                PINC
#define Rel11_PORT                               PORTC
#define Rel11_DDR                                DDRC
#define Rel11_ModeOutput()                       Rel11_DDR |= _BV(Rel11_BIT)
#define Rel11_IsOutput()                         ((Rel11_DDR & _BV(Rel11_BIT)) != 0)
#define Rel11_SetHIGH()                          Rel11_PORT |= _BV(Rel11_BIT)
#define Rel11_SetLOW()                           Rel11_PORT &= ~_BV(Rel11_BIT)
#define Rel11_Get()                              (Rel11_PIN & _BV(Rel11_BIT))
#define Rel11_SetInactive()                      Rel11_SetLOW()
#define Rel11_SetActive()                        Rel11_SetHIGH()
#define Rel11_Toggle()                           Rel11_PORT ^= _BV(Rel11_BIT)
#define Rel11_SetConditional(condition)          if (condition) Rel11_SetActive(); else Rel11_SetInactive()
#define Rel11_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel11_SetActive(); } else if (conditionoff) { Rel11_SetInactive(); } else if (conditiontoggle) { Rel11_Toggle(); }
#define Rel11_Pulse()                            { Rel11_SetActive(); Rel11_SetInactive(); }
#define Rel11_PulseNop()                         { Rel11_SetActive(); nop(); Rel11_SetInactive(); }
#define Rel11_IsInactive()                       (Rel11_Get() == 0)
#define Rel11_IsActive()                         (Rel11_Get() != 0)
#define Rel11_Init()                             { Rel11_SetInactive(); Rel11_ModeOutput(); }

/* Rel12 -> PC2 (Output, Initially Inactive) */
#define Rel12_BIT                                2
#define Rel12_PIN                                PINC
#define Rel12_PORT                               PORTC
#define Rel12_DDR                                DDRC
#define Rel12_ModeOutput()                       Rel12_DDR |= _BV(Rel12_BIT)
#define Rel12_IsOutput()                         ((Rel12_DDR & _BV(Rel12_BIT)) != 0)
#define Rel12_SetHIGH()                          Rel12_PORT |= _BV(Rel12_BIT)
#define Rel12_SetLOW()                           Rel12_PORT &= ~_BV(Rel12_BIT)
#define Rel12_Get()                              (Rel12_PIN & _BV(Rel12_BIT))
#define Rel12_SetInactive()                      Rel12_SetLOW()
#define Rel12_SetActive()                        Rel12_SetHIGH()
#define Rel12_Toggle()                           Rel12_PORT ^= _BV(Rel12_BIT)
#define Rel12_SetConditional(condition)          if (condition) Rel12_SetActive(); else Rel12_SetInactive()
#define Rel12_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Rel12_SetActive(); } else if (conditionoff) { Rel12_SetInactive(); } else if (conditiontoggle) { Rel12_Toggle(); }
#define Rel12_Pulse()                            { Rel12_SetActive(); Rel12_SetInactive(); }
#define Rel12_PulseNop()                         { Rel12_SetActive(); nop(); Rel12_SetInactive(); }
#define Rel12_IsInactive()                       (Rel12_Get() == 0)
#define Rel12_IsActive()                         (Rel12_Get() != 0)
#define Rel12_Init()                             { Rel12_SetInactive(); Rel12_ModeOutput(); }

/* Output5V -> PC1 (Output, Initially Inactive) */
#define Output5V_BIT                             1
#define Output5V_PIN                             PINC
#define Output5V_PORT                            PORTC
#define Output5V_DDR                             DDRC
#define Output5V_ModeOutput()                    Output5V_DDR |= _BV(Output5V_BIT)
#define Output5V_IsOutput()                      ((Output5V_DDR & _BV(Output5V_BIT)) != 0)
#define Output5V_SetHIGH()                       Output5V_PORT |= _BV(Output5V_BIT)
#define Output5V_SetLOW()                        Output5V_PORT &= ~_BV(Output5V_BIT)
#define Output5V_Get()                           (Output5V_PIN & _BV(Output5V_BIT))
#define Output5V_SetInactive()                   Output5V_SetLOW()
#define Output5V_SetActive()                     Output5V_SetHIGH()
#define Output5V_Toggle()                        Output5V_PORT ^= _BV(Output5V_BIT)
#define Output5V_SetConditional(condition)       if (condition) Output5V_SetActive(); else Output5V_SetInactive()
#define Output5V_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Output5V_SetActive(); } else if (conditionoff) { Output5V_SetInactive(); } else if (conditiontoggle) { Output5V_Toggle(); }
#define Output5V_Pulse()                         { Output5V_SetActive(); Output5V_SetInactive(); }
#define Output5V_PulseNop()                      { Output5V_SetActive(); nop(); Output5V_SetInactive(); }
#define Output5V_IsInactive()                    (Output5V_Get() == 0)
#define Output5V_IsActive()                      (Output5V_Get() != 0)
#define Output5V_Init()                          { Output5V_SetInactive(); Output5V_ModeOutput(); }

/* Buzzer -> PB7 (Output, Initially Inactive) */
#define Buzzer_BIT                               7
#define Buzzer_PIN                               PINB
#define Buzzer_PORT                              PORTB
#define Buzzer_DDR                               DDRB
#define Buzzer_ModeOutput()                      Buzzer_DDR |= _BV(Buzzer_BIT)
#define Buzzer_IsOutput()                        ((Buzzer_DDR & _BV(Buzzer_BIT)) != 0)
#define Buzzer_SetHIGH()                         Buzzer_PORT |= _BV(Buzzer_BIT)
#define Buzzer_SetLOW()                          Buzzer_PORT &= ~_BV(Buzzer_BIT)
#define Buzzer_Get()                             (Buzzer_PIN & _BV(Buzzer_BIT))
#define Buzzer_SetInactive()                     Buzzer_SetLOW()
#define Buzzer_SetActive()                       Buzzer_SetHIGH()
#define Buzzer_Toggle()                          Buzzer_PORT ^= _BV(Buzzer_BIT)
#define Buzzer_SetConditional(condition)         if (condition) Buzzer_SetActive(); else Buzzer_SetInactive()
#define Buzzer_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Buzzer_SetActive(); } else if (conditionoff) { Buzzer_SetInactive(); } else if (conditiontoggle) { Buzzer_Toggle(); }
#define Buzzer_Pulse()                           { Buzzer_SetActive(); Buzzer_SetInactive(); }
#define Buzzer_PulseNop()                        { Buzzer_SetActive(); nop(); Buzzer_SetInactive(); }
#define Buzzer_IsInactive()                      (Buzzer_Get() == 0)
#define Buzzer_IsActive()                        (Buzzer_Get() != 0)
#define Buzzer_Init()                            { Buzzer_SetInactive(); Buzzer_ModeOutput(); }

/* Voltmeter -> PB5 (Output, Initially Inactive) */
#define Voltmeter_BIT                            5
#define Voltmeter_PIN                            PINB
#define Voltmeter_PORT                           PORTB
#define Voltmeter_DDR                            DDRB
#define Voltmeter_ModeOutput()                   Voltmeter_DDR |= _BV(Voltmeter_BIT)
#define Voltmeter_IsOutput()                     ((Voltmeter_DDR & _BV(Voltmeter_BIT)) != 0)
#define Voltmeter_SetHIGH()                      Voltmeter_PORT |= _BV(Voltmeter_BIT)
#define Voltmeter_SetLOW()                       Voltmeter_PORT &= ~_BV(Voltmeter_BIT)
#define Voltmeter_Get()                          (Voltmeter_PIN & _BV(Voltmeter_BIT))
#define Voltmeter_SetInactive()                  Voltmeter_SetLOW()
#define Voltmeter_SetActive()                    Voltmeter_SetHIGH()
#define Voltmeter_Toggle()                       Voltmeter_PORT ^= _BV(Voltmeter_BIT)
#define Voltmeter_SetConditional(condition)      if (condition) Voltmeter_SetActive(); else Voltmeter_SetInactive()
#define Voltmeter_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { Voltmeter_SetActive(); } else if (conditionoff) { Voltmeter_SetInactive(); } else if (conditiontoggle) { Voltmeter_Toggle(); }
#define Voltmeter_Pulse()                        { Voltmeter_SetActive(); Voltmeter_SetInactive(); }
#define Voltmeter_PulseNop()                     { Voltmeter_SetActive(); nop(); Voltmeter_SetInactive(); }
#define Voltmeter_IsInactive()                   (Voltmeter_Get() == 0)
#define Voltmeter_IsActive()                     (Voltmeter_Get() != 0)
#define Voltmeter_Init()                         { Voltmeter_SetInactive(); Voltmeter_ModeOutput(); }

/* Rotary -> PA2 (Input, Initially Pullup On) */
#define Rotary_BIT                               2
#define Rotary_PIN                               PINA
#define Rotary_PORT                              PORTA
#define Rotary_DDR                               DDRA
#define Rotary_SetPullupActive()                 Rotary_PORT |= _BV(Rotary_BIT)
#define Rotary_SetPullupInactive()               Rotary_PORT &= ~_BV(Rotary_BIT)
#define Rotary_ModeInput()                       Rotary_DDR &= ~_BV(Rotary_BIT)
#define Rotary_IsInput()                         ((Rotary_DDR & _BV(Rotary_BIT)) == 0)
#define Rotary_Get()                             (Rotary_PIN & _BV(Rotary_BIT))
#define Rotary_GetBit()                          (Rotary_Get() >> Rotary_BIT)
#define Rotary_IsInactive()                      (Rotary_Get() == 0)
#define Rotary_IsActive()                        (Rotary_Get() != 0)
#define Rotary_Init()                            { Rotary_SetPullupActive(); Rotary_ModeInput(); }

/* Switch_On -> PF3 (Input, Initially Pullup On, Active-Low) */
#define Switch_On_BIT                            3
#define Switch_On_PIN                            PINF
#define Switch_On_PORT                           PORTF
#define Switch_On_DDR                            DDRF
#define Switch_On_SetPullupActive()              Switch_On_PORT |= _BV(Switch_On_BIT)
#define Switch_On_SetPullupInactive()            Switch_On_PORT &= ~_BV(Switch_On_BIT)
#define Switch_On_ModeInput()                    Switch_On_DDR &= ~_BV(Switch_On_BIT)
#define Switch_On_IsInput()                      ((Switch_On_DDR & _BV(Switch_On_BIT)) == 0)
#define Switch_On_Get()                          (Switch_On_PIN & _BV(Switch_On_BIT))
#define Switch_On_GetBit()                       (Switch_On_Get() >> Switch_On_BIT)
#define Switch_On_IsInactive()                   (Switch_On_Get() != 0)
#define Switch_On_IsActive()                     (Switch_On_Get() == 0)
#define Switch_On_Init()                         { Switch_On_SetPullupActive(); Switch_On_ModeInput(); }

/* Switch_Off -> PF5 (Input, Initially Pullup On) */
#define Switch_Off_BIT                           5
#define Switch_Off_PIN                           PINF
#define Switch_Off_PORT                          PORTF
#define Switch_Off_DDR                           DDRF
#define Switch_Off_SetPullupActive()             Switch_Off_PORT |= _BV(Switch_Off_BIT)
#define Switch_Off_SetPullupInactive()           Switch_Off_PORT &= ~_BV(Switch_Off_BIT)
#define Switch_Off_ModeInput()                   Switch_Off_DDR &= ~_BV(Switch_Off_BIT)
#define Switch_Off_IsInput()                     ((Switch_Off_DDR & _BV(Switch_Off_BIT)) == 0)
#define Switch_Off_Get()                         (Switch_Off_PIN & _BV(Switch_Off_BIT))
#define Switch_Off_GetBit()                      (Switch_Off_Get() >> Switch_Off_BIT)
#define Switch_Off_IsInactive()                  (Switch_Off_Get() == 0)
#define Switch_Off_IsActive()                    (Switch_Off_Get() != 0)
#define Switch_Off_Init()                        { Switch_Off_SetPullupActive(); Switch_Off_ModeInput(); }

/* Switch_EmergencyOff -> PF4 (Input, Initially Pullup On) */
#define Switch_EmergencyOff_BIT                  4
#define Switch_EmergencyOff_PIN                  PINF
#define Switch_EmergencyOff_PORT                 PORTF
#define Switch_EmergencyOff_DDR                  DDRF
#define Switch_EmergencyOff_SetPullupActive()    Switch_EmergencyOff_PORT |= _BV(Switch_EmergencyOff_BIT)
#define Switch_EmergencyOff_SetPullupInactive()  Switch_EmergencyOff_PORT &= ~_BV(Switch_EmergencyOff_BIT)
#define Switch_EmergencyOff_ModeInput()          Switch_EmergencyOff_DDR &= ~_BV(Switch_EmergencyOff_BIT)
#define Switch_EmergencyOff_IsInput()            ((Switch_EmergencyOff_DDR & _BV(Switch_EmergencyOff_BIT)) == 0)
#define Switch_EmergencyOff_Get()                (Switch_EmergencyOff_PIN & _BV(Switch_EmergencyOff_BIT))
#define Switch_EmergencyOff_GetBit()             (Switch_EmergencyOff_Get() >> Switch_EmergencyOff_BIT)
#define Switch_EmergencyOff_IsInactive()         (Switch_EmergencyOff_Get() == 0)
#define Switch_EmergencyOff_IsActive()           (Switch_EmergencyOff_Get() != 0)
#define Switch_EmergencyOff_Init()               { Switch_EmergencyOff_SetPullupActive(); Switch_EmergencyOff_ModeInput(); }

/* TripRCD1 -> PA0 (Output, Initially Inactive) */
#define TripRCD1_BIT                             0
#define TripRCD1_PIN                             PINA
#define TripRCD1_PORT                            PORTA
#define TripRCD1_DDR                             DDRA
#define TripRCD1_ModeOutput()                    TripRCD1_DDR |= _BV(TripRCD1_BIT)
#define TripRCD1_IsOutput()                      ((TripRCD1_DDR & _BV(TripRCD1_BIT)) != 0)
#define TripRCD1_SetHIGH()                       TripRCD1_PORT |= _BV(TripRCD1_BIT)
#define TripRCD1_SetLOW()                        TripRCD1_PORT &= ~_BV(TripRCD1_BIT)
#define TripRCD1_Get()                           (TripRCD1_PIN & _BV(TripRCD1_BIT))
#define TripRCD1_SetInactive()                   TripRCD1_SetLOW()
#define TripRCD1_SetActive()                     TripRCD1_SetHIGH()
#define TripRCD1_Toggle()                        TripRCD1_PORT ^= _BV(TripRCD1_BIT)
#define TripRCD1_SetConditional(condition)       if (condition) TripRCD1_SetActive(); else TripRCD1_SetInactive()
#define TripRCD1_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { TripRCD1_SetActive(); } else if (conditionoff) { TripRCD1_SetInactive(); } else if (conditiontoggle) { TripRCD1_Toggle(); }
#define TripRCD1_Pulse()                         { TripRCD1_SetActive(); TripRCD1_SetInactive(); }
#define TripRCD1_PulseNop()                      { TripRCD1_SetActive(); nop(); TripRCD1_SetInactive(); }
#define TripRCD1_IsInactive()                    (TripRCD1_Get() == 0)
#define TripRCD1_IsActive()                      (TripRCD1_Get() != 0)
#define TripRCD1_Init()                          { TripRCD1_SetInactive(); TripRCD1_ModeOutput(); }

/* TripRCD2 -> PA1 (Output, Initially Inactive) */
#define TripRCD2_BIT                             1
#define TripRCD2_PIN                             PINA
#define TripRCD2_PORT                            PORTA
#define TripRCD2_DDR                             DDRA
#define TripRCD2_ModeOutput()                    TripRCD2_DDR |= _BV(TripRCD2_BIT)
#define TripRCD2_IsOutput()                      ((TripRCD2_DDR & _BV(TripRCD2_BIT)) != 0)
#define TripRCD2_SetHIGH()                       TripRCD2_PORT |= _BV(TripRCD2_BIT)
#define TripRCD2_SetLOW()                        TripRCD2_PORT &= ~_BV(TripRCD2_BIT)
#define TripRCD2_Get()                           (TripRCD2_PIN & _BV(TripRCD2_BIT))
#define TripRCD2_SetInactive()                   TripRCD2_SetLOW()
#define TripRCD2_SetActive()                     TripRCD2_SetHIGH()
#define TripRCD2_Toggle()                        TripRCD2_PORT ^= _BV(TripRCD2_BIT)
#define TripRCD2_SetConditional(condition)       if (condition) TripRCD2_SetActive(); else TripRCD2_SetInactive()
#define TripRCD2_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { TripRCD2_SetActive(); } else if (conditionoff) { TripRCD2_SetInactive(); } else if (conditiontoggle) { TripRCD2_Toggle(); }
#define TripRCD2_Pulse()                         { TripRCD2_SetActive(); TripRCD2_SetInactive(); }
#define TripRCD2_PulseNop()                      { TripRCD2_SetActive(); nop(); TripRCD2_SetInactive(); }
#define TripRCD2_IsInactive()                    (TripRCD2_Get() == 0)
#define TripRCD2_IsActive()                      (TripRCD2_Get() != 0)
#define TripRCD2_Init()                          { TripRCD2_SetInactive(); TripRCD2_ModeOutput(); }

#define initHAL() {\
		RS232_RX_Init();\
		RS232_TX_Init();\
		SCK_Init();\
		MOSI_Init();\
		MISO_Init();\
		Frontpanel_SS_Init();\
		Frontpanel_RESET_Init();\
		Frontpanel_IRQ_Init();\
		Debug1_Init();\
		Debug2_Init();\
		Rel1_Init();\
		Rel2_Init();\
		Rel3_Init();\
		Rel4_Init();\
		Rel5_Init();\
		Rel6_Init();\
		Rel7_Init();\
		Rel8_Init();\
		Rel9_Init();\
		Rel10_Init();\
		Rel11_Init();\
		Rel12_Init();\
		Output5V_Init();\
		Buzzer_Init();\
		Voltmeter_Init();\
		Rotary_Init();\
		Switch_On_Init();\
		Switch_Off_Init();\
		Switch_EmergencyOff_Init();\
		TripRCD1_Init();\
		TripRCD2_Init();\
}

#endif
