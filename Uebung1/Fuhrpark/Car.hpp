#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"

class Car : public Vehicle {
public:

	Car(const std::string & brand,const TFuel & fuelType, const std::string & plate) : Vehicle(brand, fuelType,plate) {}

	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

	/**
	 * @brief Creates a clone of the vehicle.
	 *
	 * \return a excat replicate of a vehicle
	 */
	virtual Vehicle const* Clone() const;

private:
};


#endif // !1