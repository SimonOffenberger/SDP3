#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

class Odometer :public Meter {
public:

	virtual void Update() override;

	Odometer(Car& car) : m_car{ car }, m_milage{ 0 } {}

private:

	const Car& m_car;

	unsigned int m_milage;
};


#endif // !ODOMETER_HPP
