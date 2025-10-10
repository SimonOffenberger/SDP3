#include <numeric>
#include <algorithm>
#include "DriveRecord.hpp"

void DriveRecord::AddRecord(const RecordEntry& entry)
{
	m_driveRecords.push_back(entry);
}

size_t DriveRecord::Get_Milage() const
{
	return std::accumulate(m_driveRecords.cbegin(), m_driveRecords.cend(), 0,
		[](const int val,const RecordEntry& entry) {return val + entry.GetDistance();});
}

std::ostream& DriveRecord::Print(std::ostream& ost) const
{
	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	std::for_each(m_driveRecords.cbegin(), m_driveRecords.cend(), [&](const RecordEntry& entry) {entry.Print(ost);});
	
	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;
	
	return ost;
}
