/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef LINK_HPP
#define LINK_HPP

#include "FSObject.hpp"
#include "IVisitor.hpp"

class Link: public FSObject
{
public:

	explicit Link(FSObj_Sptr linked_obj);

	FSObj_Sptr operator*();

	virtual void Accept(IVisitor& visit) override;

private:
	FSObj_Wptr m_Ref;
};

#endif
