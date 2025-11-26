/*****************************************************************//**
 * \file
 * \brief
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

	virtual void Add(FSObj_Sptr fsobj) = 0;

	virtual FSObj_Sptr GetChild(size_t idx) = 0;

	virtual void Remove(FSObj_Sptr fsobj) = 0;

	virtual ~IFolder() = default;

private:
};

#endif