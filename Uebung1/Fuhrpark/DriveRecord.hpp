#ifndef DRIVE_RECORD_HPP
#define DRIVE_RECORD_HPP

#include <set>
#include "RecordEntry.hpp"
#include "Object.hpp"

using TCont = std::multiset<RecordEntry>;

class DriveRecord : public Object {
public:

	void AddRecord(const RecordEntry & entry);

	size_t Get_Milage() const;

	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

private:

	TCont m_driveRecords;
};


#endif // !1