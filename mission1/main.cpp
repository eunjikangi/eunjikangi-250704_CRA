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

// Constants
#define MAX_STACK_SIZE 10
#define DELAY_CONSTANT 1000

// Enums
typedef enum
{
    STEP_CAR_TYPE,
    STEP_ENGINE,
    STEP_BRAKE_SYSTEM,
    STEP_STEERING_SYSTEM,
    STEP_RUN_TEST,
} StepType;

typedef enum
{
    CAR_SEDAN = 1,
    CAR_SUV,
    CAR_TRUCK,
} CarType;

typedef enum
{
    ENGINE_GM = 1,
    ENGINE_TOYOTA,
    ENGINE_WIA,
    ENGINE_BROKEN,
} EngineType;

typedef enum
{
    BRAKE_MANDO = 1,
    BRAKE_CONTINENTAL,
    BRAKE_BOSCH,
} BrakeType;

typedef enum
{
    STEERING_BOSCH = 1,
    STEERING_MOBIS,
} SteeringType;

// Global Variables
int selectedComponents[MAX_STACK_SIZE];

// Function Declarations
void clearConsole();
void delay(int ms);
void printMenu(StepType step);
void handleInput(StepType *currentStep);
int isValidNumberInput(const char *input, int min, int max);
void processSelection(StepType *currentStep, int selection);
void printError(const char *message);
void handleCarTypeSelection(int selection);
void handleEngineSelection(int selection);
void handleBrakeSystemSelection(int selection);
void handleSteeringSystemSelection(int selection);
void runCar();
void testCar();
int isCarConfigurationValid();
void printCarDetails();

// Main Function
int main()
{
    StepType currentStep = STEP_CAR_TYPE;
    while (1)
    {
        printMenu(currentStep);
        handleInput(&currentStep);
    }
    return 0;
}

