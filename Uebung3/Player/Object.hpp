#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object {
public: 

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";
	inline static const std::string ERROR_NULLPTR = "ERROR: Passed in Nullptr!";

protected:
	Object() = default;

	virtual ~Object() = default;

};

#endif // !OBJECT_HPP
