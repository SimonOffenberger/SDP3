/*****************************************************************//**
 * \file   JavaType.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef JAVA_TYPE_HPP
#define JAVA_TYPE_HPP
#include "Type.hpp"
#include <string>

class JavaType : public Type
{
public:

	virtual std::string LoadTypeName(const std::string& fileLine) const override;

	virtual std::string GetSaveLine() const override;

	JavaType(const std::string name) : Type{ name } {}

	JavaType() = default;

protected:
private:
};
#endif