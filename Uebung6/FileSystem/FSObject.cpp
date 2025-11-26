#include "FSObject.hpp"
#include <string>

IFolder::Sptr FSObject::AsFolder()
{
    return nullptr;
}

std::string_view FSObject::GetName()
{
    return std::string_view(m_Name);
}

void FSObject::SetName(std::string_view name)
{
    m_Name = name;
}
