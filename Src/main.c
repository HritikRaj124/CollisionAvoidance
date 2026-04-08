#include "uart.h"
#include "pwm.h"
#include "fsm.h"
#include "controller.h"
#include "braking_profile.h"
#include <stdint.h>

#define SCB_CPACR (*(volatile uint32_t *)0xE000ED88)

int main(void)
{
    SCB_CPACR |= (0xF << 20);   // Enable FPU

    uart_init();
    pwm_init();

    uint8_t state = STATE_IDLE;

    for (int i = 0; i < PROFILE_LENGTH; i++)
    {
        uint8_t velocity = velocity_profile[i];
        uint8_t distance = distance_profile[i];

        fsm_output_t fsm = fsm_update(state, velocity, distance);
        state = fsm.state;

        uint8_t duty =
            controller_compute_duty(fsm.target_velocity, velocity);

        pwm_set_duty(duty);

        uart_send_string("VEL=");
        uart_send_int(velocity);
        uart_send_string(" DIST=");
        uart_send_int(distance);
        uart_send_string(" TARGET=");
        uart_send_int(fsm.target_velocity);
        uart_send_string(" PWM=");
        uart_send_int(duty);
        uart_send_string("\r\n");

        for (volatile int d = 0; d < 3000000; d++);
    }

    while (1);
}
