# colorCalibration
static void rootfunc(void * arg) {
	glcd_init();  //glcd초기화

	ev3_sensor_init(0, COL_REFLECT);  //ev3센서 COLOR모드 초기화

	// calibration sensor : port0, light sensor
	calibEV3Sensor(0, MAX_LIGHT_LEVEL, light_value);//3개단계로 calibration해 light_value에 저장
	task_sleep(3000); // 3s delay
	glcd_clear();

	switch(get_level(ev3_sensor_get(0), MAX_LIGHT_LEVEL, light_value))  //센서값 레벨나눔
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
	task_sleep(50);  //50ms주기로 측정
}