/**
 * @file CoffeePreparation.hpp
 * @brief Declares a queue-based coffee preparation pipeline with output helpers.
 */
#ifndef COFFEE_PREPARATION_HPP
#define	COFFEE_PREPARATION_HPP

#include "ICoffee.hpp"
#include <deque>
#include <string>
#include <iostream>

class CoffeePreparation {
public:
	inline static const std::string ERROR_NULLPTR = "Error Nullptr!";
	inline static const std::string ERROR_BAD_OSTREAM = "Error Bad Ostream";
	inline static const std::string ERROR_NO_COFFE_IN_MACHINE = "Error No Coffe in the Machine!";

	CoffeePreparation() = default;

	/**
	 * @brief Enqueue a coffee for preparation.
	 * @param coffee Ownership of the coffee instance to queue.
	 */
	void Prepare(ICoffee::Uptr coffee);

	/**
	 * @brief Prints all coffees description and price to a stream.
	 * @param ost Target output stream; must be valid.
	 */
	void Display(std::ostream& ost) const;

	/**
	 * @brief Remove and return the next finished coffee.
	 * @return Unique pointer to the prepared coffee.
	 */
	ICoffee::Uptr Finished();

	void operator=(CoffeePreparation & prep) = delete;
	CoffeePreparation(CoffeePreparation& prep) = delete;

private:
	std::deque<ICoffee::Uptr> mCoffeeQueue;
};


#endif // !COFFEE_PREPARATION_HPP