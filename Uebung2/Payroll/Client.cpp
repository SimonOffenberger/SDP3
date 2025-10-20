#include "Client.hpp"
#include "Test.hpp"
#include "ComissionWorker.hpp"
#include "HourlyWorker.hpp"
#include "Boss.hpp"
#include "PieceWorker.hpp"
#include <sstream>
#include <fstream>

using namespace std;
using namespace std::chrono;

bool Client::TestCompanyGetter(std::ostream& ost, IComp & company) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";


	try {

		ComissionWorker* cWork = new ComissionWorker{ "Simon 1", "Si1", { 2022y,November,23d }, { 2000y,November,22d }, "4711221100", 2500, 25, 2500 };
		ComissionWorker* cWork2 = new ComissionWorker{ "Simon 6", "Si6", { 2022y,November,23d }, { 2000y,November,22d }, "4711221100", 2500, 25, 200 };
		HourlyWorker* hWork = new HourlyWorker{ "Simon 2", "Si2", { 2022y,November,23d }, { 1934y,November,23d },"4712231100",20,25};
		Boss* boss = new Boss{ "Simon 3", "Si3", { 2000y,November,23d }, { 1950y,November,23d },"4712231100",35000};
		PieceWorker* pWork= new PieceWorker{ "Simon 4", "Si4", { 2022y,November,23d }, { 2010y,November,23d },"4712231100",25,25};
		PieceWorker* pWork2= new PieceWorker{ "Simon 5", "Si5", { 2022y,November,23d }, { 2011y,November,23d },"4712231100",25,25};

		company.AddEmployee(cWork);
		company.AddEmployee(cWork2);
		company.AddEmployee(hWork);
		company.AddEmployee(boss);
		company.AddEmployee(pWork);
		company.AddEmployee(pWork2);

		TestOK = TestOK && check_dump(ost, "Test Company Get Comission Worker Cnt & Add Empl",  static_cast<size_t>(2), company.GetWorkerCount(TWorker::E_CommisionWorker));
		TestOK = TestOK && check_dump(ost, "Test Company Get Houerly Worker Cnt & Add Empl",	static_cast<size_t>(1), company.GetWorkerCount(TWorker::E_HourlyWorker));
		TestOK = TestOK && check_dump(ost, "Test Company Get Boss Cnt & Add Empl",				static_cast<size_t>(1), company.GetWorkerCount(TWorker::E_Boss));
		TestOK = TestOK && check_dump(ost, "Test Company Get Piece Worker Cnt & Add Empl",		static_cast<size_t>(2), company.GetWorkerCount(TWorker::E_PieceWorker));

		
		TestOK = TestOK && check_dump(ost, "Test Company FindWorker by ID",			static_cast<const Employee *>(cWork), company.FindWorkerByID("Si1"));
		TestOK = TestOK && check_dump(ost, "Test Company FindWorker by empty ID",   static_cast<const Employee *>(nullptr), company.FindWorkerByID(""));

		TestOK = TestOK && check_dump(ost, "Test Company Get Size",					static_cast<size_t>(6), company.GetCompanySize());

		TestOK = TestOK && check_dump(ost, "Test Company Get Count worker bevor 1930 date", static_cast<size_t>(0), company.GetCountWorkerBeforDate({ 1930y,November,23d }));
		TestOK = TestOK && check_dump(ost, "Test Company Get Count worker bevor 1951 date", static_cast<size_t>(2), company.GetCountWorkerBeforDate({ 1951y,November,23d }));

		TestOK = TestOK && check_dump(ost, "Test Company Get longest serving employee", static_cast<const Employee*>(boss), company.GetLongestServing());


		TestOK = TestOK && check_dump(ost, "Test Company Get total pieces produced", static_cast<size_t>(50), company.GetProducedItems());

		TestOK = TestOK && check_dump(ost, "Test Company Get total pieces sold", static_cast<size_t>(2700), company.GetSoldItems());

	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}

