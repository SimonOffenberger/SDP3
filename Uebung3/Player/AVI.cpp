#include "AVI.hpp"

void AVI::Print(std::ostream & ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << "AVI-Format";

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;
}
