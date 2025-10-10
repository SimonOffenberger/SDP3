#ifndef RECORD_ENTRY_HPP
#define RECORD_ENTRY_HPP

#include <chrono>
#include "Object.hpp"

using TDate = std::chrono::year_month_day;

class RecordEntry : public Object {
public:

	RecordEntry(TDate date, size_t distance) : m_date{ date }, m_distance{ distance } {}

	size_t GetDistance() const;
	TDate GetDate() const;

	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

private:
	TDate m_date;
	size_t m_distance;
};


#endif // !1