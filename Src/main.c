#include "uart.h"
#include "pwm.h"
#include "fsm.h"
#include "controller.h"
#include "braking_profile.h"
#include <stdint.h>
#include <stdio.h>

#define SCB_CPACR (*(volatile uint32_t *)0xE000ED88)

int main(void)
{

    SCB_CPACR |= (0xF << 20);

    uart_init();
    pwm_init();

    uint8_t state = STATE_IDLE;


    float dist_history[3] =
        {29.0f, 29.0f, 29.0f};

    for (int i = 0; i < PROFILE_LENGTH; i++)
    {

        float distance = radar_distance[i];
        float velocity = radar_velocity[i];


        if (velocity < 0.0f)
            velocity = -velocity;

        if (distance < 0.0f  ||
            distance > 35.0f ||
            velocity > 30.0f)
        {
            uart_send_string(
                "SENSOR_FAULT\r\n");
            continue;
        }

        dist_history[i % 3] = distance;
        float smooth_dist =
            (dist_history[0] +
             dist_history[1] +
             dist_history[2]) / 3.0f;

        uint8_t dist_int =
            (uint8_t)smooth_dist;


        uint8_t vel_scaled =
            (uint8_t)(velocity * 10.0f);


        fsm_output_t fsm = fsm_update(
            state,
            vel_scaled,
            dist_int);
        state = fsm.state;


        uint8_t duty =
            controller_compute_duty(
                fsm.target_velocity,
                vel_scaled);


        pwm_set_duty(duty);


        uart_send_string("DIST=");
        uart_send_int(dist_int);
        uart_send_string("m VEL=");
        uart_send_int(vel_scaled);
        uart_send_string("x0.1m/s ");
        uart_send_string("TARGET=");
        uart_send_int(fsm.target_velocity);
        uart_send_string(" PWM=");
        uart_send_int(duty);
        uart_send_string(" STATE=");
        uart_send_int(state);
        uart_send_string("\r\n");


        for (volatile int d = 0; d < 3000000; d++);
    }

    while (1);
}
