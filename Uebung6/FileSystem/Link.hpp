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

class Link: public FSObject
{
public:

	explicit Link(FSObject::Sptr linked_obj);

	FSObject::Sptr operator*();

private:

	FSObject::Wptr m_Ref;
};

#endif
