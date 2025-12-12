/**
 * @file Sugar.cpp
 * @brief Implements the sugar ingredient decorator behavior.
 */
#include "Sugar.hpp"
#include "CoffeeInfo.hpp"

double Sugar::GetCost()
{
	return CoffeeInfo::mSugarPrice + Ingredient::GetCost();
}

std::string Sugar::GetDescription()
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mSugarInfo + ",";
}