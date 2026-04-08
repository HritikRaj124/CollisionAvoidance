#include "controller.h"

#define KP  2.0f
#define KI  0.1f

#define DUTY_MIN  0.0f
#define DUTY_MAX  100.0f

uint8_t controller_compute_duty(uint8_t target_velocity,
                                uint8_t current_velocity)
{
    static float integral = 0.0f;
    float duty_f = 0.0f;

    float error = (float)target_velocity - (float)current_velocity;
    integral += error;

    duty_f = KP * error + KI * integral;

    // Saturation + anti-windup
    if (duty_f > DUTY_MAX)
    {
        duty_f = DUTY_MAX;
        integral -= error;
    }
    else if (duty_f < DUTY_MIN)
    {
        duty_f = DUTY_MIN;
        integral -= error;
    }

    return (uint8_t)duty_f;
}
