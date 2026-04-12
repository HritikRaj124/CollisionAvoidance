/*
 * braking_profile.h
 * Auto-generated from MATLAB
 * Automated Driving Toolbox
 * Radar sensor: drivingRadarDataGenerator
 * Scenario: Ego at 50km/h approaching
 *           stationary obstacle at 30m
 * Generated: 12-Apr-2026 16:05:48
 */

#ifndef BRAKING_PROFILE_H
#define BRAKING_PROFILE_H

#define PROFILE_LENGTH 21

#define INITIAL_DISTANCE_M  17.94f
#define INITIAL_VELOCITY_MS 7.74f

/* Radar range (metres) */
static const float radar_distance[PROFILE_LENGTH] = {
    17.9385f,
    26.6007f,
    25.2738f,
    10.8659f,
    22.5248f,
    21.2086f,
    19.9184f,
    18.5517f,
    17.3114f,
    13.3042f,
    6.6389f,
    13.5413f,
    12.2844f,
    11.1562f,
    9.9020f,
    8.7463f,
    7.5179f,
    6.4268f,
    5.2894f,
    4.1321f,
    2.9954f
};

/* Radar range rate (m/s) */
/* Negative = closing */
static const float radar_velocity[PROFILE_LENGTH] = {
    7.7396f,
    -0.0304f,
    -0.4377f,
    -1.2479f,
    0.7329f,
    -0.1071f,
    0.8154f,
    1.0098f,
    0.7120f,
    -2.0593f,
    -0.7942f,
    -0.5937f,
    0.3917f,
    0.4979f,
    -0.0173f,
    -0.1241f,
    -0.1087f,
    0.8088f,
    -0.5414f,
    0.6424f,
    0.0415f
};

#endif /* BRAKING_PROFILE_H */
