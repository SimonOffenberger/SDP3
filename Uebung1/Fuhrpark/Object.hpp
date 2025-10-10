#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <ostream>

class Object {
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
	virtual std::ostream& Print() const =0;

protected:
	/// @brief Protected default constructor that makes the class abstract.
	Object() = default;
};


#endif // !1
