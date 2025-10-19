#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "IComp.hpp"

class Client {
public:

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

	bool TestCompanyGetter(std::ostream & ost,IComp& company) const;



};

#endif // !CLIENT_HPP
