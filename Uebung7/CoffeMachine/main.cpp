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

using namespace std;

static bool TestCoffeeIngridient(std::ostream& ost,ICoffee::Uptr cof, const std::string& description, const double price);

int main()
{
	ICoffee::Uptr Coff{ std::make_unique<Cream>(std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<Espresso>()))) };

	CoffeePreparation CoffeeMachine;

	CoffeeMachine.Prepare(move(Coff));
	
	CoffeeMachine.Display(std::cout);

	Coff = CoffeeMachine.Finished();

	cout << TestStart;
	cout << "Test Espresso" << endl << endl; 
	TestCoffeeIngridient(std::cout, make_unique<Espresso>(), CoffeeInfo::mEspressoInfo +":", CoffeeInfo::mEspressoPrice);
	cout << TestEnd;

	cout << TestStart;
	cout << "Test Mocha" << endl << endl; 
	TestCoffeeIngridient(std::cout, make_unique<Mocha>(), CoffeeInfo::mMochaInfo +":", CoffeeInfo::mMochaPrice);
	cout << TestEnd;

	cout << TestStart;
	cout << "Test Decaff" << endl << endl; 
	TestCoffeeIngridient(std::cout, make_unique<Decaff>(), CoffeeInfo::mDecaffInfo +":", CoffeeInfo::mDecaffPrice);
	cout << TestEnd;

	cout << TestStart;
	cout << "Test Extended One" << endl << endl; 
	TestCoffeeIngridient(std::cout, make_unique<ExtendedOne>(), CoffeeInfo::mExtendedInfo +":", CoffeeInfo::mExtendedPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Espresso with Milk" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<Milk>(make_unique<Espresso>()),
									CoffeeInfo::mEspressoInfo + ": " + CoffeeInfo::mMilkInfo+",",
									CoffeeInfo::mEspressoPrice+CoffeeInfo::mMilkPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Extended One with SojaMilk" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<SojaMilk>(make_unique<ExtendedOne>()),
									CoffeeInfo::mExtendedInfo + ": " + CoffeeInfo::mSojaMilkInfo+",",
									CoffeeInfo::mExtendedPrice+CoffeeInfo::mSojaMilkPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Mocha with Sugar" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<Sugar>(make_unique<Mocha>()),
									CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo+",",
									CoffeeInfo::mMochaPrice+CoffeeInfo::mSugarPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Decaff with Cream" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<Cream>(make_unique<Decaff>()),
									CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo+",",
									CoffeeInfo::mDecaffPrice+CoffeeInfo::mCreamPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Decaff with Cream and Cream" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<Cream>(make_unique<Cream>(make_unique<Decaff>())),
									CoffeeInfo::mDecaffInfo + ": " + CoffeeInfo::mCreamInfo+", " + CoffeeInfo::mCreamInfo + ",",
									CoffeeInfo::mDecaffPrice+CoffeeInfo::mCreamPrice+ CoffeeInfo::mCreamPrice);
	cout << TestEnd;
	
	cout << TestStart;
	cout << "Test Mocha alla Diabetes" << endl << endl;
	TestCoffeeIngridient(std::cout, make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
								    make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
								    make_unique<Sugar>(make_unique<Sugar>(make_unique<Sugar>(
								    make_unique<Mocha>()))))))))),
									CoffeeInfo::mMochaInfo + ": " + CoffeeInfo::mSugarInfo+", " 
								  + CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
								  + CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", "
								  + CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ", " 
								  + CoffeeInfo::mSugarInfo + ", " + CoffeeInfo::mSugarInfo + ",",
									CoffeeInfo::mMochaPrice+CoffeeInfo::mSugarPrice*9);
	cout << TestEnd;


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
