#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void printStepUI(int step) {
    printf(CLEAR_SCREEN);

    switch (step) {
        case CarType_Q:
            printf("        ______________\n");
            printf("       /|            | \n");
            printf("  ____/_|_____________|____\n");
            printf(" |                      O  |\n");
            printf(" '-(@)----------------(@)--'\n");
            printf("===============================\n");
            printf("어떤 차량 타입을 선택할까요?\n");
            printf("1. Sedan\n2. SUV\n3. Truck\n");
            break;
        case Engine_Q:
            printf("어떤 엔진을 탑재할까요?\n0. 뒤로가기\n1. GM\n2. TOYOTA\n3. WIA\n4. 고장난 엔진\n");
            break;
        case brakeSystem_Q:
            printf("어떤 제동장치를 선택할까요?\n0. 뒤로가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n");
            break;
        case SteeringSystem_Q:
            printf("어떤 조향장치를 선택할까요?\n0. 뒤로가기\n1. BOSCH\n2. MOBIS\n");
            break;
        case Run_Test:
            printf("멋진 차량이 완성되었습니다.\n어떤 동작을 할까요?\n0. 처음 화면으로 돌아가기\n1. RUN\n2. Test\n");
            break;
    }

    printf("===============================\nINPUT > ");
}

bool isInputValid(int step, int answer) {
    if (step == CarType_Q && !(answer >= 1 && answer <= 3)) return false;
    if (step == Engine_Q && !(answer >= 0 && answer <= 4)) return false;
    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3)) return false;
    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) return false;
    if (step == Run_Test && !(answer >= 0 && answer <= 2)) return false;
    return true;
}

void processAnswer(int& step, int answer) {
    if (answer == 0 && step == Run_Test) {
        step = CarType_Q;
        return;
    }

    if (answer == 0 && step >= 1) {
        step -= 1;
        return;
    }

    switch (step) {
        case CarType_Q:
            selectCarType(answer);
            step = Engine_Q;
            break;
        case Engine_Q:
            selectEngine(answer);
            step = brakeSystem_Q;
            break;
        case brakeSystem_Q:
            selectbrakeSystem(answer);
            step = SteeringSystem_Q;
            break;
        case SteeringSystem_Q:
            selectSteeringSystem(answer);
            step = Run_Test;
            break;
        case Run_Test:
            if (answer == 1) {
                runProducedCar();
                delay(2000);
            }
            else if (answer == 2) {
                printf("Test...\n");
                delay(1500);
                testProducedCar();
                delay(2000);
            }
            break;
    }

    delay(800);
}

int main()
{
    char buf[100];
    int step = CarType_Q;

    while (1)
    {
        printStepUI(step);

        fgets(buf, sizeof(buf), stdin);
        strtok(buf, "\r\n");

        if (!strcmp(buf, "exit")) {
            printf("바이바이\n");
            break;
        }

        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10);

        if (*checkNumber != '\0') {
            printf("ERROR :: 숫자만 입력 가능\n");
            delay(800);
            continue;
        }

        if (!isInputValid(step, answer)) {
            printf("ERROR :: 유효한 입력이 아닙니다\n");
            delay(800);
            continue;
        }

        processAnswer(step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
        return false;
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
        return false;
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
        return false;
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
        return false;
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
        return false;
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");

            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");

            if (stack[brakeSystem_Q] == 1)
                printf("Brake System : Mando\n");
            if (stack[brakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");

            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}

#endif