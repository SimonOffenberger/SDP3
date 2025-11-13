/*****************************************************************//**
 * \file   Identifier.cpp
 * \brief  Generalization of Types and Variables
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#include "Identifier.hpp"


std::string Identifier::GetName() const{
	return m_name;
}

void Identifier::SetName(const std::string& name)
{
	if (name.empty()) throw Identifier::ERROR_EMPTY_STRING;

	m_name = name;
}
