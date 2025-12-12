/**
 * @file Object.h
 * @brief Defines a minimal base object with virtual destructor support.
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
public:

protected:

   /**
    * @brief Base constructor for derived objects.
    */
   Object(){};
public:
   /**
    * @brief Virtual destructor to allow safe polymorphic deletion.
    */
   virtual ~Object(){}
};

#endif // OBJECT_H
