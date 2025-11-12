#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include "Object.h"
#include "Meter.hpp"

class Odometer : public Object, public Meter {
public:

	virtual void Update() override;

private:
	unsigned int m_milage;
};


#endif // !ODOMETER_HPP
