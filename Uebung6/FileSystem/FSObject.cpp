/*****************************************************************//**
 * \file FSObject.cpp
 * \brief Base class for filesystem objects
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "FSObject.hpp"
#include <string>
#include <stdexcept>

IFolder::Sptr FSObject::AsFolder()
{
    return nullptr;
}

std::shared_ptr<const IFolder> FSObject::AsFolder() const
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
    if (name.empty()) throw std::invalid_argument(ERROR_STRING_EMPTY);
    m_Name = name;
}

void FSObject::SetParant(Sptr parent)
{
	if (parent == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
	m_Parent = move(parent);
}

FSObject::FSObject(std::string_view name)
{
    if (name.empty()) throw std::invalid_argument(ERROR_STRING_EMPTY);
    m_Name = name;
}

FSObj_Wptr FSObject::GetParent() const
{
	return m_Parent;
}

