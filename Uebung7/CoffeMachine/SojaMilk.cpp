#include "SojaMilk.hpp"
#include "CoffeeInfo.hpp"

double SojaMilk::GetCost()
{
	return CoffeeInfo::mSojaMilkPrice + Ingredient::GetCost();
}

std::string SojaMilk::GetDescription()
{
	return Ingredient::GetDescription() + " " + CoffeeInfo::mSojaMilkInfo;
}