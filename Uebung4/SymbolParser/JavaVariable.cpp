/*****************************************************************//**
 * \file   JavaVariable.cpp
 * \brief  A Class for parsing java variables
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#include "JavaVariable.hpp"
#include <sstream>
#include <string>
#include "scanner.h"

using namespace pfc;
using namespace std;

static std::string ScanTypeName(scanner& scan)
{
	string typeName = scan.get_identifier();
	scan.next_symbol();
	return typeName;
}

static std::string ScanVarName(scanner& scan)
{
	string varName;
	varName = scan.get_identifier();

	return varName;
}

std::string JavaVariable::GetSaveLine() const
{
	stringstream line;

	if (m_type != nullptr) {
		line << m_type->GetType() << " " << m_name;
	}

	return line.str();
}

std::string JavaVariable::LoadTypeName(std::string const& fileLine) const
{
	stringstream lineStream;
	lineStream << fileLine;
	scanner scan{lineStream};
	
	return ScanTypeName(scan);
}

std::string JavaVariable::LoadVarName(std::string const& fileLine) const
{
	stringstream lineStream;
	lineStream << fileLine;
	scanner scan{ lineStream };

	string typeName = ScanTypeName(scan);
	string varName = ScanVarName(scan);
	if (typeName.empty()) varName = "";
	
	return varName;
}
