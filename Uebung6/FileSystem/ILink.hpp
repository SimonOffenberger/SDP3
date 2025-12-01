/*****************************************************************//**
 * \file ILink.hpp
 * \brief Interface for folder-like FSObjects
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef ILINK_HPP
#define ILINK_HPP
#include <memory>

 // fwd declaration
class FSObject;

// Type aliases
using FSObj_Sptr = std::shared_ptr<FSObject>;
using FSObj_Wptr = std::weak_ptr<FSObject>;

class ILink
{
public:

	using Sptr = std::shared_ptr<ILink>;

	/** \brief Get the referenced FSObject
	 * \return Shared pointer to the referenced FSObject or nullptr if expired
	 */
	virtual FSObj_Sptr GetReferncedFSObject() const =0;

	/** \brief Virtual destructor */
	virtual ~ILink() = default;

private:
};

#endif