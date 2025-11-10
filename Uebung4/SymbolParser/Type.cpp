
#include "Type.hpp"


std::string Type::GetType() const{
	return m_name;
}

void Type::SetType(const std::string& name)
{
	if (name.empty()) throw Type::ERROR_EMPTY_STRING;

	m_name = name;
}
