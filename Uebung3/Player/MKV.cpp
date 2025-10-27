#include "MKV.hpp"

void MKV::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << "MKV-Format";

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;
}