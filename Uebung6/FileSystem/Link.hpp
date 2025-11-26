/*****************************************************************//**
 * \file Link.hpp
 * \brief A link to another FSObject
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
    /* \brief Constructor taking a shared pointer to the linked FSObject
	*/
	explicit Link(FSObj_Sptr linked_obj);

    /* \brief Dereference operator to access the linked FSObject
    *  \return A shared pointer to the linked FSObject
	*/
	FSObj_Sptr operator*();

    /* \brief Accept a visitor
    *  \param visit The visitor to accept
	*/
	virtual void Accept(IVisitor& visit) override;

private:
    /* \brief Weak pointer to the linked FSObject
	*/
	FSObj_Wptr m_Ref;
};

#endif
