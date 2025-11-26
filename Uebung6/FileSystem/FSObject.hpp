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
#include <vector>

class FSObject : public Object
{
public:
	virtual void Accept(IVisitor& visit) = 0;
	virtual IFolder::Sptr AsFolder();
	std::string_view GetName();
	void SetName(std::string_view name);

private:
	std::string m_Name;
	FSObj_Wptr m_Parent;
};

#endif
