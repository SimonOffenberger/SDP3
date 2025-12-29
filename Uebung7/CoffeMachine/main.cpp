/**
 * @file main.cpp
 * @brief Runs sample preparations and tests for the coffee machine decorators.
 */
#include "vld.h"
#include "Mocha.hpp"
#include "ExtendedOne.hpp"
#include "Decaff.hpp"
#include "Espresso.hpp"
#include "Milk.hpp"
#include "Sugar.hpp"
#include "SojaMilk.hpp"
#include "Cream.hpp"
#include "CoffeePreparation.hpp"
#include "Test.hpp"
#include "CoffeeInfo.hpp"

#include <memory>
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>

using namespace std;

static bool TestCoffeeIngridient(std::ostream& ost,ICoffee::Uptr cof, const std::string& description, const double price);
static bool TestCoffeeIngridientException(std::ostream& ost);
static bool TestCoffeePreparation(std::ostream& ost);


#define WriteOutputFile  true

int main()
{	
	bool TestOK = true;
	ofstream output{ "Testoutput.txt" };

	if (!output.is_open()) {
		cerr << "Konnte Testoutput.txt nicht oeffnen" << TestCaseFail;
		return 1;
	}

	try {

		cout << TestStart;
		cout << "Test Espresso" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Espresso>(), CoffeeInfo::mEspressoInfo + ":", CoffeeInfo::mEspressoPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Mocha" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Mocha>(), CoffeeInfo::mMochaInfo + ":", CoffeeInfo::mMochaPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Decaff" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Decaff>(), CoffeeInfo::mDecaffInfo + ":", CoffeeInfo::mDecaffPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Extended One" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<ExtendedOne>(), CoffeeInfo::mExtendedInfo + ":", CoffeeInfo::mExtendedPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Espresso with Milk" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Milk>(make_unique<Espresso>()),
			CoffeeInfo::mEspressoInfo + ": " + CoffeeInfo::mMilkInfo + ",",
			CoffeeInfo::mEspressoPrice + CoffeeInfo::mMilkPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Extended One with SojaMilk" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<SojaMilk>(make_unique<ExtendedOne>()),
			CoffeeInfo::mExtendedInfo + ": " + CoffeeInfo::mSojaMilkInfo + ",",
			CoffeeInfo::mExtendedPrice + CoffeeInfo::mSojaMilkPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Mocha with Sugar" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Sugar>(make_unique<Mocha>()),
			CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo + ",",
			CoffeeInfo::mMochaPrice + CoffeeInfo::mSugarPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Decaff with Cream" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Cream>(make_unique<Decaff>()),
			CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo + ",",
			CoffeeInfo::mDecaffPrice + CoffeeInfo::mCreamPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Decaff with Cream and Cream" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Cream>(make_unique<Cream>(make_unique<Decaff>())),
			CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo + ", " + CoffeeInfo::mCreamInfo + ",",
			CoffeeInfo::mDecaffPrice + CoffeeInfo::mCreamPrice + CoffeeInfo::mCreamPrice);
		cout << TestEnd;

		cout << TestStart;
		cout << "Test Mocha alla Diabetes" << endl << endl;
		TestCoffeeIngridient(std::cout, make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
			make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
				make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
					make_unique<Mocha>()))))))))),
			CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo + ", "
			+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
			+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
			+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
			+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ",",
			CoffeeInfo::mMochaPrice + CoffeeInfo::mSugarPrice * 9);
		cout << TestEnd;


		TestCoffeePreparation(std::cout);

		TestCoffeeIngridientException(std::cout);


		if (WriteOutputFile) {

			output << TestStart;
			output << "Test Espresso" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Espresso>(), CoffeeInfo::mEspressoInfo + ":", CoffeeInfo::mEspressoPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Mocha" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Mocha>(), CoffeeInfo::mMochaInfo + ":", CoffeeInfo::mMochaPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Decaff" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Decaff>(), CoffeeInfo::mDecaffInfo + ":", CoffeeInfo::mDecaffPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Extended One" << endl << endl;
			TestCoffeeIngridient(output, make_unique<ExtendedOne>(), CoffeeInfo::mExtendedInfo + ":", CoffeeInfo::mExtendedPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Espresso with Milk" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Milk>(make_unique<Espresso>()),
				CoffeeInfo::mEspressoInfo + ": " + CoffeeInfo::mMilkInfo + ",",
				CoffeeInfo::mEspressoPrice + CoffeeInfo::mMilkPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Extended One with SojaMilk" << endl << endl;
			TestCoffeeIngridient(output, make_unique<SojaMilk>(make_unique<ExtendedOne>()),
				CoffeeInfo::mExtendedInfo + ": " + CoffeeInfo::mSojaMilkInfo + ",",
				CoffeeInfo::mExtendedPrice + CoffeeInfo::mSojaMilkPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Mocha with Sugar" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Sugar>(make_unique<Mocha>()),
				CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo + ",",
				CoffeeInfo::mMochaPrice + CoffeeInfo::mSugarPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Decaff with Cream" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Cream>(make_unique<Decaff>()),
				CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo + ",",
				CoffeeInfo::mDecaffPrice + CoffeeInfo::mCreamPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Decaff with Cream and Cream" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Cream>(make_unique<Cream>(make_unique<Decaff>())),
				CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo + ", " + CoffeeInfo::mCreamInfo + ",",
				CoffeeInfo::mDecaffPrice + CoffeeInfo::mCreamPrice + CoffeeInfo::mCreamPrice);
			output << TestEnd;

			output << TestStart;
			output << "Test Mocha alla Diabetes" << endl << endl;
			TestCoffeeIngridient(output, make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
				make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
					make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
						make_unique<Mocha>()))))))))),
				CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo + ", "
				+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
				+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
				+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
				+ CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ",",
				CoffeeInfo::mMochaPrice + CoffeeInfo::mSugarPrice * 9);
			output << TestEnd;


			TestCoffeePreparation(output);

			TestCoffeeIngridientException(output);


			if (TestOK) {
				output << TestCaseOK;
			}
			else {
				output << TestCaseFail;
			}

			output.close();
		}

		if (TestOK) {
			cout << TestCaseOK;
		}
		else {
			cout << TestCaseFail;
		}
	}
	catch (const string& err) {
		cerr << err << TestCaseFail;
	}
	catch (bad_alloc const& error) {
		cerr << error.what() << TestCaseFail;
	}
	catch (const exception& err) {
		cerr << err.what() << TestCaseFail;
	}
	catch (...) {
		cerr << "Unhandelt Exception" << TestCaseFail;
	}

	if (output.is_open()) output.close();

	return 0;


}

