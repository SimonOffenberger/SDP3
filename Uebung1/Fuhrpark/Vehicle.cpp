/*****************************************************************//**
 * \file   Vehicle.cpp
 * \brief  Implementation of the abstract vehicle class
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#include "Vehicle.hpp"

/**
* \brief Getter for the brand member.
*
* \return string with the brand name
*/
std::string Vehicle::GetBrand() const
{
    return m_brand;
}

/**
* \brief Getter for the plate member.
*
* \return string with the plate name
*/
std::string Vehicle::GetPlate() const
{
    return m_plate;
}

/**
* \brief Getter for the fuel member.
*
* \return TFuel with the specified fuel type
*/
TFuel Vehicle::GetFuelType() const
{
    return m_fuel;
}

/**
* \brief Getter for the drive record.
*
* \return const refernce to the drive record
*/
const DriveRecord & Vehicle::GetDriveRecord() const
{
    return m_record;
}

/**
* \brief Methode for adding a record entry to the drive record collection.
*
* \param entry : Entry which should be added to the drive recod
*/
void Vehicle::AddRecord(const RecordEntry& entry)
{
    m_record.AddRecord(entry);
}

/**
* \brief Getter for the total milage of a vehicle.
*
* \return Total milage of a vehicle
*/
size_t Vehicle::GetMilage() const
{
    return m_record.GetMilage();
}


