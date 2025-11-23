/*****************************************************************//**
 * \file   IDisplay.hpp
 * \brief  Interface for all display types used by vehicles.
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include <memory>

 /**
  * \class IDisplay
  * \brief Interface for display observer implementations.
  */
class IDisplay {
public:

    /**
     * \brief Shared pointer alias for IDisplay.
     */
    using Sptr = std::shared_ptr<IDisplay>;

    /**
     * \brief Called when the observed subject updates its state.
     */
    virtual void Update() = 0;

    /**
     * \brief Virtual destructor.
     *
     * Ensures proper cleanup of derived display types.
     */
    virtual ~IDisplay() = default;
};

#endif // !IDISPLAY_HPP
