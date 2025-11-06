#include "Variable.hpp"
#include <cassert>


using namespace std;


const std::string& Variable::GetName() const
{
    return m_name;
}

const std::string& Variable::GetType() const
{
    return m_type->GetType();
}

Variable::Variable(const std::string& name)
{
    assert(!name.empty());

    m_name = name;
}
