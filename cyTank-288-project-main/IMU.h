// IMU.h
#ifndef IMU_H_
#define IMU_H_

#include <stdint.h>

/**
 * Initialize I2C1 and the BNO055 IMU in NDOF fusion mode.
 * Must be called once at startup.
 */
void IMU_init(void);

/**
 * Block until the IMU is fully calibrated (system, gyro, accel, mag).
 * Shows calibration status on the LCD.
 * Move the robot around slowly while this runs.
 */
void IMU_calibrate(void);

/**
 * Read the current heading (yaw) in degrees from 0.0 to <360.0.
 */
float IMU_get_heading_deg(void);

#endif /* IMU_H_ */
