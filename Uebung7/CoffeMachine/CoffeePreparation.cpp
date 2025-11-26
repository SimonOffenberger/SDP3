#include "CoffeePreparation.hpp"

void CoffeePreparation::Prepare(ICoffee::Uptr coffee)
{
	if (coffee == nullptr) throw ERROR_NULLPTR;
	
	mCoffeeQueue.push(move(coffee));
}

void CoffeePreparation::Display(std::ostream& ost)
{
	if (ost.bad()) throw ERROR_BAD_OSTREAM;

	std::string description = mCoffeeQueue.front()->GetDescription();
	
	// discard the last "," to fullfill the requirement
	// in the excersise
	*description.rbegin() = ' ';
	
	ost << description;
	ost << mCoffeeQueue.front()->GetCost() << " Euro" << std::endl;
}

ICoffee::Uptr CoffeePreparation::Finished()
{
	ICoffee::Uptr retCoffee = move(mCoffeeQueue.front());
	mCoffeeQueue.pop();

	return move(retCoffee);
}
