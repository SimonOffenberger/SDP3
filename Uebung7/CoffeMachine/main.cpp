
#include "Espresso.hpp"
#include "Milk.hpp"

#include <memory>
#include <iostream>

int main()
{
	ICoffee::Uptr Coff{ std::make_unique<Milk>(std::make_unique<Milk>(std::make_unique<Milk>(std::make_unique<Espresso>()))) };

	std::cout << Coff->GetDescription();
}