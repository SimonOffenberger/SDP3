#include "Employee.hpp"

std::string Employee::GetID() const
{
    return std::string();
}

size_t Employee::GetProducedItems() const
{
    return size_t();
}

size_t Employee::GetSoldItems() const
{
    return size_t();
}

std::ostream& Employee::PrintDatasheet(std::ostream& ost) const
{
    return ost;
}
