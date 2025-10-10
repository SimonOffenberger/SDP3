#ifndef OBJECT_HPP  
#define OBJECT_HPP  

#include <iostream>  

class Object {  
public:  

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

   /// @brief Virtual default destructor -> once virtual, always virtual.  
   ///  
   /// It is not necessary to declare another virtual destructor   
   /// in derived classes.  
   virtual ~Object() = default;  

   /// @brief String representation of class Object.  
   /// @returns a string for class Object.  
   ///  
   /// Constructs a string representation of class Object  
   /// and can be overridden in derived classes.  
   virtual std::ostream& Print(std::ostream & ost = std::cout) const = 0;  

protected:  
   /// @brief Protected default constructor that makes the class abstract.  
   Object() = default;  
};  

#endif // !1
