/*****************************************************************//**
 * \file   JavaType.cpp
 * \brief  A Class for parsing java types
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#include "JavaType.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include "scanner.h"

using namespace pfc;
using namespace std;

static std::string ScanTypeName(scanner& scan) {
	string TypeName;

	if (scan.get_identifier() == "class") {
		scan.next_symbol();
		TypeName = scan.get_identifier();
		scan.next_symbol();
		if (!scan.has_symbol()) {
			return TypeName;
		}
	}

	return "";
}


std::string JavaType::LoadTypeName(const std::string& fileLine) const
{
	stringstream sstream;

	sstream << fileLine;

	scanner scan;

	scan.set_istream(sstream);

	return ScanTypeName(scan);
}

std::string JavaType::GetSaveLine() const
{
	stringstream sstream;

	sstream << "class " << m_name << endl;

	return sstream.str();
}
