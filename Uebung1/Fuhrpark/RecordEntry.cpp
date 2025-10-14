/*****************************************************************//**
 * \file   RecordEntry.cpp
 * \brief  Implementation of a Record Entry
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#include "RecordEntry.hpp"

using namespace std;

/**
* \brief Getter of the distance member of the Record Entry Class.
*
* \return Distance of this Record Entry
*/
size_t RecordEntry::GetDistance() const
{
	return m_distance;
}

/**
* \brief Getter of the data member of the Record Entry Class.
*
* \return Date of this Record Entry
*/
TDate RecordEntry::GetDate() const
{
	return m_date;
}

/**
* \brief Formatted output of this Record Entry on an ostream.
*
* \param ost : Refernce to an ostream where the Entry should be printed at.
* \return Referenced ostream
*/
std::ostream& RecordEntry::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << std::setfill('0')<< right << std::setw(2) << m_date.day() << "."
		<< std::setw(2) << static_cast<unsigned>(m_date.month()) << "."
		<< std::setw(4) << m_date.year() << ":" << std::setfill(' ')
		<< std::setw(6) << m_distance << " km\n";

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}

/**
* \brief less than operater, is used for storing the Entries in a multiset.
*
* \param rh : Righthandside of the less than operator
* \return true:  left hand side is less than the right hand side.
* \return false: left hand side is greather or equal than the right hand side.
*/
bool RecordEntry::operator<(const RecordEntry& rh) const
{
	return m_date < rh.m_date;
}
