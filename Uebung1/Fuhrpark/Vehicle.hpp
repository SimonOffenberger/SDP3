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
#include "TFuel.hpp"

class Vehicle: public Object {
public:

	/**
	* Defintions of the Exceptionmessages
	*/
	inline static const std::string ERROR_EMPTY_STRING = "ERROR: Passed in empty string!";

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


	/**
	 * \brief Print function that is implementet by dirved Classes.
	 * 
	 * \param ost Reference to an ostream where the Result should be printed at
	 * \return referenced ostream
     * \throw ERROR_BAD_OSTREAM
	 * \throw ERROR_WRITE_FAIL
	 */
	virtual std::ostream& Print(std::ostream& ost = std::cout) const = 0;


protected:

	/**
	 * \brief protected CTOR of a vehicle.
	 * \brief protected because it is a abstract class
	 * 
	 * \param plate : string that represents the plate of the vehicle
	 * \param brand : string that represents the brand of the vehicle
	 * \param fuelType : Fuel type of the vehicle
	 */
	Vehicle(const std::string& brand, const TFuel& fuelType, const std::string& plate);

private:
	std::string m_brand;
	std::string m_plate;
	TFuel m_fuel;
	DriveRecord m_record;
};


#endif // !1