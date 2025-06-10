#ifndef __MBDATA_H
#define __MBDATA_H

#include "stdint.h"

#define REG_INPUT_START 1
#define REG_INPUT_NREGS 46

#pragma pack(push, 1)

typedef struct {
  uint16_t mode;				// Текущий режим работы							+0
  float acc_cal_coeffs[3];		// Калибровочные коэффициенты для акселерометра	+1..6
  float gyro_cal_coeffs[3];		// Калибровочные коэффициенты для гироскопа		+7..12
  float mag_cal_coeffs[3];		// Калибровочные коэффициенты для магнитометра	+13..18
  float acc_raw[3];				// Сырые показания акселерометра				+19..24
  float gyro_raw[3];			// Сырые показания гироскопа					+25..30
  float mag_raw[3];				// Сырые показания магнитометра					+31..36
  float elev_angle;				// Текущий рассчитанный угол элевации			+37,38
  float yaw_angle;				// Текущий рассчитанный азимут					+39,40
  float elev_angle_d;			// Смещение элевации от начального положения	+41,42
  float yaw_angle_d;			// Смещение азимута от начального положения		+43,44
  uint16_t status;				// Статус работы модуля							+45
} module_ctrl_t;

#pragma pack(pop)

void mbDataInit();

#endif /* __MBDATA_H */
