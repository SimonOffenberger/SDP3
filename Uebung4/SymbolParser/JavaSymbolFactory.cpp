/*****************************************************************//**
 * \file   JavaSymbolFactory.cpp
 * \brief  A factory for parsing java variables and types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/


#include "JavaSymbolFactory.hpp"
#include "JavaType.hpp"
#include "JavaVariable.hpp"


Variable::Uptr JavaSymbolFactory::CreateVariable(const std::string& name)
{
    return std::make_unique<JavaVariable>(JavaVariable{ name });
}

Type::Uptr JavaSymbolFactory::CreateType(const std::string& name)
{
    return std::make_unique<JavaType>(JavaType{name});
}

const std::string& JavaSymbolFactory::GetTypeFileName()
{
    return m_TypeFileName;
}

const std::string& JavaSymbolFactory::GetVariableFileName()
{
    return m_VariableFileName;
}
