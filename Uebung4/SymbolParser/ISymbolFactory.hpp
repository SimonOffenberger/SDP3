/*****************************************************************//**
 * \file   ISymbolFactory.hpp
 * \brief  A Interface for creating SymbolFactories
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/
#ifndef ISYMBOL_FACTORY_HPP
#define ISYMBOL_FACTORY_HPP

#include "Variable.hpp"
#include "Type.hpp"

class ISymbolFactory
{
public:
	/**
	 * \brief Creates a variable
	 *
	 * \param string of variables name
	 * \return uniqie pointer to variable
	 */
	virtual Variable::Uptr CreateVariable(const std::string& name)=0;
	
	/**
	 * \brief Creates a type
	 *
	 * \param string of typename
	 * \return unique pointer to type
	 */
	virtual Type::Uptr CreateType(const std::string& name)=0;

	/**
	 * \brief Getter for file path of type file
	 *
	 * \return string of filePath
	 */
	virtual const std::string& GetTypeFileName()=0;

	/**
	 * \brief Getter for file path of variable file
	 *
	 * \return string of filePath
	 */
	virtual const std::string& GetVariableFileName()=0;



	virtual ~ISymbolFactory() = default;

protected:
private:
};
#endif