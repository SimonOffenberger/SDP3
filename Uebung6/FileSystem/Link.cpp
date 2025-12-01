#include "Link.hpp"

/** \brief Construct a link to another FSObject */
Link::Link(FSObj_Sptr linked_obj, std::string_view name) : FSObject(name)
{
    if (linked_obj == nullptr) throw Link::ERROR_NULLPTR;

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
    visit.Visit(shared_from_this());
}
