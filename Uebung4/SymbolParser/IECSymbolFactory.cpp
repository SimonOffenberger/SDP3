/*****************************************************************//**
 * \file   IECSymbolFactory.cpp
 * \brief  A factory for creating IEC variables and types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/

#include "IECSymbolFactory.hpp"
#include "IECType.hpp"
#include "IECVariable.hpp"


Variable::Uptr IECSymbolFactory::CreateVariable(const std::string& name) const
{
    return std::make_unique<IECVariable>(name);
}

Type::Uptr IECSymbolFactory::CreateType(const std::string& name) const
{
    return std::make_unique<IECType>(name);
}

const std::string& IECSymbolFactory::GetTypeFileName() const
{
    return m_TypeFileName;
}

const std::string& IECSymbolFactory::GetVariableFileName() const
{
    return m_VariableFileName;
}
