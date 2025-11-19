/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FS_OBJECT_HPP
#define FS_OBJECT_HPP

#include "Object.h"
#include "IVisitor.hpp"
#include "IFolder.hpp"

#include <memory>

class FSObject : public Object
{
public:
	using Sptr = std::shared_ptr<FSObject>;
	using Wptr = std::weak_ptr<FSObject>;

	virtual void Accept(IVisitor& visit) = 0;

	virtual IFolder::Sptr AsFolder();

	std::string_view GetName();

	void SetName(std::string_view name);

private:
};

#endif
