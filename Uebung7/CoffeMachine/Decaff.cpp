#include "Decaff.hpp"
#include "CoffeeInfo.hpp"

double Decaff::GetCost()
{
	return CoffeeInfo::mDecaffPrice;
}

std::string Decaff::GetDescription()
{
	return CoffeeInfo::mDecaffInfo + ":";
}