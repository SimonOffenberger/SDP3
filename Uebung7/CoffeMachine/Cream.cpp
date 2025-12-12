/**
 * @file Cream.cpp
 * @brief Implements the cream ingredient decorator behavior.
 */
#include "Cream.hpp"
#include "CoffeeInfo.hpp"

double Cream::GetCost()
{
	return CoffeeInfo::mCreamPrice + Ingredient::GetCost();
}

std::string Cream::GetDescription()
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mCreamInfo + ",";
}