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

	// Public Error Messages
	using Sptr = std::shared_ptr<Link>;
	using Uptr = std::unique_ptr<Link>;
	using Wptr = std::weak_ptr<Link>;

    /** \brief Constructor taking a shared pointer to the linked FSObject
	 * \param linked_obj Shared pointer to the referenced FSObject
	 * \param name Optional name for the link
	 */
	explicit Link(FSObj_Sptr linked_obj, std::string_view name = "");

	/** \brief Cast this object to link interface
	 * \return Shared pointer to ILink
	 */
	virtual std::shared_ptr<const ILink> AsLink() const override;

    /** \brief Get the referenced FSObject
	 * \return Shared pointer to the referenced FSObject or nullptr if expired
	 */
	virtual FSObj_Sptr GetReferncedFSObject() const override;

    /** \brief Accept a visitor
	 * \param visit Visitor to accept
	 */
	virtual void Accept(IVisitor& visit) override;

private:
    /** \brief Weak pointer to the linked FSObject
	*/
	FSObj_Wptr m_Ref;
};

#endif
