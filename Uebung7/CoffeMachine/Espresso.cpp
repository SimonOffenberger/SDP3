#include "Espresso.hpp"
#include "CoffeeInfo.hpp"


double Espresso::GetCost()
{
	return CoffeeInfo::mEspressoPrice;
}

std::string Espresso::GetDescription()
{
	return CoffeeInfo::mEspressoInfo + ":";
}
