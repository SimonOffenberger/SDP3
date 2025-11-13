/*****************************************************************//**
 * \file   JavaSymbolFactory.hpp
 * \brief  A factory for creating java variables and types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/
#ifndef JAVA_SYMBOL_FACTORY_HPP
#define JAVA_SYMBOL_FACTORY_HPP

#include "Object.h"
#include "ISymbolFactory.hpp"
#include "SingetonBase.hpp"

class JavaSymbolFactory :public ISymbolFactory, public SingletonBase<JavaSymbolFactory>
{
public:

	friend class SingletonBase<JavaSymbolFactory>;

	/**
	 * \brief Creates a java variable
	 *
	 * \param string of variables name
	 * \return unique pointer to variable
	 */
	virtual Variable::Uptr CreateVariable(const std::string& name) override;

	/**
	 * \brief Creates a java type
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

protected:
private:
	JavaSymbolFactory() = default;
	const std::string m_TypeFileName = "IECTypes.sym";
	const std::string m_VariableFileName = "IECVars.sym";
};
#endif