/**
 * @file ExtendedOne.cpp
 * @brief Implements the extended coffee variant pricing and description.
 */
#include "ExtendedOne.hpp"
#include "CoffeeInfo.hpp"


double ExtendedOne::GetCost()
{
	return CoffeeInfo::mExtendedPrice;
}

std::string ExtendedOne::GetDescription()
{
	return CoffeeInfo::mExtendedInfo + ":";
}