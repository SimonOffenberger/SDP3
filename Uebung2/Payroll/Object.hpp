#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object {
protected:

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

	Object() = default;

	virtual ~Object() = default;

};

#endif // !OBJECT_HPP
