#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

uint8_t controller_compute_duty(uint8_t target_velocity,
                                uint8_t current_velocity);

#endif // CONTROLLER_H
