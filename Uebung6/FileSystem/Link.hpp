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

class Link : public FSObject, public ILink, public std::enable_shared_from_this<Link>
{
public:

    /* \brief Constructor taking a shared pointer to the linked FSObject
	*/
	explicit Link(FSObj_Sptr linked_obj);

	virtual std::shared_ptr<const ILink> AsLink() const override;

    /* \brief Dereference operator to access the linked FSObject
    *  \return A shared pointer to the linked FSObject
	*/
	virtual FSObj_Sptr GetReferncedFSObject() const override;

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
