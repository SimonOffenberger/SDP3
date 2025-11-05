/*****************************************************************//**
 * \file   IECSymbolFactory.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef IEC_SYMBOL_FACTORY_HPP
#define IEC_SYMBOL_FACTORY_HPP
#include "Object.h"
#include "ISymbolFactory.hpp"
#include "SingetonBase.hpp"

class IECSymbolFactory:public ISymbolFactory , public SingletonBase<IECSymbolFactory> , public Object
{
public:

	virtual Variable::Uptr CreateVariable(const std::string& name) override;

	virtual Type::Uptr CreateType(const std::string& name) override;

	virtual const std::string& GetTypeFileName() override;

	virtual const std::string& GetVariableFileName() override;

protected:
private:
	IECSymbolFactory() = default;
	const std::string m_TypeFileName = "IECTypes.sym";
	const std::string m_VariableFileName  =  "IECVars.sym";
};

#endif