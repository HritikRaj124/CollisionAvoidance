#include "fsm.h"

fsm_output_t fsm_update(
    uint8_t current_state,
    uint8_t velocity,
    uint8_t distance)
{
    fsm_output_t out;

    /* Vehicle truly stopped —
     * only release if also very close
     * prevents false STATE_RELEASED
     * from noisy zero velocity */
    if (velocity == 0 && distance <= 3)
    {
        out.state = STATE_RELEASED;
        out.target_velocity = 0;
        return out;
    }

    /* Collision — distance zero */
    if (distance == 0)
    {
        out.state = STATE_FULL_BRAKE;
        out.target_velocity = 0;
        return out;
    }

    /* Emergency braking — < 5m */
    if (distance <= 5)
    {
        out.state = STATE_FULL_BRAKE;
        out.target_velocity = 0;
    }
    /* Active braking — 5m to 15m */
    else if (distance <= 15)
    {
        out.state = STATE_BRAKING;
        out.target_velocity = 0;
    }
    /* Controlled deceleration
     * 15m to 28m
     * target velocity scales
     * with distance */
    else if (distance <= 28)
    {
        out.state = STATE_BRAKING;
        out.target_velocity =
            (uint8_t)(distance - 14);
    }
    /* Safe distance — above 28m */
    else
    {
        out.state = STATE_IDLE;
        out.target_velocity = 14;
    }

    return out;
}
