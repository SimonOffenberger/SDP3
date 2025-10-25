/*****************************************************************//**
 * \file   main.cpp
 * \brief  Testdriver for the Company
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "Company.hpp"
#include "Employee.hpp"
#include "HourlyWorker.hpp"
#include "vld.h"
#include "Client.hpp"
#include "Test.hpp"
#include "ComissionWorker.hpp"
#include "HourlyWorker.hpp"
#include "Boss.hpp"
#include "PieceWorker.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
using namespace std::chrono;

static bool TestEmployeeBoss(std::ostream& ost);
static bool TestEmployeeHourlyWorker(std::ostream& ost);
static bool TestEmployeePieceWorker(std::ostream& ost);
static bool TestEmployeeComissionWorker(std::ostream& ost);
static bool TestCompanyAdd(std::ostream& ost);

#define WRITE_OUTPUT true

int main(void){
	bool TestOK = true;
	ofstream testoutput;
	try {

		if (WRITE_OUTPUT == true) {
			testoutput.open("TestOutput.txt");
		}

		Company comp{ "Offenberger Devices" };
		Client TestClient;
		ComissionWorker* cWork = new ComissionWorker{ "Simon 1", "Si1", { 2022y,November,23d }, { 2000y,November,22d }, "4711", 2500, 25, 2500 };
		ComissionWorker* cWork2 = new ComissionWorker{ "Simon 6", "Si6", { 2022y,November,23d }, { 2000y,November,22d }, "4711", 2500, 25, 200 };
		HourlyWorker* hWork = new HourlyWorker{ "Simon 2", "Si2", { 2022y,November,23d }, { 1934y,November,23d },"4712",20,25 };
		Boss* boss = new Boss{ "Simon 3", "Si3", { 2000y,November,23d }, { 1950y,November,23d },"4712",35000 };
		PieceWorker* pWork = new PieceWorker{ "Simon 4", "Si4", { 2022y,November,23d }, { 2010y,November,23d },"4712",25,25 };
		PieceWorker* pWork2 = new PieceWorker{ "Simon 5", "Si5", { 2022y,November,23d }, { 2011y,November,23d },"4712",25,25 };

		comp.AddEmployee(cWork);
		comp.AddEmployee(cWork2);
		comp.AddEmployee(hWork);
		comp.AddEmployee(boss);
		comp.AddEmployee(pWork);
		comp.AddEmployee(pWork2);

		TestOK = TestOK && TestClient.TestCompanyGetter(cout, comp);
		if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyGetter(testoutput, comp);

		// Copy Ctor Call !
		Company compCopy = comp;

		TestOK = TestOK && TestClient.TestCompanyCopyCTOR(cout, comp, compCopy);
		if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyCopyCTOR(testoutput, comp, compCopy);

		// Test Assign Operator
		Company compAss{ "Assign Company" };
		compAss = comp;

		TestOK = TestOK && TestClient.TestCompanyAssignOp(cout, comp, compAss);
		if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyAssignOp(testoutput, comp, compAss);


		TestOK = TestOK && TestClient.TestCompanyPrint(cout, comp);
		if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyPrint(testoutput, comp);

		Company emptyComp{ "empty" };

		TestOK = TestOK && TestClient.TestEmptyCompanyGetter(cout, emptyComp);
		if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmptyCompanyGetter(testoutput, emptyComp);

		// Test Boss
		TestOK = TestOK && TestEmployeeBoss(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestEmployeeBoss(testoutput);

		// Test Hourly Worker
		TestOK = TestOK && TestEmployeeHourlyWorker(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestEmployeeHourlyWorker(testoutput);

		// Test Piece Worker
		TestOK = TestOK && TestEmployeePieceWorker(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestEmployeePieceWorker(testoutput);

		// Test Comission Worker
		TestOK = TestOK && TestEmployeeComissionWorker(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestEmployeeComissionWorker(testoutput);

		// Test Company Add
		TestOK = TestOK && TestCompanyAdd(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestCompanyAdd(testoutput);

		if (WRITE_OUTPUT) {
			if (TestOK) TestCaseOK(testoutput);
			else TestCaseFail(testoutput);

			testoutput.close();
		}

		if (TestOK) TestCaseOK(cout);
		else TestCaseFail(cout);
	}
	catch (const string& err) {
		cout << err;
	}
	catch (bad_alloc const& error) {
		cout << error.what();
	}
	catch (const exception& err) {
		cout  << err.what();
	}
	catch (...) {
		cout << "Unhandelt Exception";
	}



}



static bool TestEmployeeBoss(std::ostream& ost)
{

	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t testSalary = 7800;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };

		TestOK = TestOK && check_dump(ost, "Test - Boss.GetSalary()", testSalary, testBoss.GetSalary());
		TestOK = TestOK && check_dump(ost, "Test - Boss.GetSoldItems()", static_cast<size_t>(0), testBoss.GetSoldItems());
		TestOK = TestOK && check_dump(ost, "Test - Boss.GetProducedItems()", static_cast<size_t>(0), testBoss.GetProducedItems());
		TestOK = TestOK && check_dump(ost, "Test - Boss.GetWorkerType()", E_Boss, testBoss.GetWorkerType());
		TestOK = TestOK && check_dump(ost, "Test - Boss.GetDateBirth()", dateBorn, testBoss.GetDateBirth());
		TestOK = TestOK && check_dump(ost, "Test - Boss.GetDateJoined()", dateJoined, testBoss.GetDateJoined());
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//clone test
	try {
		size_t testSalary = 7800;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };
		Employee* pEmp = testBoss.Clone();
		TestOK = TestOK && check_dump(ost, "Test Boss.Clone()", pEmp != nullptr && pEmp != &testBoss, true);
		delete pEmp;
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Unavialable ID
	try {
		size_t testSalary = 7800;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAXL";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };
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

	TestOK = TestOK && check_dump(ost, "Boss Constructor bad ID", error_msg, Employee::ERROR_BAD_ID);
	error_msg.clear();

	// Constructor bad SV
	try {
		size_t testSalary = 7800;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };
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

	TestOK = TestOK && check_dump(ost, "Boss Constructor bad SV - invalid character", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);

	error_msg.clear();


	// Constructor bad SV - too many nums
	try {
		size_t testSalary = 7800;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };
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

	TestOK = TestOK && check_dump(ost, "Boss Constructor bad SV - too many nums", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);
	error_msg.clear();

	// Bad ostream
	try {
		size_t testSalary = 7800;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary };
		std::stringstream out_stream;
		out_stream.setstate(ios::badbit);
		testBoss.PrintDatasheet(out_stream);
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

	TestOK = TestOK && check_dump(ost, "Boss bad ostream", error_msg, Object::ERROR_BAD_OSTREAM);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}

static bool TestEmployeeHourlyWorker(std::ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };

		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetSalary()", hourlyRate * workedHours, testHourlyWorker.GetSalary());
		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetSoldItems()", static_cast<size_t>(0), testHourlyWorker.GetSoldItems());
		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetProducedItems()", static_cast<size_t>(0), testHourlyWorker.GetProducedItems());
		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetWorkerType()", E_HourlyWorker, testHourlyWorker.GetWorkerType());
		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetDateBirth()", dateBorn, testHourlyWorker.GetDateBirth());
		TestOK = TestOK && check_dump(ost, "Test - HourlyWorker.GetDateJoined()", dateJoined, testHourlyWorker.GetDateJoined());
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//clone test
	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };

		Employee* pEmp = testHourlyWorker.Clone();
		TestOK = TestOK && check_dump(ost, "Test testPieceWorker.Clone()", pEmp != nullptr && pEmp != &testHourlyWorker, true);
		delete pEmp;
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Unavialable ID
	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAXL";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };
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

	TestOK = TestOK && check_dump(ost, "HourlyWorker Constructor bad ID", error_msg, Employee::ERROR_BAD_ID);
	error_msg.clear();

	// Constructor bad SV
	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };
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

	TestOK = TestOK && check_dump(ost, "HourlyWorker Constructor bad SV - invalid character", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);

	error_msg.clear();

	// Constructor bad SV - too many nums
	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };
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

	TestOK = TestOK && check_dump(ost, "HourlyWorker Constructor bad SV - too many nums", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);
	error_msg.clear();

	// Bad ostream
	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		HourlyWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, hourlyRate, workedHours };
		std::stringstream out_stream;
		out_stream.setstate(ios::badbit);
		testHourlyWorker.PrintDatasheet(out_stream);
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

	TestOK = TestOK && check_dump(ost, "HourlyWorker bad ostream", error_msg, Object::ERROR_BAD_OSTREAM);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}

static bool TestEmployeePieceWorker(std::ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		PieceWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };

		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetSalary()", piecesProduced * comissionPerPiece, testHourlyWorker.GetSalary());
		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetSoldItems()", static_cast<size_t>(0), testHourlyWorker.GetSoldItems());
		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetProducedItems()", piecesProduced, testHourlyWorker.GetProducedItems());
		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetWorkerType()", E_PieceWorker, testHourlyWorker.GetWorkerType());
		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetDateBirth()", dateBorn, testHourlyWorker.GetDateBirth());
		TestOK = TestOK && check_dump(ost, "Test - PieceWorker.GetDateJoined()", dateJoined, testHourlyWorker.GetDateJoined());
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//clone test
	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		PieceWorker testPieceWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };
		Employee* pEmp = testPieceWorker.Clone();
		TestOK = TestOK && check_dump(ost, "Test testPieceWorker.Clone()", pEmp != nullptr && pEmp != &testPieceWorker, true);
		delete pEmp;
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Unavialable ID
	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAXL";

		PieceWorker testPieceWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };
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

	TestOK = TestOK && check_dump(ost, "PieceWorker Constructor bad ID", error_msg, Employee::ERROR_BAD_ID);
	error_msg.clear();

	// Constructor bad SV
	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		PieceWorker testPieceWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };
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

	TestOK = TestOK && check_dump(ost, "PieceWorker Constructor bad SV - invalid character", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);

	error_msg.clear();

	// Constructor bad SV - too many nums
	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		PieceWorker testPieceWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };
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

	TestOK = TestOK && check_dump(ost, "PieceWorker Constructor bad SV - too many nums", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);
	error_msg.clear();

	// Bad ostream
	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		PieceWorker testPieceWorker{ name, id, dateJoined, dateBorn, svr, piecesProduced, comissionPerPiece };
		std::stringstream out_stream;
		out_stream.setstate(ios::badbit);
		testPieceWorker.PrintDatasheet(out_stream);
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

	TestOK = TestOK && check_dump(ost, "PieceWorker bad ostream", error_msg, Object::ERROR_BAD_OSTREAM);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}

static bool TestEmployeeComissionWorker(std::ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		ComissionWorker testHourlyWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };

		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetSalary()", baseSalary + piecesSold * comissionPerPiece, testHourlyWorker.GetSalary());
		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetSoldItems()", piecesSold, testHourlyWorker.GetSoldItems());
		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetProducedItems()", static_cast<size_t>(0), testHourlyWorker.GetProducedItems());
		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetWorkerType()", E_CommisionWorker, testHourlyWorker.GetWorkerType());
		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetDateBirth()", dateBorn, testHourlyWorker.GetDateBirth());
		TestOK = TestOK && check_dump(ost, "Test - ComissionWorker.GetDateJoined()", dateJoined, testHourlyWorker.GetDateJoined());
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	//clone test
	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		ComissionWorker testComissionWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };
		Employee* pEmp = testComissionWorker.Clone();
		TestOK = TestOK && check_dump(ost, "Test testPieceWorker.Clone()", pEmp != nullptr && pEmp != &testComissionWorker, true);
		delete pEmp;
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

	TestOK = TestOK && check_dump(ost, "Test - error buffer", error_msg.empty(), true);
	error_msg.clear();

	// Unavialable ID
	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAXL";

		ComissionWorker testComissionWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };
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

	TestOK = TestOK && check_dump(ost, "ComissionWorker Constructor bad ID ", error_msg, Employee::ERROR_BAD_ID);
	error_msg.clear();

	// Constructor bad SV - no numbers
	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "ARGH";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		ComissionWorker testComissionWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };
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

	TestOK = TestOK && check_dump(ost, "ComissionWorker Constructor bad SV - invalid character", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);

	error_msg.clear();

	// Constructor bad SV - too many nums
	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "47488888239874";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		ComissionWorker testComissionWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };
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

	TestOK = TestOK && check_dump(ost, "ComissionWorker Constructor bad SV - too many nums", Employee::ERROR_BAD_SOZIAL_SEC_NUM, error_msg);
	error_msg.clear();

	// Bad ostream
	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "4711";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		ComissionWorker testComissionWorker{ name, id, dateJoined, dateBorn, svr, baseSalary, comissionPerPiece, piecesSold };
		std::stringstream out_stream;
		out_stream.setstate(ios::badbit);
		testComissionWorker.PrintDatasheet(out_stream);
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

	TestOK = TestOK && check_dump(ost, "ComissionWorker bad ostream", error_msg, Object::ERROR_BAD_OSTREAM);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}


static bool TestCompanyAdd(std::ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		ComissionWorker* cWork = new ComissionWorker{ "Simon 1", "Si1", { 2022y,November,23d }, { 2000y,November,22d }, "4711", 2500, 25, 2500 };

		Company comp{"Dup"};
		comp.AddEmployee(cWork);
		comp.AddEmployee(cWork);
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

	TestOK = TestOK && check_dump(ost, "Test Exception in Company Add Duplicate", Company::ERROR_DUPLICATE_EMPL, error_msg);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}