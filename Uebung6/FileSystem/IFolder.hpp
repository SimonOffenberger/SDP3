/*****************************************************************//**
 * \file IFolder.hpp
 * \brief Interface for folder-like FSObjects
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef IFOLDER_HPP
#define IFOLDER_HPP
#include <memory>

// fwd declaration
class FSObject;

// Type aliases
using FSObj_Sptr = std::shared_ptr<FSObject>;
using FSObj_Wptr = std::weak_ptr<FSObject>;

class IFolder
{
public:

	using Sptr = std::shared_ptr<IFolder>;

	/** \brief Add a child FSObject to the folder
	 * \param fsobj Shared pointer to the FSObject to add
	 */
	virtual void Add(FSObj_Sptr fsobj) =0;

	/** \brief Get a child by index
	 * \param idx Index of the child
	 * \return Shared pointer to the child or nullptr if out of range
	 */
	virtual FSObj_Sptr GetChild(size_t idx) =0;

	/** \brief Remove a child FSObject from the folder
	 * \param fsobj Shared pointer to the FSObject to remove
	 */
	virtual void Remove(FSObj_Sptr fsobj) =0;

	virtual ~IFolder() = default;

private:
};

#endif