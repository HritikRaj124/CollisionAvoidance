#include "fsm.h"

fsm_output_t fsm_update(uint8_t current_state,
                        uint8_t velocity,
                        uint8_t distance)
{
    fsm_output_t out;

    if (velocity == 0)
    {
        out.state = STATE_RELEASED;
        out.target_velocity = 0;
    }
    else if (distance == 0)
    {
        out.state = STATE_FULL_BRAKE;
        out.target_velocity = 0;
    }
    else if (distance <= 20)
    {
        out.state = STATE_BRAKING;
        out.target_velocity = 0;     // Emergency slow-down
    }
    else if (distance <= 50)
    {
        out.state = STATE_BRAKING;
        out.target_velocity = 30;    // Controlled braking
    }
    else
    {
        out.state = STATE_IDLE;
        out.target_velocity = 100;   // Full speed allowed
    }

    return out;
}
