#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <string>
#include "Object.hpp"
#include "IComp.hpp"

class Company : public Object, public IComp{
public:




private:

	std::string m_companyName;
};

#endif // !COMPANY_HPP
