#ifndef TACHOMETER_HPP
#define TACHOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

class Tachometer : public Meter {
public:

	virtual void Update() override;

	Tachometer(Car& car) : m_car{ car }, m_speed{ 0 } {}

private:

	const Car & m_car;

	unsigned int m_speed;
};


#endif // !TACHOMETER_HPP