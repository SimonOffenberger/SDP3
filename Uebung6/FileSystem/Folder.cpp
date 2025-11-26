#include "Folder.hpp"

void Folder::Add(FSObj_Sptr fsobj)
{
    m_Children.push_back(fsobj);
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
    return Folder::Sptr(this);
}

void Folder::Accept(IVisitor& visit)
{
    visit.Visit(*this);
}

