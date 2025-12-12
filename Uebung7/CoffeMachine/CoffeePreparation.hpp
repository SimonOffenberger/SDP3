/**
 * @file CoffeePreparation.hpp
 * @brief Declares a queue-based coffee preparation pipeline with output helpers.
 */
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

	/**
	 * @brief Enqueue a coffee for preparation.
	 * @param coffee Ownership of the coffee instance to queue.
	 */
	void Prepare(ICoffee::Uptr coffee);

	/**
	 * @brief Print the next coffee description and price to a stream.
	 * @param ost Target output stream; must be valid.
	 */
	void Display(std::ostream& ost);

	/**
	 * @brief Remove and return the next finished coffee.
	 * @return Unique pointer to the prepared coffee.
	 */
	ICoffee::Uptr Finished();

private:
	std::queue<ICoffee::Uptr> mCoffeeQueue;
};


#endif // !COFFEE_PREPARATION_HPP