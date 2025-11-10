/*****************************************************************//**
 * \file   IECType.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#include "IECType.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include "scanner.h"

using namespace pfc;
using namespace std;

static std::string ScanTypeName(scanner& scan) {
	string TypeName;

	if (scan.get_identifier() == "TYPE") {
		scan.next_symbol();
		TypeName = scan.get_identifier();
		scan.next_symbol();
		return TypeName;
	}

	return "";
}


std::string IECType::LoadTypeName(const std::string& fileLine)
{
	stringstream sstream;

	sstream << fileLine;

	scanner scan;

	scan.set_istream(sstream);

	return ScanTypeName(scan);
}

std::string IECType::GetSaveLine()
{
	return "TYPE" + m_name + "\n";
}
