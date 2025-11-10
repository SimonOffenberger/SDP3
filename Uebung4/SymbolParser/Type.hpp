/*****************************************************************//**
 * \file   Type.hpp
 * \brief
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
	using Uptr = std::unique_ptr<Type>;
	using Sptr = std::shared_ptr<Type>;


	inline static const std::string ERROR_EMPTY_STRING = "ERROR: Empty String";

	std::string GetType() const;

	void SetType(const std::string& name);

	virtual std::string LoadTypeName(const std::string& fileLine) = 0;
	
	virtual std::string GetSaveLine()=0;

	Type(const std::string& name) : m_name{ name } {}
	Type() = default;

protected:
	std::string m_name;
private:
};
#endif