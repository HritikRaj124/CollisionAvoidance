// braking_profile.h
// Auto-generated from MATLAB Scenario Designer
// Scenario: Emergency braking at 50 km/h
// Points: 50

#ifndef BRAKING_PROFILE_H
#define BRAKING_PROFILE_H

#include <stdint.h>

#define PROFILE_LENGTH 50

// Velocity profile (0-100, where 100 = 13.89 m/s = 50 km/h)
const uint8_t velocity_profile[PROFILE_LENGTH] = {
    100, 98, 96, 94, 92, 90, 88, 86, 84, 82, 
    79, 77, 75, 73, 71, 69, 67, 65, 63, 61, 
    59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 
    39, 37, 35, 33, 31, 29, 26, 25, 22, 20, 
    18, 16, 14, 12, 10, 8, 6, 4, 2, 0
};

// Distance profile (0-100, where 100 = 30m from obstacle)
const uint8_t distance_profile[PROFILE_LENGTH] = {
    96, 87, 78, 69, 61, 52, 44, 36, 28, 21, 
    13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#endif // BRAKING_PROFILE_H
