/*****************************************************************//**
 * \file   Vehicle.hpp
 * \brief  This class imlements an abstract vehicle which is used in the
 * \brief  Garage class. It implements all the core featues of a vehicle
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Object.hpp"
#include "DriveRecord.hpp"

// Enumeration for a fuel type
enum TFuel {
	Diesel = 0,
	Benzin = 1,
	Elektro = 2,
};

class Vehicle: public Object {
public:

	/**
	 * \brief Getter for the brand member.
	 * 
	 * \return string with the brand name
	 */
	std::string GetBrand() const;

	/**
	 * \brief Getter for the plate member.
	 * 
	 * \return string with the plate name
	 */
	std::string GetPlate() const;

	/**
	 * \brief Getter for the fuel member.
	 * 
	 * \return TFuel with the specified fuel type
	 */
	TFuel GetFuelType() const;

	/**
	 * \brief Getter for the drive record.
	 * 
	 * \return const refernce to the drive record
	 */
	const DriveRecord & GetDriveRecord() const;

	/**
	 * \brief Methode for adding a record entry to the drive record collection.
	 * 
	 * \param entry : Entry which should be added to the drive recod
	 */
	void AddRecord(const RecordEntry& entry);

	/**
	 * \brief Getter for the total milage of a vehicle.
	 * 
	 * \return Total milage of a vehicle
	 */
	size_t GetMilage() const;

	/**
	 * @brief Creates a clone of the vehicle.
	 *
	 * \return a excat replicate of a vehicle
	 */
	virtual Vehicle const* Clone() const = 0;

protected:

	/**
	 * \brief protected CTOR of a vehicle.
	 * \brief protected because it is a abstract class
	 * 
	 * \param brand : string that represents the brand of the vehicle
	 * \param fuelType : Fuel type of the vehicle
	 */
	Vehicle(const std::string& brand, const TFuel& fuelType, const std::string& plate) : m_brand{ brand }, m_fuel{ fuelType }, m_plate{plate} {}

private:
	std::string m_brand;
	std::string m_plate;
	TFuel m_fuel;
	DriveRecord m_record;
};


#endif // !1