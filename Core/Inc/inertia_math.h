#ifndef INERTIA_MATH_H_
#define INERTIA_MATH_H_

#include "stdint.h"
#include "mbdata.h"

#define RAD_TO_DEG 57.295779513082320876798154814105f

float calc_elev_angle(module_ctrl_t *data);
float calc_yaw_angle(module_ctrl_t *data);

#endif /* INERTIA_MATH_H_ */
