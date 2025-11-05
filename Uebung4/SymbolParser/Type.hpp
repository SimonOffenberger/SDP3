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

#include <memory>
class Type : public Object
{
public: 
	using Uptr = std::unique_ptr<Type>;

protected:
private:
};
#endif