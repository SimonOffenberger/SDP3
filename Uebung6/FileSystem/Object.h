/*****************************************************************//**
 * \file   Object.h
 * \brief  Root base class for all objects
 * 
 * \author Simon
 * \date   December 2025
 *********************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
protected:
	/** \brief Prevent direct instantiation */
   Object() = default;
public:
	/** \brief Virtual destructor */
   virtual ~Object(){}
};

#endif // OBJECT_H
