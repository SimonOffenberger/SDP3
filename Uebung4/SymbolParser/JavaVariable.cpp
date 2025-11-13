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

/**
 * \brief Scans an input string for the Type name of the Var.
 *
 * \param scan Reference to scanner object
 * \return emtpy string if no valid type name is found
 * \return name of type
 */
static std::string ScanTypeName(scanner& scan)
{
	string typeName = scan.get_identifier();
	scan.next_symbol();
	return typeName;
}

/**
 * \brief Scans an input string for the Variable name of the Var.
 *
 * \param scan Reference to scanner object
 * \return emtpy string if no valid Variable name is found
 * \return name of Variable
 */
static std::string ScanVarName(scanner& scan)
{
	string varName;
	varName = scan.get_identifier();
	scan.next_symbol();

	// The line should be emty after the var Name!
	if (!scan.has_symbol()) return varName;
	else				    return "";
}

std::string JavaVariable::GetSaveLine() const
{
	if (m_type == nullptr) return "";

	return m_type->GetName() + " " + m_name + "\n";
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
