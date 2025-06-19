#ifndef __SENSORS_H_
#define __SENSORS_H_

#include "main.h"
#include "mbdata.h"

#define I2C_TIMEOUT 100U

typedef struct {
	float acc_data_raw[3];
	float gyro_data_raw[3];
	float mag_data_raw[3];
} sensors_ctrl_t;

uint8_t i2c_write_reg(uint8_t sensor, uint8_t addr, uint8_t val);
uint8_t i2c_read_reg(uint8_t sensor, uint8_t addr, uint8_t* reg);

/*** LSM6DSOX REGISTERS ***/
#define LSM6DSOX_ADDR 0x6A				// LSM6DSOX I2C address
#define LSM6DSOX_FUNC_CFG_ACCESS 0x01	// Embedded functions register
#define LSM6DSOX_CTRL1_XL 0x10			// ACC settings
#define LSM6DSOX_CTRL2_G 0x11			// GYRO settings
#define LSM6DSOX_TEMP_REG 0x20			// Temp register
#define LSM6DSOX_GYRO_REG 0x22			// GYRO register
#define LSM6DSOX_ACC_REG 0x28			// ACC register

/*** LIS3MDL REGISTERS ***/
#define LIS3MDL_ADDR 0x1C				// LIS3MDL I2C address
#define LIS3MDL_CTRL1 0x20				// Data rate and mode
#define LIS3MDL_CTRL2 0x21				// Scale config
#define LIS3MDL_CTRL3 0x22				// Operating mode
#define LIS3MDL_CTRL4 0x23				// Z axis op mode
#define LIS3MDL_MAG_REG 0x28			// Mag register
#define LIS3MDL_TEMP_REG 0x2E			// Temp register

/*** SENSORS INIT FUNCTIONS ***/
uint8_t lsm6dsox_init(void);
uint8_t lis3mdl_init(void);

/*** DATA READ FUNCTIONS ***/
uint8_t lis3mdl_read_mag(void);
float lis3mdl_read_temp(void);
float lsm6dsox_read_temp(void);
uint8_t lsm6dsox_read_acc(void);
uint8_t lsm6dsox_read_gyro(void);

/*** DATA CONVERSION FUNCTIONS ***/
float lis3mdl_from_fs4_to_gauss(int16_t lsb);
float lis3mdl_from_fs8_to_gauss(int16_t lsb);
float lis3mdl_from_fs12_to_gauss(int16_t lsb);
float lis3mdl_from_fs16_to_gauss(int16_t lsb);
float lis3mdl_from_lsb_to_celsius(int16_t lsb);
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
