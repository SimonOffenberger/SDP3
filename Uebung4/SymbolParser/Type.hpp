/*****************************************************************//**
 * \file   Type.hpp
 * \brief
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef TYPE_HPP
#define TYPE_HPP
#include <memory>
#include "Object.h"

class Type : public Object
{
public: 
	using Uptr = std::unique_ptr<Type>;
	using Sptr = std::shared_ptr<Type>;

	const std::string& GetType() const;

protected:
	std::string m_name;
private:
};
#endif