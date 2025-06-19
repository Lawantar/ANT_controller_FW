#include "sensors.h"
#include "mbdata.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

sensors_ctrl_t sensors_data;

uint8_t i2c_write_reg(uint8_t sensor, uint8_t addr, uint8_t val) {
   uint8_t buff[2];

   buff[0] = addr;
   buff[1] = val;

   if (HAL_I2C_Master_Transmit(&hi2c2, sensor << 1U, buff, 2, I2C_TIMEOUT) != HAL_OK) {
      return 1;
   }
   return 0;
}

uint8_t i2c_read_reg(uint8_t sensor, uint8_t addr, uint8_t* reg) {
   if (HAL_I2C_Master_Transmit(&hi2c2, sensor << 1U, &addr, 1, I2C_TIMEOUT) != HAL_OK) {
      return 1;
   }
   if (HAL_I2C_Master_Receive(&hi2c2, sensor << 1U, reg, 1, I2C_TIMEOUT) != HAL_OK) {
       return 1;
   }
   return 0;
}

uint8_t lis3mdl_init(void) {
	uint8_t ret = 0;
	ret = i2c_write_reg(LIS3MDL_ADDR, LIS3MDL_CTRL1, 0xF4);
	if(ret != 0) {
		return ret;
	}
	ret = i2c_write_reg(LIS3MDL_ADDR, LIS3MDL_CTRL2, 0x00);
	if(ret != 0) {
		return ret;
	}
	ret = i2c_write_reg(LIS3MDL_ADDR, LIS3MDL_CTRL3, 0x00);
	if(ret != 0) {
		return ret;
	}
	ret = i2c_write_reg(LIS3MDL_ADDR, LIS3MDL_CTRL4, 0x0C);
	return ret;
}

