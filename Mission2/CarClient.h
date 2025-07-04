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
    // �Է� ó�� �Լ�(�׽�Ʈ��)
    void setStep(int s) { step = s; }
    int getStep() { return step; }
protected:
    virtual void print(const char* msg);
};
