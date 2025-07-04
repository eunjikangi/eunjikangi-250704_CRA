#pragma once

class IState
{
public:
	virtual ~IState() = default;
	virtual void selectCarType() = 0;
	virtual void selectEngine() = 0;
	virtual void selectBrake() = 0;
	virtual void selectSteering() = 0;

protected:
};