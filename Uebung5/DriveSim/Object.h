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
