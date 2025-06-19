#include "inertia_math.h"
#include "math.h"

float calc_elev_angle(module_ctrl_t *data) {
	return atanf(data->acc_raw[0] / (sqrtf(data->acc_raw[1]*data->acc_raw[1] + data->acc_raw[2]*data->acc_raw[2]))) * RAD_TO_DEG * -1;
}




