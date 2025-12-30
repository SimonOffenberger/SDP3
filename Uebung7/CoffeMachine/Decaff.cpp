/**
 * @file Decaff.cpp
 * @brief Implements the decaffeinated coffee pricing and description.
 */
#include "Decaff.hpp"
#include "CoffeeInfo.hpp"

double Decaff::GetCost() const
{
	return CoffeeInfo::mDecaffPrice;
}

std::string Decaff::GetDescription() const
{
	return CoffeeInfo::mDecaffInfo + ":";
}