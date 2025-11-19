/*****************************************************************//**
 * \file   Object.h
 * \brief  Base Object class for all other classes
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
public:

	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

protected:


   Object(){};
public:
   virtual ~Object(){}
};

#endif // OBJECT_H
