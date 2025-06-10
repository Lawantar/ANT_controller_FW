#ifndef __SENSORS_H_
#define __SENSORS_H_

#include "main.h"
#include "mbdata.h"

#define I2C_TIMEOUT 100U

uint8_t i2c_write_reg(uint8_t sensor, uint8_t addr, uint8_t val);

/*** LSM6DSOX REGISTERS ***/
#define LSM6DSOX_ADDR 0x6A		// LSM6DSOX I2C address
#define FUNC_CFG_ACCESS 0x01	// Embedded functions register
#define CTRL1_XL 0x10			// ACC settings
#define CTRL2_G 0x11			// GYRO settings
#define LSM6DSOX_TEMP_REG 0x20	// Temp register
#define LSM6DSOX_GYRO_REG 0x22	// GYRO register
#define LSM6DSOX_ACC_REG 0x28	// ACC register

/*** LIS3MDL REGISTERS ***/
#define LIS3MDL_ADDR 0x1C		// LIS3MDL I2C address

/*** SENSORS INIT FUNCTIONS ***/
uint8_t LSM6DSOXInit();
uint8_t LIS3MDLInit();

/*** DATA READ FUNCTIONS ***/
float lsm6dsox_read_temp(module_ctrl_t *data);
uint8_t lsm6dsox_read_acc(module_ctrl_t* data);
uint8_t lsm6dsox_read_gyro(module_ctrl_t* data);

/*** DATA CONVERSION FUNCTIONS ***/
float lsm6dsox_from_fs2_to_mg(int16_t lsb);
float lsm6dsox_from_fs4_to_mg(int16_t lsb);
float lsm6dsox_from_fs8_to_mg(int16_t lsb);
float lsm6dsox_from_fs16_to_mg(int16_t lsb);
float lsm6dsox_from_fs125_to_mdps(int16_t lsb);
float lsm6dsox_from_fs250_to_mdps(int16_t lsb);
float lsm6dsox_from_fs500_to_mdps(int16_t lsb);
float lsm6dsox_from_fs1000_to_mdps(int16_t lsb);
float lsm6dsox_from_fs2000_to_mdps(int16_t lsb);
float lsm6dsox_from_lsb_to_celsius(int16_t lsb);

#endif /* __SENSORS_H_ */
