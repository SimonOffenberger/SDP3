/*****************************************************************//**
 * \file   Object.hpp
 * \brief  Root of all Objects
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef OBJECT_HPP  
#define OBJECT_HPP  

#include <iostream>  

class Object {  
public:  
	/**
	* Defintions of the Exceptionmessages
	*/
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

   /**
    * Virtual DTOR, once virtual always virtual.
    */
   virtual ~Object() = default;  

protected: 
	/**
	 * \brief protected CTOR -> abstract.
	 */
   Object() = default;  
};  

#endif // !1
