#include "WMV.hpp"

void WMV::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << "WMV-Format";

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;
}