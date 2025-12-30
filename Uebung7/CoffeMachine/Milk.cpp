/**
 * @file Milk.cpp
 * @brief Implements the milk ingredient decorator behavior.
 */
#include "Milk.hpp"
#include "CoffeeInfo.hpp"

double Milk::GetCost() const
{
   return CoffeeInfo::mMilkPrice + Ingredient::GetCost();
}

std::string Milk::GetDescription() const
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mMilkInfo + ",";
}
