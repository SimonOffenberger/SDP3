/*****************************************************************//**
 * \file   RecordEntry.cpp
 * \brief  
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "RecordEntry.hpp"
using namespace std;


size_t RecordEntry::GetDistance() const
{
	return m_distance;
}

TDate RecordEntry::GetDate() const
{
	return m_date;
}

std::ostream& RecordEntry::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << std::setfill('0') << std::setw(2) << m_date.day() << "."
		<< std::setw(2) << static_cast<unsigned>(m_date.month()) << "."
		<< std::setw(4) << m_date.year() << ":" << std::setfill(' ')
		<< std::setw(6) << m_distance << " km\n";

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}
