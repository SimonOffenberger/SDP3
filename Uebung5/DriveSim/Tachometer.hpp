#ifndef TACHOMETER_HPP
#define TACHOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"


class Tachometer : public Meter {
public:

	virtual void Update() override;

	Tachometer(Car & car, WindowsDisplay::SPtr display);
									
private:

	Car & m_car;

	double m_speed;
};


#endif // !TACHOMETER_HPP