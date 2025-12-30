/**
 * @file SojaMilk.cpp
 * @brief Implements the soja milk ingredient decorator behavior.
 */
#include "SojaMilk.hpp"
#include "CoffeeInfo.hpp"

double SojaMilk::GetCost() const
{
	return CoffeeInfo::mSojaMilkPrice + Ingredient::GetCost();
}

std::string SojaMilk::GetDescription() const
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mSojaMilkInfo + ",";
}