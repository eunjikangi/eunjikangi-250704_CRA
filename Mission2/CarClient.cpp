#include "CarClient.h"
#include <stdio.h>
#define CLEAR_SCREEN "\033[H\033[2J"

CarClient::CarClient() : step(CarType_Q), car() {}

void CarClient::print(const char* msg) {
    printf("%s", msg);
}

void CarClient::printStepUI() {
    print(CLEAR_SCREEN);
    switch (step)
    {
    case CarType_Q:
        print("        ______________\n");
        print("       /|            | \n");
        print("  ____/_|_____________|____\n");
        print(" |                      O  |\n");
        print(" '-(@)----------------(@)--'\n");
        print("===============================\n");
        print("� ���� Ÿ���� �����ұ��?\n");
        print("1. Sedan\n2. SUV\n3. Truck\n");
        break;
    case Engine_Q:
        print("� ������ ž���ұ��?\n0. �ڷΰ���\n1. GM\n2. TOYOTA\n3. WIA\n4. ���峭 ����\n");
        break;
    case brakeSystem_Q:
        print("� ������ġ�� �����ұ��?\n0. �ڷΰ���\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n");
        break;
    case SteeringSystem_Q:
        print("� ������ġ�� �����ұ��?\n0. �ڷΰ���\n1. BOSCH\n2. MOBIS\n");
        break;
    case Run_Test:
        print("���� ������ �ϼ��Ǿ����ϴ�.\n� ������ �ұ��?\n0. ó�� ȭ������ ���ư���\n1. RUN\n2. Test\n");
        break;
    }
    print("===============================\nINPUT > ");
}

bool CarClient::isInputValid(int answer) {
    char buf[128];
    if (step == CarType_Q && !(answer >= MIN_CAR_TYPE && answer <= MAX_CAR_TYPE)) {
        snprintf(buf, sizeof(buf), "ERROR :: ���� Ÿ���� %d ~ %d ������ ���� ����\n", MIN_CAR_TYPE, MAX_CAR_TYPE);
        print(buf);
        return false;
    }
    if (step == Engine_Q && !(answer >= MIN_ENGINE && answer <= MAX_ENGINE)) {
        snprintf(buf, sizeof(buf), "ERROR :: ������ %d ~ %d ������ ���� ����\n", MIN_ENGINE, MAX_ENGINE);
        print(buf);
        return false;
    }
    if (step == brakeSystem_Q && !(answer >= MIN_BRAKE && answer <= MAX_BRAKE)) {
        snprintf(buf, sizeof(buf), "ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", MIN_BRAKE, MAX_BRAKE);
        print(buf);
        return false;
    }
    if (step == SteeringSystem_Q && !(answer >= MIN_STEERING && answer <= MAX_STEERING)) {
        snprintf(buf, sizeof(buf), "ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", MIN_STEERING, MAX_STEERING);
        print(buf);
        return false;
    }
    if (step == Run_Test && !(answer >= MIN_RUN_TEST && answer <= MAX_RUN_TEST)) {
        print("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        return false;
    }
    return true;
}

void CarClient::processAnswer(int answer) {
    if (answer == 0 && step == Run_Test) {
        step = CarType_Q;
        return;
    }
    if (answer == 0 && step >= Engine_Q) {
        step -= 1;
        return;
    }
    switch (step) {
    case CarType_Q:
        car.selectCarType(answer);
        step = Engine_Q;
        break;
    case Engine_Q:
        car.selectEngine(answer);
        step = brakeSystem_Q;
        break;
    case brakeSystem_Q:
        car.selectBrake(answer);
        step = SteeringSystem_Q;
        break;
    case SteeringSystem_Q:
        car.selectSteering(answer);
        step = Run_Test;
        break;
    case Run_Test:
        if (answer == RUN) {
            car.run();
        }
        else if (answer == TEST) {
            print("Test...\n");
            car.test();
        }
        break;
    }
}
