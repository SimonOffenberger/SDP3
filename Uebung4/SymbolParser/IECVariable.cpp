/*****************************************************************//**
 * \file   IECVariable.cpp
 * \brief  
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

std::string IECVariable::GetSaveLine()
{
	stringstream line;

	line << "VAR " << m_type->GetType() << " : " << m_name << ";";

	return line.str();
}

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


std::string IECVariable::LoadTypeName(std::string const& fileLine)
{
	stringstream converter;
	converter << fileLine;
	scanner Scan;

	Scan.set_istream(converter);

	return ScanTypeName(Scan);
}

std::string IECVariable::LoadVarName(std::string const& fileLine)
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
