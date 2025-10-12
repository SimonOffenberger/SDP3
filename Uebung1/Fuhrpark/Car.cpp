#include "Car.hpp"

using namespace std;

std::ostream& Car::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost <<endl<< left << setw(14) << "Fahrzeugart:" << "Auto" << endl;
	ost << left << setw(14) << "Marke:" << GetBrand() << endl;
	ost << left << setw(14) << "Kennzeichen:" << GetPlate() << endl;
	GetDriveRecord().Print(ost);

		if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}

Vehicle const* Car::Clone() const
{
	return new Car(*this);
}
