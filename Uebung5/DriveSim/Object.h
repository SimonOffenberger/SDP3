#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
protected:

	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

   Object(){};
public:
   virtual ~Object(){}
};

#endif // OBJECT_H
