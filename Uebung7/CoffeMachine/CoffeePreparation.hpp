#ifndef COFFEE_PREPARATION_HPP
#define	COFFEE_PREPARATION_HPP

#include "ICoffee.hpp"
#include <queue>
#include <string>
#include <iostream>

class CoffeePreparation {
public:
	inline static const std::string ERROR_NULLPTR = "Error Nullptr!";
	inline static const std::string ERROR_BAD_OSTREAM = "Error Bad Ostream";

	void Prepare(ICoffee::Uptr coffee);

	void Display(std::ostream& ost);

	ICoffee::Uptr Finished();

private:
	std::queue<ICoffee::Uptr> mCoffeeQueue;
};


#endif // !COFFEE_PREPARATION_HPP