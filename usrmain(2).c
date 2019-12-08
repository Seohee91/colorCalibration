/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the exe_helloworld component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

/* -------------------------------------------------------------------------
	Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_switch/itf/lib_switch.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_sensorcalib/itf/lib_sensorcalib.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);


/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_led_switch_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void rootfunc(void * arg) {
	glcd_init();

	ev3_sensor_init(0, COL_REFLECT);

	// calibration sensor : port0, light sensor
	calibEV3Sensor(0, MAX_LIGHT_LEVEL, light_value);

	task_sleep(3000); // 3s delay
	glcd_clear();

	switch(get_level(ev3_sensor_get(0), MAX_LIGHT_LEVEL, light_value))
	{
	case LIGHT_DARK:
		glcd_printf("Mode1 : %3d", ev3_sensor_get(0));
		break;

	case LIGHT_DIM:
		glcd_printf("Mode2 : %3d", ev3_sensor_get(0));
		break;

	case LIGHT_BRIGHT:
		glcd_printf("Mode3 : %3d", ev3_sensor_get(0));
		break;

	default:
		glcd_printf("UNDEFINE");
		break;
	}

	task_sleep(50);		// 50ms delay
}

