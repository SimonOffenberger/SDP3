/*****************************************************************//**
 * \file   Truck.cpp
 * \brief  Implementation of a Truck
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "Truck.hpp"

using namespace std;

/**
* \brief Function that print all the vehicle specific info with the drive record.
*
* \param ost where the data should be printed at
* \return referenced ostream
*/
std::ostream& Truck::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << endl << left << setw(14) << "Fahrzeugart:" << "LKW" << endl;
	ost << left << setw(14) << "Marke:" << GetBrand() << endl;
	ost << left << setw(14) << "Kennzeichen:" << GetPlate() << endl;
	GetDriveRecord().Print(ost);

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}

/**
* @brief Creates a clone of the vehicle.
*
* \return a excat replicate of a vehicle
*/
Vehicle const* Truck::Clone() const
{
	return new Truck(*this);
}
