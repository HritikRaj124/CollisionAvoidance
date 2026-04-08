#ifndef FSM_H
#define FSM_H

#include <stdint.h>

#define STATE_IDLE        0
#define STATE_BRAKING     1
#define STATE_FULL_BRAKE  2
#define STATE_RELEASED    3

typedef struct
{
    uint8_t state;
    uint8_t target_velocity;
} fsm_output_t;

fsm_output_t fsm_update(uint8_t current_state,
                        uint8_t velocity,
                        uint8_t distance);

#endif // FSM_H
