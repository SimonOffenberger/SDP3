#include "Variable.hpp"
#include <cassert>


using namespace std;


std::string Variable::GetName() const
{
    return m_name;
}

std::string Variable::GetType() const
{
    return m_type->GetType();
}

void Variable::SetName(const std::string& name)
{
    if (name.empty()) throw Variable::ERROR_EMPTY_STRING;

    m_name = name;
}

