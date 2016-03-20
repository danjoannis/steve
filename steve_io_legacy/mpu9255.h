/*
 * mpu9255.h
 *
 *  Created on: Nov 24, 2015
 *      Author: Daniel
 */

#ifndef MPU9255_H_
#define MPU9255_H_

/* I2C addresses of Accelerometer/Gyro and Compass */
#define I2CACCGYROADD 0x68
#define I2CCOMPADD 0x0C

/* Accelerometer/Gyro register addresses */
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define TEMP_OUT_H 0x41
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47
#define PWR_MGMT_1 0x6B

/*Compass register addresses */
#define COMP_STATUS 0x02
#define COMP_XOUT_L 0x03
#define COMP_YOUT_L 0x05
#define COMP_ZOUT_L 0x07

/* Accelerometer range modes */
#define ACCELRANGE_2g 0
#define ACCELRANGE_4g 1
#define ACCELRANGE_8g 2
#define ACCELRANGE_16g 3

/* Gyroscope sensitivity */
#define GYRORANGE_250DPS 0
#define GYRORANGE_500DPS 1
#define GYRORANGE_1000DPS 2
#define GYRORANGE_2000DPS 3

/*Prototypes...see description of them at the begining of each definition*/
int Read_Acc_Gyro(unsigned char axis);
void Initalise_AccelGyro(unsigned char Accel_Range,unsigned char Gyro_Range);
int Read_Compass(unsigned char axis);
void Trigger_Compass(void);


#endif /* MPU9255_H_ */
