#include "Decaff.hpp"
#include "CoffeeInfo.hpp"

double Decaff::GetCost()
{
	return CoffeeInfo::mEspressoPrice;
}

std::string Decaff::GetDescription()
{
	return CoffeeInfo::mEspressoInfo;
}