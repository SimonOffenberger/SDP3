/*****************************************************************//**
 * \file   IECSymbolFactory.hpp
 * \brief  A factory for creating IEC variables and types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/
#ifndef IEC_SYMBOL_FACTORY_HPP
#define IEC_SYMBOL_FACTORY_HPP

#include "Object.h"
#include "ISymbolFactory.hpp"
#include "SingetonBase.hpp"

class IECSymbolFactory : public ISymbolFactory , public SingletonBase<IECSymbolFactory>
{
public:

	// This class is a Singleton
	friend class SingletonBase<IECSymbolFactory>;

	/**
	 * \brief Creates a IEC variable
	 *
	 * \param string of variables name
	 * \return uniqie pointer to variable
	 */
	virtual Variable::Uptr CreateVariable(const std::string& name) override;

	/**
	 * \brief Creates a IEC type
	 *
	 * \param string of typename
	 * \return unique pointer to type
	 */
	virtual Type::Uptr CreateType(const std::string& name) override;

	/**
	 * \brief Getter for file path of type file
	 *
	 * \return string of filePath
	 */
	virtual const std::string& GetTypeFileName() override;

	/**
	 * \brief Getter for file path of variable file
	 *
	 * \return string of filePath
	 */
	virtual const std::string& GetVariableFileName() override;

	// delete CopyCtor and Assign operator to prevent untestet behaviour
	IECSymbolFactory(IECSymbolFactory& fact) = delete;
	void operator=(IECSymbolFactory fact) = delete;

protected:
private:
	IECSymbolFactory() = default;

	const std::string m_TypeFileName = "IECTypes.sym";
	const std::string m_VariableFileName  =  "IECVars.sym";
};

#endif