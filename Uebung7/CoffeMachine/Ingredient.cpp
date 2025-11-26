#include "Ingredient.hpp"



Ingredient::Ingredient(ICoffee::Uptr mCoffeeIngredient)
{
    if (mCoffeeIngredient == nullptr) throw "";

    mDecorator = move(mCoffeeIngredient);
}

double Ingredient::GetCost()
{   
    return mDecorator->GetCost();
}

std::string Ingredient::GetDescription()
{
    return mDecorator->GetDescription();
}
