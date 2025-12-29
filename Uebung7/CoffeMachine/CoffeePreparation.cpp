/**
 * @file CoffeePreparation.cpp
 * @brief Implements the coffee preparation queue with display and pickup helpers.
 */
#include "CoffeePreparation.hpp"

void CoffeePreparation::Prepare(ICoffee::Uptr coffee)
{
	if (coffee == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
	
	mCoffeeQueue.push_back(move(coffee));
}

void CoffeePreparation::Display(std::ostream& ost)
{
	if (ost.bad()) throw std::invalid_argument(ERROR_BAD_OSTREAM);
	if (mCoffeeQueue.empty()) throw std::runtime_error(ERROR_NO_COFFE_IN_MACHINE);


	for(const auto & coffee : mCoffeeQueue) {
		std::string description = coffee->GetDescription();

		// discard the last "," to fullfill the requirement
		// in the excersise
		if (!description.empty()) {
			*description.rbegin() = ' ';
		}
		ost << description;
		ost << coffee->GetCost() << " Euro" << std::endl;
	}


}

ICoffee::Uptr CoffeePreparation::Finished()
{
	if (mCoffeeQueue.empty()) throw std::runtime_error(ERROR_NO_COFFE_IN_MACHINE);

	ICoffee::Uptr retCoffee = move(mCoffeeQueue.front());
	mCoffeeQueue.pop_front();

	return move(retCoffee);
}
