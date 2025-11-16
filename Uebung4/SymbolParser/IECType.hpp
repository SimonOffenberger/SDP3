/*****************************************************************//**
 * \file   IECType.hpp
 * \brief  A Class for parsing IEC types
 * \author Simon 
 * \date   Dezember 2025
 *********************************************************************/

#ifndef IEC_TYPE_HPP
#define IEC_TYPE_HPP
#include "Object.h"
#include "Type.hpp"

class IECType: public Type
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

	/**
	 * \brief Constructs a Type with a specified name.
	 * 
	 * \param name
	 */
	IECType(const std::string & name) : Type{ name } {}

	IECType() = default;

protected:
private:
};
#endif