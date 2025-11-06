/*****************************************************************//**
 * \file   IECVariable.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#include "IECVariable.hpp"
#include <sstream>
#include <string>

using namespace std;

std::string const& IECVariable::Save()
{
	stringstream line;

	line << "VAR " << m_type->GetType() << " : " << m_name << ";";

	return line.str();
}

std::string const& IECVariable::Load(std::string const& fileLine)
{
	return "Hello World";
}
