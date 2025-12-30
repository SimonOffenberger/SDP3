/**
 * @file Mocha.cpp
 * @brief Implements the mocha coffee pricing and description.
 */
#include "Mocha.hpp"
#include "CoffeeInfo.hpp"

double Mocha::GetCost() const
{
	return CoffeeInfo::mMochaPrice;
}

std::string Mocha::GetDescription() const
{
	return CoffeeInfo::mMochaInfo + ":";
}