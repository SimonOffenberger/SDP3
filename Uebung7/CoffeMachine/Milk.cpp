/**
 * @file Milk.cpp
 * @brief Implements the milk ingredient decorator behavior.
 */
#include "Milk.hpp"
#include "CoffeeInfo.hpp"

double Milk::GetCost()
{
   return CoffeeInfo::mMilkPrice + Ingredient::GetCost();
}

std::string Milk::GetDescription()
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mMilkInfo + ",";
}
