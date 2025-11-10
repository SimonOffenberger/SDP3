/*****************************************************************//**
 * \file   IECSymbolFactory.cpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#include "IECSymbolFactory.hpp"
#include "IECType.hpp"
#include "IECVariable.hpp"


Variable::Uptr IECSymbolFactory::CreateVariable(const std::string& name)
{
    return std::make_unique<IECVariable>(IECVariable{name});
}

Type::Uptr IECSymbolFactory::CreateType(const std::string& name)
{
    return std::make_unique<IECType>(IECType{name});
}

const std::string& IECSymbolFactory::GetTypeFileName()
{
    return m_TypeFileName;
}

const std::string& IECSymbolFactory::GetVariableFileName()
{
    return m_VariableFileName;
}
