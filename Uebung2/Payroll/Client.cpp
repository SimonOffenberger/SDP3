#include "Client.hpp"
#include "Test.hpp"
#include "ComissionWorker.hpp"

bool Client::TestCompanyGetter(std::ostream& ost, IComp& company) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;



	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;
}
