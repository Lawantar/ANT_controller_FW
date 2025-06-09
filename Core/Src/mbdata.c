#include "mbdata.h"

module_ctrl_t Data;

void mbDataInit(){
	Data.mode = 0xFFFF;
	Data.acc_cal_coeffs[0] = 0.0f;
	Data.acc_cal_coeffs[1] = 0.0f;
	Data.acc_cal_coeffs[2] = 0.0f;
	Data.gyro_cal_coeffs[0] = 0.0f;
	Data.gyro_cal_coeffs[1] = 0.0f;
	Data.gyro_cal_coeffs[2] = 0.0f;
	Data.mag_cal_coeffs[0] = 0.0f;
	Data.mag_cal_coeffs[1] = 0.0f;
	Data.mag_cal_coeffs[2] = 0.0f;
	Data.elev_angle_d = 0.0f;
	Data.yaw_angle_d = 0.0f;
	Data.status = 0x0000;
}