uint8_t lis3mdl_read_mag(void) {
	uint8_t regAddress = LIS3MDL_MAG_REG;
	uint8_t buff[6];
	int16_t val[3];

	if (HAL_I2C_Master_Transmit(&hi2c2, (LIS3MDL_ADDR << 1), &regAddress, 1,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}
	if (HAL_I2C_Master_Receive(&hi2c2, (LIS3MDL_ADDR << 1), buff, 6,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}

	val[0] = (int16_t)buff[1];
	val[0] = (val[0] * 256) + (int16_t)buff[0];
	val[1] = (int16_t)buff[3];
	val[1] = (val[1] * 256) + (int16_t)buff[2];
	val[2] = (int16_t)buff[5];
	val[2] = (val[2] * 256) + (int16_t)buff[4];

	sensors_data.mag_data_raw[0] = val[0];
	sensors_data.mag_data_raw[1] = val[1];
	sensors_data.mag_data_raw[2] = val[2];

	return 0;
}

float lis3mdl_read_temp(void) {
	uint8_t regAddress = LIS3MDL_TEMP_REG;
	uint8_t buff[2];
	int16_t val;

	if (HAL_I2C_Master_Transmit(&hi2c2, (LIS3MDL_ADDR << 1), &regAddress, 1,
			I2C_TIMEOUT) != HAL_OK) {
		return 999;
	}
	if (HAL_I2C_Master_Receive(&hi2c2, (LIS3MDL_ADDR << 1), buff, 2,
			I2C_TIMEOUT) != HAL_OK) {
		return 999;
	}

	val = (int16_t)buff[1];
	val = (val * 256) + (int16_t)buff[0];

	return lsm6dsox_from_lsb_to_celsius(val);
}

uint8_t lsm6dsox_init(void) {
	uint8_t ret = 0;
	ret = i2c_write_reg(LSM6DSOX_ADDR, LSM6DSOX_CTRL1_XL, 0x42);
	if(ret != 0) {
		return ret;
	}
	ret = i2c_write_reg(LSM6DSOX_ADDR, LSM6DSOX_CTRL2_G, 0x40);
	return ret;
}

float lsm6dsox_read_temp(void) {
	uint8_t regAddress = LSM6DSOX_TEMP_REG;
	uint8_t buff[2];
	int16_t val;

	if (HAL_I2C_Master_Transmit(&hi2c2, (LSM6DSOX_ADDR << 1), &regAddress, 1,
			I2C_TIMEOUT) != HAL_OK) {
		return 999;
	}
	if (HAL_I2C_Master_Receive(&hi2c2, (LSM6DSOX_ADDR << 1), buff, 2,
			I2C_TIMEOUT) != HAL_OK) {
		return 999;
	}

	val = (int16_t)buff[1];
	val = (val * 256) + (int16_t)buff[0];

	return lsm6dsox_from_lsb_to_celsius(val);
}

uint8_t lsm6dsox_read_acc(void) {
	uint8_t regAddress = LSM6DSOX_ACC_REG;
	uint8_t buff[6];
	int16_t val[3];

	if (HAL_I2C_Master_Transmit(&hi2c2, (LSM6DSOX_ADDR << 1), &regAddress, 1,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}
	if (HAL_I2C_Master_Receive(&hi2c2, (LSM6DSOX_ADDR << 1), buff, 6,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}

	val[0] = (int16_t) buff[1];
	val[0] = (val[0] * 256) + (int16_t) buff[0];
	val[1] = (int16_t) buff[3];
	val[1] = (val[1] * 256) + (int16_t) buff[2];
	val[2] = (int16_t) buff[5];
	val[2] = (val[2] * 256) + (int16_t) buff[4];

	sensors_data.acc_data_raw[0] = val[0];
	sensors_data.acc_data_raw[1] = val[1];
	sensors_data.acc_data_raw[2] = val[2];

	return 0;
}

uint8_t lsm6dsox_read_gyro(void) {
	uint8_t regAddress = LSM6DSOX_GYRO_REG;
	uint8_t buff[6];
	int16_t val[3];

	if (HAL_I2C_Master_Transmit(&hi2c2, (LSM6DSOX_ADDR << 1), &regAddress, 1,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}
	if (HAL_I2C_Master_Receive(&hi2c2, (LSM6DSOX_ADDR << 1), buff, 6,
			I2C_TIMEOUT) != HAL_OK) {
		return 1;
	}

	val[0] = (int16_t) buff[1];
	val[0] = (val[0] * 256) + (int16_t) buff[0];
	val[1] = (int16_t) buff[3];
	val[1] = (val[1] * 256) + (int16_t) buff[2];
	val[2] = (int16_t) buff[5];
	val[2] = (val[2] * 256) + (int16_t) buff[4];

	sensors_data.gyro_data_raw[0] = val[0];
	sensors_data.gyro_data_raw[1] = val[1];
	sensors_data.gyro_data_raw[2] = val[2];

	return 0;
}

float lis3mdl_from_fs4_to_gauss(int16_t lsb)
{
  return ((float)lsb / 6842.0f);
}

float lis3mdl_from_fs8_to_gauss(int16_t lsb)
{
  return ((float)lsb / 3421.0f);
}

float lis3mdl_from_fs12_to_gauss(int16_t lsb)
{
  return ((float)lsb / 2281.0f);
}

float lis3mdl_from_fs16_to_gauss(int16_t lsb)
{
  return ((float)lsb / 1711.0f);
}

float lis3mdl_from_lsb_to_celsius(int16_t lsb)
{
  return ((float)lsb / 8.0f) + (25.0f);
}

float lsm6dsox_from_fs2_to_mg(int16_t lsb) {
	return ((float) lsb) * 0.061f;
}

float lsm6dsox_from_fs4_to_mg(int16_t lsb) {
	return ((float) lsb) * 0.122f;
}

float lsm6dsox_from_fs8_to_mg(int16_t lsb) {
	return ((float) lsb) * 0.244f;
}

float lsm6dsox_from_fs16_to_mg(int16_t lsb) {
	return ((float) lsb) * 0.488f;
}

float lsm6dsox_from_fs125_to_mdps(int16_t lsb) {
	return ((float) lsb) * 4.375f;
}

float lsm6dsox_from_fs250_to_mdps(int16_t lsb) {
	return ((float) lsb) * 8.750f;
}

float lsm6dsox_from_fs500_to_mdps(int16_t lsb) {
	return ((float) lsb) * 17.50f;
}

float lsm6dsox_from_fs1000_to_mdps(int16_t lsb) {
	return ((float) lsb) * 35.0f;
}

float lsm6dsox_from_fs2000_to_mdps(int16_t lsb) {
	return ((float) lsb) * 70.0f;
}

float lsm6dsox_from_lsb_to_celsius(int16_t lsb) {
	return (((float) lsb / 256.0f) + 25.0f);
}
