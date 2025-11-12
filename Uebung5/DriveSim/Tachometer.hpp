#ifndef TACHOMETER_HPP
#define TACHOMETER_HPP

#include "Object.h"
#include "Meter.hpp"

class Tachometer : public Object, public Meter {
public:

	virtual void Update() override;

private:
	unsigned int m_speed;
};


#endif // !TACHOMETER_HPP