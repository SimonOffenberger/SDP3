/*****************************************************************//**
 * \file   Bike.hpp
 * \brief  Header fo the specific Class Bike
 *
 * \author Simon
 * \date   October 2025
 *********************************************************************/
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
	 * \throw ERROR_EMPTY_STRING
	 */
	Bike(const std::string& brand, const TFuel& fuelType, const std::string& plate) : Vehicle(brand, fuelType, plate) {}

	/**
	 * \brief Function that print all the vehicle specific info with the drive record.
	 *
	 * \param ost where the data should be printed at
	 * \return referenced ostream
	 * \throw ERROR_BAD_OSTREAM
	 * \throw ERROR_WRITE_FAIL
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