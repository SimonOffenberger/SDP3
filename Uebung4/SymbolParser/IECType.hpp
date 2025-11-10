/*****************************************************************//**
 * \file   IECType.hpp
 * \brief  
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef IEC_TYPE_HPP
#define IEC_TYPE_HPP
#include "Object.h"
#include "Type.hpp"

class IECType: public Type
{
public:

	virtual std::string LoadTypeName(const std::string& fileLine) override;

	virtual std::string GetSaveLine() override;

	IECType(const std::string name) : Type{ name } {}

	IECType() = default;

protected:
private:
};
#endif