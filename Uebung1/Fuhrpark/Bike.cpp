/*****************************************************************//**
 * \file   Bike.cpp
 * \brief  Implementation of the Bike Class
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "Bike.hpp"

using namespace std;


std::ostream& Bike::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << endl << left << setw(14) << "Fahrzeugart:" << "Motorrad" << endl;
	ost << left << setw(14) << "Marke:" << GetBrand() << endl;
	ost << left << setw(14) << "Kennzeichen:" << GetPlate() << endl;
	GetDriveRecord().Print(ost);

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}


Vehicle const* Bike::Clone() const
{
	return new Bike(*this);
}
