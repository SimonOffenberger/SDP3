/*****************************************************************//**
 * \file   DriveRecord.cpp
 * \brief  Implementation of a Drive Record
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#include <numeric>
#include <algorithm>
#include "DriveRecord.hpp"

/**
* \brief Methode for adding a record entry to a collection of drive records.
*
* \param entry : Record to be added to the colletion
*/
void DriveRecord::AddRecord(const RecordEntry& entry)
{
	m_driveRecords.insert(entry);
}

/**
* \brief This methode adds up all the distance of all record entries.
*
* \return the sum of all distances in the collection
*/
size_t DriveRecord::GetMilage() const
{
	// use std accumulet + lambda to calc the total Milage
	return std::accumulate(m_driveRecords.cbegin(), m_driveRecords.cend(), static_cast<size_t>(0),
		[](const size_t val,const RecordEntry& entry) {return val + entry.GetDistance();});
}

/**
* \brief Formatted output of all Record Entry on an ostream.
*
* \param ost : Refernce to an ostream where the Entries should be printed at.
* \return Referenced ostream
*/
std::ostream& DriveRecord::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	std::for_each(m_driveRecords.cbegin(), m_driveRecords.cend(), [&](const RecordEntry& entry) {entry.Print(ost);});
	
	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;
	
	return ost;
}