bool Client::TestEmptyCompanyGetter(std::ostream& ost, IComp& company) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";


	try {

		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Comission Worker Cnt & Add Empl", static_cast<size_t>(0), company.GetWorkerCount(TWorker::E_CommisionWorker));
		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Houerly Worker Cnt & Add Empl", static_cast<size_t>(0), company.GetWorkerCount(TWorker::E_HourlyWorker));
		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Boss Cnt & Add Empl", static_cast<size_t>(0), company.GetWorkerCount(TWorker::E_Boss));
		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Piece Worker Cnt & Add Empl", static_cast<size_t>(0), company.GetWorkerCount(TWorker::E_PieceWorker));


		TestOK = TestOK && check_dump(ost, "Test Empty Company FindWorker by ID", static_cast<const Employee *>(nullptr), company.FindWorkerByID("Si1"));
		TestOK = TestOK && check_dump(ost, "Test Empty Company FindWorker by ID empty ID", static_cast<const Employee *>(nullptr), company.FindWorkerByID(""));


		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Size", static_cast<size_t>(0), company.GetCompanySize());

		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Count worker bevor 1930 date", static_cast<size_t>(0), company.GetCountWorkerBeforDate({ 1930y,November,23d }));
		TestOK = TestOK && check_dump(ost, "Test Empty Company Get Count worker bevor 1951 date", static_cast<size_t>(0), company.GetCountWorkerBeforDate({ 1951y,November,23d }));

		TestOK = TestOK && check_dump(ost, "Test Empty Company Get longest serving employee", static_cast<const Employee*>(nullptr), company.GetLongestServing());


		TestOK = TestOK && check_dump(ost, "Test Empty Company Get total pieces produced", static_cast<size_t>(0), company.GetProducedItems());

		TestOK = TestOK && check_dump(ost, "Test Empty Company Get total pieces sold", static_cast<size_t>(0), company.GetSoldItems());

	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	try {

		company.AddEmployee(nullptr);
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


	TestOK = TestOK && check_dump(ost, "Test Company Add nullptr", Object::ERROR_NULLPTR, error_msg);

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}

bool Client::TestCompanyCopyCTOR(std::ostream& ost,const IComp& company,const IComp& companyCopy) const
{

	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;
		stringstream expected;

		company.PrintDataSheet(expected);
		companyCopy.PrintDataSheet(result);

		TestOK = TestOK && check_dump(ost, "Test Company Copy Ctor", true ,expected.str() == result.str());

	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;

	return false;
}

bool Client::TestCompanyAssignOp(std::ostream& ost,const IComp& company,const IComp& companyAss) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;
		stringstream expected;

		company.PrintDataSheet(expected);
		companyAss.PrintDataSheet(result);

		TestOK = TestOK && check_dump(ost, "Test Company Assign Operator", true, expected.str() == result.str());

	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;

	return false;
}

bool Client::TestCompanyPrint(std::ostream& ost, const IComp& company) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	fstream badstream;
	badstream.setstate(ios::badbit);

	try {

		company.PrintDataSheet(badstream);

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

	TestOK = TestOK && check_dump(ost, "Test Company Print Exception", Client::ERROR_BAD_OSTREAM, error_msg);

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;

	return false;
}

bool Client::TestEmployeeBoss(std::ostream& ost)
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";
	
	try {
		size_t testSalary = 7800;
		string svr = "4711221100";
		TDate dateBorn = { 2000y,November,22d };
		TDate dateJoined = { 2022y,November,23d };
		string name = "Max Musterman";
		string id = "MAX";

		Boss testBoss{ name, id, dateJoined, dateBorn, svr, testSalary};

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
		string svr = "4711221100";
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
		string svr = "4711221100";
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

	TestEnd(ost);
	return TestOK;
}

bool Client::TestEmployeeHourlyWorker(std::ostream& ost)
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t hourlyRate = 21;
		size_t workedHours = 160;
		string svr = "4711221100";
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
		string svr = "4711221100";
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
		string svr = "4711221100";
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

	TestEnd(ost);
	return TestOK;
}

bool Client::TestEmployeePieceWorker(std::ostream& ost)
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t piecesProduced = 950;
		size_t comissionPerPiece = 2;
		string svr = "4711221100";
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
		string svr = "4711221100";
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
		string svr = "4711221100";
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


	TestEnd(ost);
	return TestOK;
}

bool Client::TestEmployeeComissionWorker(std::ostream& ost)
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {
		size_t baseSalary = 2300;
		size_t piecesSold = 300;
		size_t comissionPerPiece = 2;
		string svr = "4711221100";
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
		string svr = "4711221100";
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
		string svr = "4711221100";
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

	TestOK = TestOK && check_dump(ost, "ComissionWorker Constructor bad ID", error_msg, Employee::ERROR_BAD_ID);
	error_msg.clear();

	TestEnd(ost);
	return TestOK;
}
