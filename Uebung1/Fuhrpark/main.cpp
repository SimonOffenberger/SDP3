/*****************************************************************//**
 * \file   main.cpp
 * \brief  Testdriver
 * 
 * \author Simon / Simon
 * \date   October 2025
 *********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include "Test.hpp"
#include "RecordEntry.hpp"
#include "DriveRecord.hpp"
#include "Car.hpp"
#include "Bike.hpp"
#include "Truck.hpp"
#include "Garage.hpp"
#include "vld.h"

using namespace std;
using namespace chrono;

static bool Test_RecordEntry(ostream & ost = cout);
static bool Test_DriveRecord(ostream & ost = cout);
static bool Test_Garage(ostream & ost = cout);
static bool Test_Car(ostream & ost = cout);
static bool Test_Bike(ostream & ost = cout);
static bool Test_Truck(ostream & ost = cout);

#define WriteOutputFile true

int main(void){
	bool Test_OK = true;

	Test_OK = Test_OK && Test_RecordEntry(cout);
	Test_OK = Test_OK && Test_DriveRecord(cout);
	Test_OK = Test_OK && Test_Garage(cout);
	Test_OK = Test_OK && Test_Car(cout);
	Test_OK = Test_OK && Test_Bike(cout);
	Test_OK = Test_OK && Test_Truck(cout);

	if (Test_OK) TestCaseOK(cout);
	else TestCaseFail(cout);
	

	if (WriteOutputFile) {

		ofstream test_output;
		test_output.open("TestOutput.txt");

		Test_OK = Test_OK && Test_RecordEntry(test_output);
		Test_OK = Test_OK && Test_DriveRecord(test_output);
		Test_OK = Test_OK && Test_Garage(test_output);
		Test_OK = Test_OK && Test_Car(test_output);
		Test_OK = Test_OK && Test_Bike(test_output);
		Test_OK = Test_OK && Test_Truck(test_output);

		if (Test_OK) TestCaseOK(test_output);
		else TestCaseFail(test_output);

		test_output.close();
	}
}

bool Test_RecordEntry(ostream& ost)
{
	bool Test_OK = true;
	string error_msg;

	ost << TestStart;
	const TDate date{ 2025y,October,13d };
	const size_t distance = 150;

	RecordEntry entry1{ date, distance };

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry Get Date", date,entry1.GetDate());

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry Get Distance", distance,entry1.GetDistance());

	stringstream result;
	string expected = "13.10.2025:   150 km\n";
	entry1.Print(result);

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry Print", true, result.str() == expected);

	ofstream badstream;
	badstream.setstate(ios::badbit);

	try {
		RecordEntry entry{ TDate{2025y,October,13d}, 150 };
		entry.Print(badstream);
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

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry Exception Bad Ostream", Object::ERROR_BAD_OSTREAM, error_msg);
	
	badstream.close();


	RecordEntry entrygreater{ {2025y,October,8d},10 };
	RecordEntry entryless{ {2025y,October,6d},6 };

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry less than operator", true, entryless<entrygreater);

	try {
		RecordEntry entry{ TDate{2025y,October,13d}, 0 };
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

	Test_OK = Test_OK && check_dump(ost, "Test RecordEntry Exceotion Distance = 0", RecordEntry::ERROR_DISTANCE_ZERO, error_msg);


	ost << TestEnd;

	return Test_OK;
}

bool Test_DriveRecord(ostream& ost)
{
	bool Test_OK = true;
	string error_msg;

	ost << TestStart;
	const TDate date{ 2025y,October,13d };
	const TDate date1{ 2025y,October,10d };
	const TDate date2{ 2025y,October,5d };
	const size_t distance = 150;
	const size_t distance1 = 150;
	const size_t distance2 = 150;

	RecordEntry entry{ date,distance };
	RecordEntry entry1{ date1,distance1 };
	RecordEntry entry2{ date2,distance2 };

	DriveRecord dRecord;

	dRecord.AddRecord(entry);
	dRecord.AddRecord(entry1);
	dRecord.AddRecord(entry2);

	stringstream result;
	stringstream expected;
	dRecord.Print(result);

	entry2.Print(expected);
	entry1.Print(expected);
	entry.Print(expected);

	Test_OK = Test_OK && check_dump(ost, "Test DriveRecord Print Sorted and Add Record", true, result.str() == expected.str());

	const size_t total_milage = 450;

	Test_OK = Test_OK && check_dump(ost, "Test DriveRecord Get Milage", total_milage, dRecord.GetMilage());

	ofstream badstream;
	badstream.setstate(ios::badbit);

	try {
		DriveRecord dEntry{};
		dEntry.AddRecord(entry);
		dEntry.Print(badstream);
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

	Test_OK = Test_OK && check_dump(ost, "Test DriveRecord Exception Bad Ostream", Object::ERROR_BAD_OSTREAM, error_msg);

	const string NoExc = "No Exception";

	try {
		DriveRecord dEntry{};
		dEntry.Print(result);
		error_msg = NoExc;
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

	Test_OK = Test_OK && check_dump(ost, "Test DriveRecord Empty Print", error_msg, NoExc);

	badstream.close();

	ost << TestEnd;

	return Test_OK;
}

static bool Test_Garage(ostream& ost)
{
	bool Test_OK = true;
	string error_msg;

	ost << TestStart;

	// Testing search plate func
	try
	{
		
		std::string testPlate = "SR770BA";
		Car* testCar = new Car{ "UAZ", Diesel,testPlate };
		testCar->AddRecord({ { 2025y,October,13d }, 25 });

		Garage testGarage;
		testGarage.AddVehicle(testCar);
		testGarage.AddVehicle(new Bike{"Kawasaki Z650RS", Benzin, "SB13KK"});
		testGarage.AddVehicle(new Truck{"Scania", Diesel, "SB132KK"});

		Test_OK = Test_OK &&
			check_dump(
				ost,
				"vehicle plate search",
				(const Vehicle*) testCar,
				testGarage.SearchPlate(testPlate)
			);
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test garage plate search - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Searching invalid plate
	try
	{

		std::string testPlate = "SR770BA";
		Car* testCar = new Car{ "UAZ", Diesel, testPlate };
		testCar->AddRecord({ { 2025y,October,13d }, 25 });

		Garage testGarage;
		testGarage.AddVehicle(testCar);

		Vehicle const* result = testGarage.SearchPlate("NOTREAL");
		Test_OK = Test_OK && check_dump(ost, "Test garage plate search invalid plate", result, (Vehicle const*)nullptr);

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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test garage plate search invalid plate - error buffer", error_msg.empty(), true);
	error_msg.clear();

	try
	{
		std::string testPlate = "SR770BA";
		Car* testCar = new Car{ "UAZ", Diesel, testPlate };
		testCar->AddRecord({ { 2025y,October,13d }, 25 });

		Garage testGarage;
		testGarage.AddVehicle(testCar);

		// testing print
		std::stringstream expectation;
		std::stringstream result;

		testCar->Print(expectation);
		testGarage.Print(result);
		Test_OK = Test_OK && check_dump(ost, "Test Garage Print", expectation.str(), result.str());

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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test garage print - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Empty Garage
	try
	{
		Garage testGarage;
		std::stringstream result;
		testGarage.Print(result);
		Test_OK = Test_OK && check_dump(ost, "Test garage print empty garage ", result.str().empty(), true);
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test garage print empty garage - error buffer", error_msg.empty(), true);
	error_msg.clear();

	try
	{
		std::string testPlate = "SR770BA";
		Car* testCar = new Car{ "UAZ", Diesel, testPlate };
		Car* testCar2 = new Car{"Mercedes", Benzin, "UU1234AB"};

		testCar->AddRecord({ { 2025y,October,13d }, 25 });
		testCar2->AddRecord({ { 2025y,October,13d }, 25 });

		Garage testGarage;
		testGarage.AddVehicle(testCar);
		testGarage.AddVehicle(testCar2);

		testGarage.DeleteVehicle(testGarage.SearchPlate(testPlate));
		Vehicle const * const testPtr = testGarage.SearchPlate(testPlate);

		Test_OK = Test_OK && check_dump(ost, "Test Delete Vehicle", testPtr, (Vehicle const* const) 0);
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test garage print - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//Test Copy and Swap
	try
	{
		std::string testPlate = "SR770BA";
		Car* testCar = new Car{ "UAZ", Diesel, testPlate };
		Car* testCar2 = new Car{ "Mercedes", Benzin, "UU1234AB" };
		Vehicle* const testPtr = nullptr;

		testCar->AddRecord({ { 2025y,October,13d }, 25 });
		testCar2->AddRecord({ { 2025y,October,13d }, 25 });

		Garage testGarage;
		testGarage.AddVehicle(testCar);
		testGarage.AddVehicle(testCar2);

		Garage testGarageCopy = testGarage;
		
		Test_OK = Test_OK && check_dump(ost, "Test Delete Vehicle", testPtr, (Vehicle* const)0);
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test Delete Vehicle - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Test GetTotalDrivenKilometers()
	
	try
	{
		Car* const testCar1 = new Car{ "Madza", Elektro, "WD40AHAH" };
		Car* const testCar2 = new Car{ "MG", Elektro, "DeiMama" };

		testCar1->AddRecord({ { 2025y,October,13d }, 25 });
		testCar1->AddRecord({ { 2025y,October,28d }, 34 });
		testCar2->AddRecord({ { 2025y,September,13d }, 25 });
		testCar2->AddRecord({ { 2025y,March,28d }, 34 });

		size_t expect = testCar1->GetMilage() + testCar2->GetMilage();

		Garage testGarage;
		testGarage.AddVehicle(testCar1);
		testGarage.AddVehicle(testCar2);

		size_t result = testGarage.GetTotalDrivenKilometers();

		Test_OK = Test_OK && check_dump(ost, "TTest GetTotalDrivenKilometers()", expect, result);
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test GetTotalDrivenKilometers() - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//Test ostream operator
	try
	{
		Car* const testCar1 = new Car{ "Madza", Elektro, "WD40AHAH" };

		testCar1->AddRecord({ { 2025y,October,13d }, 25 });
		testCar1->AddRecord({ { 2025y,October,28d }, 34 });
		Garage testGarage;
		testGarage.AddVehicle(testCar1);

		std::stringstream expect;
		std::stringstream result;

		testGarage.Print(expect);
		result << testGarage;

		Test_OK = Test_OK && check_dump(ost, "Test ostream operator", expect.str(), result.str());
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
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "Test ostream operator - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Adding Car as nullptr;
	try
	{
		Car* const testCar1 = nullptr;
		Garage testGarage;
		testGarage.AddVehicle(testCar1);	
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (...) {
		error_msg = "Unhandled exception";
	}

	Test_OK = Test_OK && check_dump(ost, "TestAdding Car as nullptr;", error_msg, Garage::ERROR_NULLPTR);
	error_msg.clear();

	// End of garage testing
	ost << TestEnd;
	return Test_OK;
}


static bool Test_Car(ostream& ost) {
	ost << TestStart;

	bool Test_OK = true;

	Car Audi{ "Audi A3",Diesel,"SB278FH" };

	string expected = "\nFahrzeugart:  PKW\nMarke:        Audi A3\nKennzeichen:  SB278FH\n";
	stringstream result;
	Audi.Print(result);

	Test_OK = Test_OK && check_dump(ost, "Test Car Print without record",true ,expected == result.str());

	return Test_OK;

}
static bool Test_Bike(ostream& ost) {
	return true;
}
static bool Test_Truck(ostream& ost){
	return true;
}
