/*****************************************************************//**
 * \file   Type.hpp
 * \brief  Abstract class for parsing types
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef TYPE_HPP
#define TYPE_HPP

#include <memory>
#include <string>
#include "Object.h"

class Type : public Object
{
public: 

	inline static const std::string ERROR_EMPTY_STRING = "ERROR: Empty String";

	/**
	 * \brief Unique pointer type for type
	 */
	using Uptr = std::unique_ptr<Type>;
	
	/**
	 * \brief Shared pointer type for type
	 */
	using Sptr = std::shared_ptr<Type>;

	/**
	 * \brief Getter for type name
	 *
	 * \return string of type
	 */
	std::string GetType() const;

	/**
	 * \brief Sets a types name
	 *
	 * \param string fileLine
	 * \return string of type - SymbolParser has to check type for validity
	 */
	void SetType(const std::string& name);

	/**
	 * \brief Loads a types name from a files line
	 *
	 * \param string fileLine
	 * \return string of type
	 */
	virtual std::string LoadTypeName(const std::string& fileLine) const = 0;
	
	/**
	 * \brief Returns formatted line of a types declaration
	 *
	 * \return string of type declaration
	 */
	virtual std::string GetSaveLine() const =0;

	Type(const std::string& name) : m_name{ name } {}
	Type() = default;

protected:
	std::string m_name;
private:
};
#endif