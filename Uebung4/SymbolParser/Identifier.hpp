/*****************************************************************//**
 * \file   Identifier.hpp
 * \brief  Generalization of Types and Variables
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/
#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <string>
#include "Object.h"

class Identifier : public Object
{
public: 

	inline static const std::string ERROR_EMPTY_STRING = "ERROR: Empty String";

	/**
	 * \brief Getter for  name
	 *
	 * \return string of name
	 */
	std::string GetName() const;

	/**
	 * \brief Sets a  name
	 *
	 * \param string fileLine
	 * \return string of type - SymbolParser has to check type for validity
	 * \throw ERROR_EMPTY_STRING
	 */
	void SetName(const std::string& name);


protected:
	Identifier(const std::string& name) : m_name{ name } {}
	Identifier() = default;

	std::string m_name;
private:
};

#endif