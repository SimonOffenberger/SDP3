#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <string_view>
#include <memory>

#include "RPM_Sensor.hpp"
#include "Vehicle.hpp"

class Car : public Vehicle {
public:

	using Sptr = std::shared_ptr<Car>;

	static inline const std::string ERROR_WHEEL_DIA_0 = "ERROR: Wheel Diameter cannot be 0!";

	void Process();

	double GetCurrentSpeed();

	Car(const unsigned int & wheel_diameter, RPM_Sensor::Sptr wh_rpm_sen);

protected:

private:
	unsigned int m_wheel_rmp;
	unsigned int m_wheel_diameter;
	RPM_Sensor::Sptr m_wheel_rpm_sensor;
};

#endif // !CAR_HPP