// Function Definitions
void clearConsole()
{
    printf(CLEAR_SCREEN);
}

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < DELAY_CONSTANT; i++)
    {
        for (int j = 0; j < DELAY_CONSTANT; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void printMenu(StepType step)
{
    clearConsole();
    switch (step)
    {
    case STEP_CAR_TYPE:
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
        break;
    case STEP_ENGINE:
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
        break;
    case STEP_BRAKE_SYSTEM:
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
        break;
    case STEP_STEERING_SYSTEM:
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
        break;
    case STEP_RUN_TEST:
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        break;
    }
    printf("===============================\n");
    printf("INPUT > ");
}

void handleInput(StepType *currentStep)
{
    char inputBuffer[100];
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    char *context = NULL;
    strtok_s(inputBuffer, "\r", &context);
    strtok_s(inputBuffer, "\n", &context);

    if (strcmp(inputBuffer, "exit") == 0)
    {
        printf("바이바이\n");
        exit(0);
    }

    int selection = strtol(inputBuffer, &context, 10);
    if (*context != '\0')
    {
        printError("숫자만 입력 가능");
        return;
    }

    processSelection(currentStep, selection);
}

int isValidNumberInput(const char *input, int min, int max)
{
    char *end;
    int number = strtol(input, &end, 10);
    if (*end == '\0' && number >= min && number <= max)
    {
        return number;
    }
    return -1;
}

void processSelection(StepType *currentStep, int selection)
{
    switch (*currentStep)
    {
    case STEP_CAR_TYPE:
        if (selection >= CAR_SEDAN && selection <= CAR_TRUCK)
        {
            handleCarTypeSelection(selection);
            *currentStep = STEP_ENGINE;
        }
        else
        {
            printError("차량 타입은 1 ~ 3 범위만 선택 가능");
        }
        break;

    case STEP_ENGINE:
        if (selection == 0)
        {
            *currentStep = STEP_CAR_TYPE;
        }
        else if (selection >= ENGINE_GM && selection <= ENGINE_BROKEN)
        {
            handleEngineSelection(selection);
            *currentStep = STEP_BRAKE_SYSTEM;
        }
        else
        {
            printError("엔진은 1 ~ 4 범위만 선택 가능");
        }
        break;

    case STEP_BRAKE_SYSTEM:
        if (selection == 0)
        {
            *currentStep = STEP_ENGINE;
        }
        else if (selection >= BRAKE_MANDO && selection <= BRAKE_BOSCH)
        {
            handleBrakeSystemSelection(selection);
            *currentStep = STEP_STEERING_SYSTEM;
        }
        else
        {
            printError("제동장치는 1 ~ 3 범위만 선택 가능");
        }
        break;

    case STEP_STEERING_SYSTEM:
        if (selection == 0)
        {
            *currentStep = STEP_BRAKE_SYSTEM;
        }
        else if (selection >= STEERING_BOSCH && selection <= STEERING_MOBIS)
        {
            handleSteeringSystemSelection(selection);
            *currentStep = STEP_RUN_TEST;
        }
        else
        {
            printError("조향장치는 1 ~ 2 범위만 선택 가능");
        }
        break;

    case STEP_RUN_TEST:
        if (selection == 0)
        {
            *currentStep = STEP_CAR_TYPE;
        }
        else if (selection == 1)
        {
            runCar();
        }
        else if (selection == 2)
        {
            testCar();
        }
        else
        {
            printError("Run 또는 Test 중 하나를 선택 필요");
        }
        break;
    }
}

void printError(const char *message)
{
    printf("ERROR :: %s\n", message);
    delay(800);
}

void handleCarTypeSelection(int selection)
{
    selectedComponents[STEP_CAR_TYPE] = selection;
    switch (selection)
    {
    case CAR_SEDAN:
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
        break;
    case CAR_SUV:
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
        break;
    case CAR_TRUCK:
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
        break;
    }
    delay(800);
}

void handleEngineSelection(int selection)
{
    selectedComponents[STEP_ENGINE] = selection;
    switch (selection)
    {
    case ENGINE_GM:
        printf("GM 엔진을 선택하셨습니다.\n");
        break;
    case ENGINE_TOYOTA:
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
        break;
    case ENGINE_WIA:
        printf("WIA 엔진을 선택하셨습니다.\n");
        break;
    case ENGINE_BROKEN:
        printf("고장난 엔진을 선택하셨습니다.\n");
        break;
    }
    delay(800);
}

void handleBrakeSystemSelection(int selection)
{
    selectedComponents[STEP_BRAKE_SYSTEM] = selection;
    switch (selection)
    {
    case BRAKE_MANDO:
        printf("MANDO 제동장치를 선택하셨습니다.\n");
        break;
    case BRAKE_CONTINENTAL:
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
        break;
    case BRAKE_BOSCH:
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
        break;
    }
    delay(800);
}

void handleSteeringSystemSelection(int selection)
{
    selectedComponents[STEP_STEERING_SYSTEM] = selection;
    switch (selection)
    {
    case STEERING_BOSCH:
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
        break;
    case STEERING_MOBIS:
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
        break;
    }
    delay(800);
}

int isCarConfigurationValid()
{
    if (selectedComponents[STEP_CAR_TYPE] == CAR_SEDAN && selectedComponents[STEP_BRAKE_SYSTEM] == BRAKE_CONTINENTAL)
        return 0;
    if (selectedComponents[STEP_CAR_TYPE] == CAR_SUV && selectedComponents[STEP_ENGINE] == ENGINE_TOYOTA)
        return 0;
    if (selectedComponents[STEP_CAR_TYPE] == CAR_TRUCK && selectedComponents[STEP_ENGINE] == ENGINE_WIA)
        return 0;
    if (selectedComponents[STEP_CAR_TYPE] == CAR_TRUCK && selectedComponents[STEP_BRAKE_SYSTEM] == BRAKE_MANDO)
        return 0;
    if (selectedComponents[STEP_BRAKE_SYSTEM] == BRAKE_BOSCH && selectedComponents[STEP_STEERING_SYSTEM] != STEERING_BOSCH)
        return 0;
    return 1;
}

void runCar()
{
    if (!isCarConfigurationValid())
    {
        printf("자동차가 동작되지 않습니다\n");
        delay(2000);
        return;
    }

    if (selectedComponents[STEP_ENGINE] == ENGINE_BROKEN)
    {
        printf("엔진이 고장나있습니다.\n자동차가 움직이지 않습니다.\n");
        delay(2000);
        return;
    }

    printCarDetails();
    printf("자동차가 동작됩니다.\n");
    delay(2000);
}

void testCar()
{
    if (!isCarConfigurationValid())
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        delay(2000);
        return;
    }

    printf("자동차 부품 조합 테스트 결과 : PASS\n");
    delay(2000);
}

void printCarDetails()
{
    printf("Car Details:\n");
    switch (selectedComponents[STEP_CAR_TYPE])
    {
    case CAR_SEDAN:
        printf("Car Type : Sedan\n");
        break;
    case CAR_SUV:
        printf("Car Type : SUV\n");
        break;
    case CAR_TRUCK:
        printf("Car Type : Truck\n");
        break;
    }

    switch (selectedComponents[STEP_ENGINE])
    {
    case ENGINE_GM:
        printf("Engine : GM\n");
        break;
    case ENGINE_TOYOTA:
        printf("Engine : TOYOTA\n");
        break;
    case ENGINE_WIA:
        printf("Engine : WIA\n");
        break;
    }

    switch (selectedComponents[STEP_BRAKE_SYSTEM])
    {
    case BRAKE_MANDO:
        printf("Brake System : Mando\n");
        break;
    case BRAKE_CONTINENTAL:
        printf("Brake System : Continental\n");
        break;
    case BRAKE_BOSCH:
        printf("Brake System : Bosch\n");
        break;
    }

    switch (selectedComponents[STEP_STEERING_SYSTEM])
    {
    case STEERING_BOSCH:
        printf("Steering System : Bosch\n");
        break;
    case STEERING_MOBIS:
        printf("Steering System : Mobis\n");
        break;
    }
}

#endif