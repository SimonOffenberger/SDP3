/**
 * @file Ingredient.cpp
 * @brief Implements the decorator base class used by ingredient add-ons.
 */
#include "Ingredient.hpp"
#include <stdexcept>


Ingredient::Ingredient(ICoffee::Uptr mCoffeeIngredient)
{
    if (mCoffeeIngredient == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

    mDecorator = move(mCoffeeIngredient);
}

double Ingredient::GetCost() const
{   
    return mDecorator->GetCost();
}

std::string Ingredient::GetDescription() const
{
    return mDecorator->GetDescription();
}
