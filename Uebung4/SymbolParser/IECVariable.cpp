/*****************************************************************//**
 * \file   IECVariable.cpp
 * \brief  A Class for parsing IEC variables
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

#include "IECVariable.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include "scanner.h"

using namespace pfc;
using namespace std;

std::string IECVariable::GetSaveLine() const
{
	if (m_type == nullptr) return "";

	return  "VAR " + m_type->GetName() + " : " + m_name + ";\n";
}

/**
 * \brief Scans an input string for the Type name of the Var.
 *
 * \param scan Reference to scanner object
 * \return emtpy string if no valid type name is found
 * \return name of type
 */
static std::string ScanTypeName(scanner & scan) {
	string TypeName;

	if (scan.get_identifier() == "VAR") {
		scan.next_symbol();
		TypeName = scan.get_identifier();
		scan.next_symbol();
		return TypeName;
	}

	return "";
}

/**
 * \brief Scans an input string for the Variable name of the Var.
 *
 * \param scan Reference to scanner object
 * \return emtpy string if no valid Variable name is found
 * \return name of Variable
 */
static std::string ScanVarName(scanner & scan) {
	string VarName;

	if (scan.is(':')) {
		scan.next_symbol();
		VarName = scan.get_identifier();
		scan.next_symbol();
		if (!scan.is(';')) {
			VarName = "";
		}
	}

	return VarName;
}


std::string IECVariable::LoadTypeName(std::string const& fileLine) const
{
	stringstream converter;
	converter << fileLine;
	scanner Scan;

	Scan.set_istream(converter);

	return ScanTypeName(Scan);
}

std::string IECVariable::LoadVarName(std::string const& fileLine) const
{
	stringstream converter;
	converter << fileLine;
	scanner Scan;

	Scan.set_istream(converter);

	string Typename = ScanTypeName(Scan);
	string VarName = ScanVarName(Scan);

	if (Typename.empty()) VarName = "";

	return VarName;
}
