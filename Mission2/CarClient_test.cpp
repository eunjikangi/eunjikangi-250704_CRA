#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CarClient.h"
#include <string>
#include <vector>

using namespace testing;

class MockCarClient : public CarClient {
public:
    std::vector<std::string> prints;
    void print(const char* msg) {
        prints.emplace_back(msg);
    }
    void clearPrints() { prints.clear(); }
    std::string getAllPrints() const {
        std::string out;
        for (const auto& s : prints) out += s;
        return out;
    }
};

class CarClientFixture : public Test {
protected:
    MockCarClient client;
};

TEST_F(CarClientFixture, PrintStepUI_AllSteps) {
    client.setStep(CarType_Q);
    client.clearPrints();
    client.printStepUI();
    EXPECT_NE(client.getAllPrints().find("Sedan"), std::string::npos);

    client.setStep(Engine_Q);
    client.clearPrints();
    client.printStepUI();
    EXPECT_NE(client.getAllPrints().find("GM"), std::string::npos);

    client.setStep(brakeSystem_Q);
    client.clearPrints();
    client.printStepUI();
    EXPECT_NE(client.getAllPrints().find("MANDO"), std::string::npos);

    client.setStep(SteeringSystem_Q);
    client.clearPrints();
    client.printStepUI();
    EXPECT_NE(client.getAllPrints().find("BOSCH"), std::string::npos);

    client.setStep(Run_Test);
    client.clearPrints();
    client.printStepUI();
    EXPECT_NE(client.getAllPrints().find("RUN"), std::string::npos);
}

TEST_F(CarClientFixture, StepStartsAtCarTypeQ) {
    EXPECT_EQ(client.getStep(), CarType_Q);
}

TEST_F(CarClientFixture, RunTestStepAndAnswerZero) {
    client.setStep(Run_Test);
    client.processAnswer(0);

    EXPECT_EQ(client.getStep(), CarType_Q);
}

TEST_F(CarClientFixture, ValidInputAdvancesStep) {
    client.processAnswer(SEDAN);
    EXPECT_EQ(client.getStep(), Engine_Q);
    client.processAnswer(GM);
    EXPECT_EQ(client.getStep(), brakeSystem_Q);
    client.processAnswer(MANDO);
    EXPECT_EQ(client.getStep(), SteeringSystem_Q);
    client.processAnswer(BOSCH_S);
    EXPECT_EQ(client.getStep(), Run_Test);
}

TEST_F(CarClientFixture, ValidInputTest) {
    client.setStep(CarType_Q);

    bool valid = client.isInputValid(1);
    EXPECT_TRUE(valid);
}

TEST_F(CarClientFixture, InvalidInputDoesNotAdvanceStep) {
    int before = client.getStep();
    client.clearPrints();

    bool valid = client.isInputValid(0);
    EXPECT_FALSE(valid);
    EXPECT_EQ(client.getStep(), before);
    EXPECT_NE(client.getAllPrints().find("ERROR"), std::string::npos);
}

TEST_F(CarClientFixture, CanGoBackWithZero) {
    client.processAnswer(SEDAN);
    client.processAnswer(0);
    EXPECT_EQ(client.getStep(), CarType_Q);
}

TEST_F(CarClientFixture, RunAndTestPrints) {
    client.setStep(Run_Test);
    client.car.selectCarType(SEDAN);
    client.car.selectEngine(GM);
    client.car.selectBrake(MANDO);
    client.car.selectSteering(BOSCH_S);
    client.clearPrints();
    client.processAnswer(RUN);

    // TEST 동작
    client.setStep(Run_Test);
    client.clearPrints();
    client.processAnswer(TEST);

    EXPECT_NE(client.getAllPrints().find("Test..."), std::string::npos);
}

TEST_F(CarClientFixture, AllInputValidationErrors) {

    // Engine_Q
    client.setStep(Engine_Q);
    client.clearPrints();
    EXPECT_FALSE(client.isInputValid(99));
    EXPECT_NE(client.getAllPrints().find("엔진은"), std::string::npos);

    // brakeSystem_Q
    client.setStep(brakeSystem_Q);
    client.clearPrints();
    EXPECT_FALSE(client.isInputValid(99));
    EXPECT_NE(client.getAllPrints().find("제동장치는"), std::string::npos);

    // SteeringSystem_Q
    client.setStep(SteeringSystem_Q);
    client.clearPrints();
    EXPECT_FALSE(client.isInputValid(99));
    EXPECT_NE(client.getAllPrints().find("조향장치는"), std::string::npos);

    // Run_Test
    client.setStep(Run_Test);
    client.clearPrints();
    EXPECT_FALSE(client.isInputValid(99));
    EXPECT_NE(client.getAllPrints().find("Run 또는 Test"), std::string::npos);
}
