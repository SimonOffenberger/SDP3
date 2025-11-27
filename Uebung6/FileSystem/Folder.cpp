#include "Folder.hpp"

void Folder::Add(FSObj_Sptr fsobj)
{
	if (fsobj == nullptr) throw FSObject::ERROR_NULLPTR;
    fsobj->SetParant(std::move(shared_from_this()));
    m_Children.emplace_back(move(fsobj));
}

FSObj_Sptr Folder::GetChild(size_t idx)
{
    if(idx < m_Children.size())
    {
        return m_Children.at(idx);
    }

    return nullptr;
}

void Folder::Remove(FSObj_Sptr fsobj)
{
    m_Children.erase(
        std::remove(m_Children.begin(), m_Children.end(), fsobj), m_Children.end()
    );
}

IFolder::Sptr Folder::AsFolder()
{
    return shared_from_this();
}

void Folder::Accept(IVisitor& visit)
{
    visit.Visit(*this);

    for(auto& child : m_Children)
    {
        child->Accept(visit);
	}
}

