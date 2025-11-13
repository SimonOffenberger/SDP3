/*****************************************************************//**
 * \file   JavaSymbolFactory.cpp
 * \brief  A factory for creating java variables and types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/
#include "JavaSymbolFactory.hpp"
#include "JavaType.hpp"
#include "JavaVariable.hpp"


Variable::Uptr JavaSymbolFactory::CreateVariable(const std::string& name) const
{
    return std::make_unique<JavaVariable>( name );
}

Type::Uptr JavaSymbolFactory::CreateType(const std::string& name) const
{
    return std::make_unique<JavaType>(name);
}

const std::string& JavaSymbolFactory::GetTypeFileName() const
{
    return m_TypeFileName;
}

const std::string& JavaSymbolFactory::GetVariableFileName() const
{
    return m_VariableFileName;
}
