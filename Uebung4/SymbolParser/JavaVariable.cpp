/*****************************************************************//**
 * \file   JavaVariable.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

//
//	INCLDUES
// 
#include "JavaVariable.hpp"
#include <sstream>
#include <string>
#include "scanner.h"

using namespace pfc;
using namespace std;

std::string ScanTypeName(scanner& scan)
{
	string typeName = scan.get_identifier();
	scan.next_symbol();
	return typeName;
}
std::string ScanVarName(scanner& scan)
{
	string varName;
	varName = scan.get_identifier();
	
	if (!varName.empty())
	{
		scan.next_symbol();
		if (!scan.is(';'))
		{
			varName = "";
		}
	}

	return varName;
}

std::string JavaVariable::Save()
{
	stringstream line;

	line << m_type << " " << m_name << ";";

	return line.str();
}

std::string JavaVariable::LoadVarName(std::string const& fileLine)
{
	stringstream lineStream;
	lineStream << fileLine;
	scanner scan{lineStream};
	
	return ScanTypeName(scan);
}

std::string JavaVariable::LoadTypeName(std::string const& fileLine)
{
	stringstream lineStream;
	lineStream << fileLine;
	scanner scan{ lineStream };

	string typeName = ScanTypeName(scan);
	string varName = ScanVarName(scan);
	if (typeName.empty()) varName = "";
	
	return varName;
}
