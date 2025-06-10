#include "sensors.h"
#include "mbdata.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t i2c_write_reg(uint8_t sensor, uint8_t addr, uint8_t val) {
   uint8_t buff[2];

   buff[0] = addr;
   buff[1] = val;

   if (HAL_I2C_Master_Transmit(&hi2c2, sensor, buff, 2, I2C_TIMEOUT) != HAL_OK) {
      return 1;
   }
   return 0;
}

uint8_t LSM6DSOXInit() {
	i2c_write_reg(LSM6DSOX_ADDR, FUNC_CFG_ACCESS, 0x40);
	i2c_write_reg(LSM6DSOX_ADDR, CTRL1_XL, 0x42);
	i2c_write_reg(LSM6DSOX_ADDR, CTRL2_G, 0x40);
}

float lsm6dsox_read_temp(module_ctrl_t *data) {
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

uint8_t lsm6dsox_read_acc(module_ctrl_t *data) {
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

	data->acc_raw[0] = lsm6dsox_from_fs2_to_mg(val[0]);
	data->acc_raw[1] = lsm6dsox_from_fs2_to_mg(val[1]);
	data->acc_raw[2] = lsm6dsox_from_fs2_to_mg(val[2]);

	return 0;
}

uint8_t lsm6dsox_read_gyro(module_ctrl_t *data) {
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

	data->gyro_raw[0] = lsm6dsox_from_fs250_to_mdps(val[0]);
	data->gyro_raw[1] = lsm6dsox_from_fs250_to_mdps(val[1]);
	data->gyro_raw[2] = lsm6dsox_from_fs250_to_mdps(val[2]);

	return 0;
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
