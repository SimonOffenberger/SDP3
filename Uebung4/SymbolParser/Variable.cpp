#include "Variable.hpp"
#include <cassert>

std::string const& Variable::Save()
{
    // TODO: insert return statement here
    return "";
}

Variable::Variable(const std::string& name)
{
    assert(!name.empty());

    m_name = name;
}
