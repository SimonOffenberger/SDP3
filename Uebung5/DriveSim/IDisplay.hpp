/*****************************************************************//**
 * \file   IDisplay.hpp
 * \brief  Interface for all display types
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include <memory>

class IDisplay{
public:
	/**
     * \brief Shared pointer type to IDisplay
	 */
	using Sptr = std::shared_ptr<IDisplay>;

	/**
     * \brief Update the display with new values
	 */
	virtual	void Update() = 0;

	virtual ~IDisplay() = default;

protected:
	IDisplay() = default;
};

#endif // !IDISPLAY_HPP