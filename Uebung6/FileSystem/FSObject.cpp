#include "FSObject.hpp"
#include <string>

IFolder::Sptr FSObject::AsFolder()
{
    return nullptr;
}

std::shared_ptr<const ILink> FSObject::AsLink() const
{
	return nullptr;
}

std::string_view FSObject::GetName() const
{
    return std::string_view(m_Name);
}

void FSObject::SetName(std::string_view name)
{
    m_Name = name;
}

void FSObject::SetParant(Sptr parent)
{
	if (parent == nullptr) throw ERROR_NULLPTR;
	m_Parent = move(parent);
}

FSObj_Wptr FSObject::GetParent() const
{
	return m_Parent;
}
