#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "Vehicle.hpp"

class Truck : public Vehicle {
public:

	/**
	 * \brief CTOR of a Truck -> calles the Base Class vehicle CTOR.
	 * 
	 * \param brand string that identifies the brand.
	 * \param fuelType Fueltype of the Truck
	 * \param plate string that identifies the plate.
	 */
	Truck(const std::string& brand, const TFuel& fuelType, const std::string& plate) : Vehicle(brand, fuelType, plate) {}

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