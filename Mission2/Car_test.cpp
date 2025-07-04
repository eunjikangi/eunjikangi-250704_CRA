#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Car.h"

using namespace testing;

class CarFixture : public Test {
protected:
    Car car;
};

TEST_F(CarFixture, SelectCarTypeSetsType) {
    car.selectCarType(SEDAN);
    EXPECT_EQ(car.carType, SEDAN);

    car.selectCarType(SUV);
    EXPECT_EQ(car.carType, SUV);

    car.selectCarType(TRUCK);
    EXPECT_EQ(car.carType, TRUCK);
}

TEST_F(CarFixture, SelectEngineSetsEngine) {
    car.selectEngine(GM);
    EXPECT_EQ(car.engine, GM);

    car.selectEngine(TOYOTA);
    EXPECT_EQ(car.engine, TOYOTA);

    car.selectEngine(WIA);
    EXPECT_EQ(car.engine, WIA);
}

TEST_F(CarFixture, SelectBrakeTest) {
    car.selectBrake(MANDO);
    EXPECT_EQ(car.brake, MANDO);

    car.selectBrake(CONTINENTAL);
    EXPECT_EQ(car.brake, CONTINENTAL);

    car.selectBrake(BOSCH_B);
    EXPECT_EQ(car.brake, BOSCH_B);
}

TEST_F(CarFixture, SelectSteeringTest) {
    car.selectSteering(BOSCH_S);
    EXPECT_EQ(car.steering, BOSCH_S);

    car.selectSteering(MOBIS);
    EXPECT_EQ(car.steering, MOBIS);
}

TEST_F(CarFixture, IsValidReturnsFalseForInvalidCombinations_1) {
    car.selectCarType(SEDAN);
    car.selectBrake(CONTINENTAL);
    EXPECT_FALSE(car.isValid());

    car.selectCarType(SUV);
    car.selectEngine(TOYOTA);
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarFixture, IsValidReturnsFalseForInvalidCombinations_2) {
    car.selectCarType(SEDAN);
    car.selectBrake(CONTINENTAL);
    car.run();
    EXPECT_FALSE(car.isValid());
}

TEST_F(CarFixture, IsValidReturnsFalseForInvalidCombinations_3) {
    car.selectCarType(SEDAN);
    car.selectBrake(BROKEN_ENGINE);
    car.run();
}

TEST_F(CarFixture, RunPrintsErrorForBrokenEngine) {
    car.selectCarType(SEDAN);
    car.selectEngine(BROKEN_ENGINE);
}


TEST_F(CarFixture, IsValidReturnsTrueForValidCombination) {
    car.selectCarType(SEDAN);
    car.selectEngine(GM);
    car.selectBrake(MANDO);
    car.selectSteering(BOSCH_S);
    EXPECT_TRUE(car.isValid());
}

TEST_F(CarFixture, carTestMethodTest) {
    car.selectCarType(SEDAN);
    car.selectBrake(CONTINENTAL);
    car.test();
    // FAIL

    car.selectCarType(SUV);
    car.selectEngine(TOYOTA);
    car.test();
    // FAIL

    car.selectCarType(TRUCK);
    car.selectEngine(WIA);
    car.test();
    // FAIL

    car.selectCarType(TRUCK);
    car.selectBrake(MANDO);
    car.test();
    // FAIL

    car.selectCarType(BOSCH_B);
    car.selectBrake(CONTINENTAL);
    car.test();
    // FAIL
}

TEST_F(CarFixture, carTestMethodTest2) {
    car.selectCarType(TRUCK);
    car.selectBrake(MANDO);
    car.test();
    // FAIL
}

TEST_F(CarFixture, carTestMethodTest3) {
    car.selectBrake(BOSCH_B);
    car.selectSteering(MOBIS);
    car.test();
    // FAIL
}