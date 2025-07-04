#include "Car.h"
#include <stdio.h>

void Car::selectCarType(int answer) {
	carType = answer;
	if (answer == SEDAN)
		printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
	if (answer == SUV)
		printf("차량 타입으로 SUV을 선택하셨습니다.\n");
	if (answer == TRUCK)
		printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}
void Car::selectEngine(int answer) {
	engine = answer;
	if (answer == GM)
		printf("GM 엔진을 선택하셨습니다.\n");
	if (answer == TOYOTA)
		printf("TOYOTA 엔진을 선택하셨습니다.\n");
	if (answer == WIA)
		printf("WIA 엔진을 선택하셨습니다.\n");
}
void Car::selectBrake(int answer) {
	brake = answer;
	if (answer == MANDO)
		printf("MANDO 제동장치를 선택하셨습니다.\n");
	if (answer == CONTINENTAL)
		printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
	if (answer == BOSCH_B)
		printf("BOSCH 제동장치를 선택하셨습니다.\n");
}
void Car::selectSteering(int answer) {
	steering = answer;
	if (answer == BOSCH_S)
		printf("BOSCH 조향장치를 선택하셨습니다.\n");
	if (answer == MOBIS)
		printf("MOBIS 조향장치를 선택하셨습니다.\n");
}
bool Car::isValid() {
	if (carType == SEDAN && brake == CONTINENTAL) return false;
	if (carType == SUV && engine == TOYOTA) return false;
	if (carType == TRUCK && engine == WIA) return false;
	if (carType == TRUCK && brake == MANDO) return false;
	if (brake == BOSCH_B && steering != BOSCH_S) return false;
	return true;
}
void Car::run() {
	if (!isValid()) {
		printf("자동차가 동작되지 않습니다\n");
		return;
	}
	if (engine == BROKEN_ENGINE) {
		printf("엔진이 고장나있습니다.\n");
		printf("자동차가 움직이지 않습니다.\n");
		return;
	}
	if (carType == SEDAN) printf("Car Type : Sedan\n");
	if (carType == SUV) printf("Car Type : SUV\n");
	if (carType == TRUCK) printf("Car Type : Truck\n");
	if (engine == GM) printf("Engine : GM\n");
	if (engine == TOYOTA) printf("Engine : TOYOTA\n");
	if (engine == WIA) printf("Engine : WIA\n");
	if (brake == MANDO) printf("Brake System : Mando\n");
	if (brake == CONTINENTAL) printf("Brake System : Continental\n");
	if (brake == BOSCH_B) printf("Brake System : Bosch\n");
	if (steering == BOSCH_S) printf("SteeringSystem : Bosch\n");
	if (steering == MOBIS) printf("SteeringSystem : Mobis\n");
	printf("자동차가 동작됩니다.\n");
}
void Car::test() {
	if (carType == SEDAN && brake == CONTINENTAL) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Sedan에는 Continental제동장치 사용 불가\n");
	}
	else if (carType == SUV && engine == TOYOTA) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("SUV에는 TOYOTA엔진 사용 불가\n");
	}
	else if (carType == TRUCK && engine == WIA) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Truck에는 WIA엔진 사용 불가\n");
	}
	else if (carType == TRUCK && brake == MANDO) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Truck에는 Mando제동장치 사용 불가\n");
	}
	else if (brake == BOSCH_B && steering != BOSCH_S) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
	}
	else {
		printf("자동차 부품 조합 테스트 결과 : PASS\n");
	}
}
