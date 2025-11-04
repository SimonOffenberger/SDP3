/*****************************************************************//**
 * \file   Object.hpp
 * \brief  common ancestor for all objects
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object {
public: 

	// Exceptions constants
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";
	inline static const std::string ERROR_NULLPTR = "ERROR: Passed in Nullptr!";

	// once virtual always virtual
	virtual ~Object() = default;


protected:
	Object() = default;
};

#endif // !OBJECT_HPP
