/*****************************************************************//**
 * \file   Truck.cpp
 * \brief  Implementation of a Truck
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "Truck.hpp"

using namespace std;


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


Vehicle const* Truck::Clone() const
{
	return new Truck(*this);
}
