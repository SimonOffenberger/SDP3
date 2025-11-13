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
#include "Identifier.hpp"

class Type : public Identifier
{
public: 

	/**
	 * \brief Unique pointer type for type
	 */
	using Uptr = std::unique_ptr<Type>;
	
	/**
	 * \brief Shared pointer type for type
	 */
	using Sptr = std::shared_ptr<Type>;

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
	virtual std::string GetSaveLine() const = 0;


protected:
	Type(const std::string& name) : Identifier{ name } {}
	Type() = default;
private:
};
#endif