/*****************************************************************//**
 * \file   ISymbolFactory.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef ISYMBOL_FACTORY_HPP
#define ISYMBOL_FACTORY_HPP

#include "Variable.hpp"
#include "Type.hpp"

class ISymbolFactory
{
public:
	virtual Variable::Uptr CreateVariable(const std::string& name)=0;
	
	virtual Type::Uptr CreateType(const std::string& name)=0;

	virtual const std::string& GetTypeFileName()=0;

	virtual const std::string& GetVariableFileName()=0;

protected:
private:
};
#endif