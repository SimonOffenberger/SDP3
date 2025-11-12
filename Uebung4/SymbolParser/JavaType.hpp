/*****************************************************************//**
 * \file   JavaType.hpp
 * \brief  A Class for parsing java types
 * \author Simon
 * \date   Dezember 2025
 *********************************************************************/

#ifndef JAVA_TYPE_HPP
#define JAVA_TYPE_HPP

#include "Type.hpp"
#include <string>

class JavaType : public Type
{
public:
	/**
	 * \brief Loads a types name from a files line
	 *
	 * \param string fileLine
	 * \return string of type
	 */
	virtual std::string LoadTypeName(const std::string& fileLine) const override;

	/**
	 * \brief Returns formatted line of a types declaration
	 *
	 * \return string of type declaration
	 */
	virtual std::string GetSaveLine() const override;

	JavaType(const std::string name) : Type{ name } {}

	JavaType() = default;

protected:
private:
};
#endif