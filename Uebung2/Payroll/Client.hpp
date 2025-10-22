/*****************************************************************//**
 * \file   Client.hpp
 * \brief  Client Class that uses the Class Company via the Interface IComp
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "IComp.hpp"

class Client {
public:
	/**
	 * Constant for Exception Bad Ostream.
	 */
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: Provided Ostream is bad";
	
	/**
	 * Constant for Exception Write Fail.
	 */
	inline static const std::string ERROR_FAIL_WRITE = "ERROR: Fail to write on provided Ostream";

	/**
	 * \brief Test Methode for the Getter Methodes of the Company via the Interface.
	 * 
	 * \param ost Refernce to an ostream where the Test results should be printed at
	 * \param company Reference to a company interface
	 * \return true -> Test OK
	 * \return false -> Test NOK
	 */
	bool TestCompanyGetter(std::ostream & ost,IComp& company) const;

	/**
	 * \brief Test Methode for the Getter Methodes of an Empty Company via the Interface.
	 *
	 * \param ost Refernce to an ostream where the Test results should be printed at
	 * \param company Reference to a company interface
	 * \return true -> Test OK
	 * \return false -> Test NOK
	 */
	bool TestEmptyCompanyGetter(std::ostream & ost,IComp& company) const;
	
	/**
	 * \brief Test Methode for testing the Copy Ctor of the Company
	 *
	 * \param ost Refernce to an ostream where the Test results should be printed at
	 * \param company Reference to a company interface
	 * \param companyCopy Reference to the copy of company
	 * \return true -> Test OK
	 * \return false -> Test NOK
	 */
	bool TestCompanyCopyCTOR(std::ostream & ost,const IComp& company,const IComp& companyCopy) const;
	
	/**
	 * \brief Test Methode for the Assign Operator of Company
	 *
	 * \param ost Refernce to an ostream where the Test results should be printed at
	 * \param company Reference to a company interface
	 * \param companyAss Reference to the assigned Company should be Equal to company
	 * \return true -> Test OK
	 * \return false -> Test NOK
	 */
	bool TestCompanyAssignOp(std::ostream & ost,const IComp& company,const IComp& companyAss) const;
	
	/**
	 * \brief Test Methode for the Print Methode of Company
	 *
	 * \param ost Refernce to an ostream where the Test results should be printed at
	 * \param company Reference to a company interface
	 * \return true -> Test OK
	 * \return false -> Test NOK
	 */
	bool TestCompanyPrint(std::ostream & ost,const IComp& company) const;

};

#endif // !CLIENT_HPP
	