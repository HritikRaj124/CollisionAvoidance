#include "fsm.h"

fsm_output_t fsm_update(
    uint8_t current_state,
    uint8_t velocity,
    uint8_t distance)
{
    fsm_output_t out;


    if (velocity == 0 && distance <= 3)
    {
        out.state = STATE_RELEASED;
        out.target_velocity = 0;
        return out;
    }


    if (distance == 0)
    {
        out.state = STATE_FULL_BRAKE;
        out.target_velocity = 0;
        return out;
    }


    if (distance <= 5)
    {
        out.state = STATE_FULL_BRAKE;
        out.target_velocity = 0;
    }

    else if (distance <= 15)
    {
        out.state = STATE_BRAKING;
        out.target_velocity = 0;
    }

    else if (distance <= 28)
    {
        out.state = STATE_BRAKING;
        out.target_velocity =
            (uint8_t)(distance - 14);
    }

    else
    {
        out.state = STATE_IDLE;
        out.target_velocity = 14;
    }

    return out;
}
