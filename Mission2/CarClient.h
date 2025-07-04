#pragma once
#include "Car.h"
#include <string>

class CarClient {
public:
    int step;
    Car car;
    CarClient();
    virtual ~CarClient() = default;
    void printStepUI();
    bool isInputValid(int answer);
    void processAnswer(int answer);
    // 입력 처리 함수(테스트용)
    void setStep(int s) { step = s; }
    int getStep() { return step; }
protected:
    virtual void print(const char* msg);
};