bool TestCoffeeIngridient(std::ostream & ost,ICoffee::Uptr cof, const std::string & description, const double price)
{
	assert(cof != nullptr);
	assert(ost.good());

	std::string error_msg;
	bool TestOK = true;

	try {
		TestOK = TestOK && check_dump(ost, "Test ICoffee Description", cof->GetDescription(), description);
		TestOK = TestOK && check_dump(ost, "Test ICoffee Price", cof->GetCost(), price);
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test for Exception in Testcase", true, error_msg.empty());

	return TestOK;
}

bool TestCoffeeIngridientException(std::ostream& ost)
{
	assert(ost.good());

	std::string error_msg;
	bool TestOK = true;

	try {
		ICoffee::Uptr cof = make_unique<Milk>(nullptr);
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test for Exception in Ingedient CTOR", Ingredient::ERROR_NULLPTR, error_msg);

	return TestOK;
}

bool TestCoffeePreparation(std::ostream& ost) {

	assert(ost.good());


	std::string error_msg;
	bool TestOK = true;

	try {
		CoffeePreparation CoffeeMachine;

		CoffeeMachine.Prepare(make_unique<Milk>(make_unique<Espresso>()));
		CoffeeMachine.Prepare(make_unique<SojaMilk>(make_unique<ExtendedOne>()));

		stringstream expected_output;
		stringstream actual_output;


		CoffeeMachine.Display(actual_output);

		expected_output << CoffeeInfo::mEspressoInfo + ": " + CoffeeInfo::mMilkInfo + " " << CoffeeInfo::mEspressoPrice + CoffeeInfo::mMilkPrice << " Euro" << std::endl;
		expected_output << CoffeeInfo::mExtendedInfo + ": " + CoffeeInfo::mSojaMilkInfo + " " << CoffeeInfo::mExtendedPrice + CoffeeInfo::mSojaMilkPrice << " Euro" << std::endl;

		TestOK = TestOK && check_dump(ost, "Test CoffeePreparation Display 1", actual_output.str(), expected_output.str());

		ICoffee::Uptr cof = CoffeeMachine.Finished();

		actual_output.str("");
		expected_output.str("");

		CoffeeMachine.Display(actual_output);

		expected_output << CoffeeInfo::mExtendedInfo + ": " + CoffeeInfo::mSojaMilkInfo + " " << CoffeeInfo::mExtendedPrice + CoffeeInfo::mSojaMilkPrice << " Euro" << std::endl;

		TestOK = TestOK && check_dump(ost, "Test CoffeePreparation Display 2", actual_output.str(), expected_output.str());

		cof = CoffeeMachine.Finished();

	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test for Exception in Testcase", true, error_msg.empty());

	try {

		CoffeePreparation CoffeeMachine;

		stringstream badstream;

		badstream.setstate(ios::badbit);

		CoffeeMachine.Display(badstream);
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception Bad Ostream in CoffeePreparation", CoffeePreparation::ERROR_BAD_OSTREAM, error_msg);

	try {

		CoffeePreparation CoffeeMachine;

		CoffeeMachine.Display(ost);
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception Queue is Empty Display", CoffeePreparation::ERROR_NO_COFFE_IN_MACHINE, error_msg);

	try {

		CoffeePreparation CoffeeMachine;

		CoffeeMachine.Finished();
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception Queue is Empty Finished", CoffeePreparation::ERROR_NO_COFFE_IN_MACHINE, error_msg);


	return TestOK;	
}
