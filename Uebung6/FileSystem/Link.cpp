#include "Link.hpp"

Link::Link(FSObj_Sptr linked_obj, std::string_view name) : FSObject(name)
{
    m_Ref = move(linked_obj);
}

std::shared_ptr<const ILink> Link::AsLink() const
{
    return shared_from_this();
}

FSObj_Sptr Link::GetReferncedFSObject() const
{
    return m_Ref.lock();
}

void Link::Accept(IVisitor& visit)
{
    visit.Visit(shared_from_this());
}
