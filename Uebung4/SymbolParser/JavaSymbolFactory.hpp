/*****************************************************************//**
 * \file   JavaSymbolFactory.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef JAVA_SYMBOL_FACTORY_HPP
#define JAVA_SYMBOL_FACTORY_HPP
#include "Object.h"
#include "ISymbolFactory.hpp"

class JavaSymbolFactory :public ISymbolFactory , public Object
{
public:

	virtual Variable::Uptr CreateVariable(const std::string& name) override;

	virtual Type::Uptr CreateType(const std::string& name) override;

	virtual const std::string& GetTypeFileName() override;

	virtual const std::string& GetVariableFileName() override;

protected:
private:
	const std::string m_TypeFileName = "IEC_Type.txt";
	const std::string m_VariableFileName = "IEC_Variable.txt";
};
#endif