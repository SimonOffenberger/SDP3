
#include "Espresso.hpp"
#include "CoffeeInfo.hpp"

double ExtendedOne::GetCost()
{
	return CoffeeInfo::mEspressoPrice;
}

std::string ExtendedOne::GetDescription()
{
	return CoffeeInfo::mEspressoInfo;
}