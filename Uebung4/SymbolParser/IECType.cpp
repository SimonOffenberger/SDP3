/*****************************************************************//**
 * \file   IECType.cpp
 * \brief  A Class for parsing IEC types
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#include "IECType.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include "scanner.h"

using namespace pfc;
using namespace std;

/**
 * \brief Scans an input string for the Type name of the Type.
 * 
 * \param scan Reference to scanner object
 * \return emtpy string if no valid type name is found
 * \return name of type
 */
static std::string ScanTypeName(scanner& scan) {
	try {
		string TypeName;

		if (scan.get_identifier() == "TYPE") {
			scan.next_symbol();
			TypeName = scan.get_identifier();
			scan.next_symbol();
			if (!scan.has_symbol()) {
				return TypeName;
			}
		}
	}
	// catch Scanner Exceptions 
	catch (...) {
		return "";
	}

	return "";
}


std::string IECType::LoadTypeName(const std::string& fileLine) const
{
	stringstream sstream;

	sstream << fileLine;

	scanner scan;

	scan.set_istream(sstream);

	return ScanTypeName(scan);
}


std::string IECType::GetSaveLine() const
{
	return "TYPE " + m_name + "\n";
}
