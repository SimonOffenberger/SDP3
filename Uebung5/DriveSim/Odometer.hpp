#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

class Odometer :public Meter {
public:

	virtual void Update() override;

	Odometer(Car::Sptr car, WindowsDisplay::SPtr display);
						

private:

	Car::Sptr m_car;

	double m_milage;
};


#endif // !ODOMETER_HPP
