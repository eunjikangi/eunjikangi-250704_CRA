#pragma once
#include <stdio.h>

// enum 정의는 그대로 사용
// (main.cpp에서 복사)
enum QuestionType {
	CarType_Q,
	Engine_Q,
	brakeSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};
enum CarType {
	SEDAN = 1,
	SUV,
	TRUCK,
	CAR_TYPE_COUNT
};
const int MIN_CAR_TYPE = SEDAN;
const int MAX_CAR_TYPE = CAR_TYPE_COUNT - 1;
enum Engine {
	GM = 1,
	TOYOTA,
	WIA,
	BROKEN_ENGINE,
	ENGINE_COUNT
};
const int MIN_ENGINE = 0;
const int MAX_ENGINE = ENGINE_COUNT - 1;
enum brakeSystem {
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B,
	BRAKE_COUNT
};
const int MIN_BRAKE = 0;
const int MAX_BRAKE = BRAKE_COUNT - 1;
enum SteeringSystem {
	BOSCH_S = 1,
	MOBIS,
	STEERING_COUNT
};
const int MIN_STEERING = 0;
const int MAX_STEERING = STEERING_COUNT - 1;
enum RunMode {
	RUN = 1,
	TEST,
	RUN_MODE_COUNT
};
const int MIN_RUN_TEST = 0;
const int MAX_RUN_TEST = RUN_MODE_COUNT - 1;

class Car {
public:
	int carType = 0;
	int engine = 0;
	int brake = 0;
	int steering = 0;

	void selectCarType(int answer);
	void selectEngine(int answer);
	void selectBrake(int answer);
	void selectSteering(int answer);
	bool isValid();
	void run();
	void test();
};
