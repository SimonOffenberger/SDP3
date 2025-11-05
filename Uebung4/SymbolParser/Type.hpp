/*****************************************************************//**
 * \file   Type.hpp
 * \brief
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/
#ifndef ITYPE_HPP
#define ITYPE_HPP
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