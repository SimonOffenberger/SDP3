/**
 * @file Espresso.cpp
 * @brief Implements the espresso coffee pricing and description.
 */
#include "Espresso.hpp"
#include "CoffeeInfo.hpp"


double Espresso::GetCost() const
{
	return CoffeeInfo::mEspressoPrice;
}

std::string Espresso::GetDescription() const
{
	return CoffeeInfo::mEspressoInfo + ":";
}
