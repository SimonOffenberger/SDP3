/*****************************************************************//**
 * \file Link.cpp
 * \brief A link to another FSObject
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "Link.hpp"
#include <stdexcept>

/** \brief Construct a link to another FSObject */
Link::Link(FSObj_Sptr linked_obj, std::string_view name) : FSObject(name)
{
    if (linked_obj == nullptr) throw std::invalid_argument(Link::ERROR_NULLPTR);
    if (name.empty())          throw std::invalid_argument(Link::ERROR_STRING_EMPTY);
  
    m_Ref = move(linked_obj);
}

/** \brief Cast to ILink */
std::shared_ptr<const ILink> Link::AsLink() const
{
    return move(shared_from_this());
}

/** \brief Get referenced FSObject (shared_ptr) or nullptr */
FSObj_Sptr Link::GetReferncedFSObject() const
{
    return m_Ref.lock();
}

/** \brief Accept a visitor */
void Link::Accept(IVisitor& visit)
{
    visit.Visit(move(shared_from_this()));
}

FSObj_Sptr Link::Clone() const 
{
	// Call Copy Constructor of Link
    return make_shared<Link>(Link::Link(*this));
}
