#ifndef OBJECT_HPP  
#define OBJECT_HPP  

#include <iostream>  

class Object {  
public:  

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

   virtual ~Object() = default;  
 
   virtual std::ostream& Print(std::ostream & ost = std::cout) const = 0;  

protected:  
   Object() = default;  
};  

#endif // !1
