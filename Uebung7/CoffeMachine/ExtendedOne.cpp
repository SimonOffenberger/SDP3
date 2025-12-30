/**
 * @file ExtendedOne.cpp
 * @brief Implements the extended coffee variant pricing and description.
 */
#include "ExtendedOne.hpp"
#include "CoffeeInfo.hpp"


double ExtendedOne::GetCost() const
{
	return CoffeeInfo::mExtendedPrice;
}

std::string ExtendedOne::GetDescription() const
{
	return CoffeeInfo::mExtendedInfo + ":";
}