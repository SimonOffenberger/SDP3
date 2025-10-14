#ifndef BIKE_HPP
#define BIKE_HPP

#include "Vehicle.hpp"

class Bike : public Vehicle {
public:

	/**
	 * \brief CTOR of a Bike -> calles the Base Class vehicle CTOR.
	 *
	 * \param brand string that identifies the brand.
	 * \param fuelType Fueltype of the Bike
	 * \param plate string that identifies the plate.
	 */
	Bike(const std::string& brand, const TFuel& fuelType, const std::string& plate) : Vehicle(brand, fuelType, plate) {}

	/**
	 * \brief Function that print all the vehicle specific info with the drive record.
	 *
	 * \param ost where the data should be printed at
	 * \return referenced ostream
	 */
	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

	/**
	 * @brief Creates a clone of the vehicle.
	 *
	 * \return a excat replicate of a vehicle
	 */
	virtual Vehicle const* Clone() const;

private:
};


#endif 