#include "Link.hpp"

Link::Link(FSObj_Sptr linked_obj)
{
    m_Ref = move(linked_obj);
}

FSObj_Sptr Link::operator*()
{
    return m_Ref.lock();
}

void Link::Accept(IVisitor& visit)
{
    visit.Visit(*this);
}
