#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object {
public: 

	/**
	 * \brief Constant for Exception Bad Ostream.
	 */
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";

	/**
	 * \brief Constant for Exception Fail Write.
	 */
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";
	
	/**
	 * \brief Constant for Exception Nullprt.
	 */
	inline static const std::string ERROR_NULLPTR = "ERROR: Passed in Nullptr!";

protected:

	/**
	 * \brief protected CTOR -> abstract Object.
	 * 
	 */
	Object() = default;

	/**
	 * \brief virtual DTOR -> once Virtual always virtual.
	 * 
	 */
	virtual ~Object() = default;

};

#endif // !OBJECT_HPP
