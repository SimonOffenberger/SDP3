/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef IFOLDER_HPP
#define IFOLDER_HPP

#include "FSObject.hpp"

#include <memory>

class IFolder
{
public:

	using Sptr = std::shared_ptr<IFolder>;

	virtual void Add(FSObject::Sptr fsobj) = 0;

	virtual FSObject::Sptr GetChild(size_t idx) = 0;

	virtual void Remove(FSObject::Sptr fsobj) = 0;

	virtual ~IFolder() = default;

private:
};

#endif