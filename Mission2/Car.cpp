#include "Car.h"
#include <stdio.h>

void Car::selectCarType(int answer) {
	carType = answer;
	if (answer == SEDAN)
		printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
	if (answer == SUV)
		printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
	if (answer == TRUCK)
		printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}
void Car::selectEngine(int answer) {
	engine = answer;
	if (answer == GM)
		printf("GM ������ �����ϼ̽��ϴ�.\n");
	if (answer == TOYOTA)
		printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
	if (answer == WIA)
		printf("WIA ������ �����ϼ̽��ϴ�.\n");
}
void Car::selectBrake(int answer) {
	brake = answer;
	if (answer == MANDO)
		printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == CONTINENTAL)
		printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == BOSCH_B)
		printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}
void Car::selectSteering(int answer) {
	steering = answer;
	if (answer == BOSCH_S)
		printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
	if (answer == MOBIS)
		printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
		printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
		return;
	}
	if (engine == BROKEN_ENGINE) {
		printf("������ ���峪�ֽ��ϴ�.\n");
		printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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
	printf("�ڵ����� ���۵˴ϴ�.\n");
}
void Car::test() {
	if (carType == SEDAN && brake == CONTINENTAL) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Sedan���� Continental������ġ ��� �Ұ�\n");
	}
	else if (carType == SUV && engine == TOYOTA) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("SUV���� TOYOTA���� ��� �Ұ�\n");
	}
	else if (carType == TRUCK && engine == WIA) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Truck���� WIA���� ��� �Ұ�\n");
	}
	else if (carType == TRUCK && brake == MANDO) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Truck���� Mando������ġ ��� �Ұ�\n");
	}
	else if (brake == BOSCH_B && steering != BOSCH_S) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
	}
	else {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
	}
}
