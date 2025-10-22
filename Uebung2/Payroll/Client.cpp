/*****************************************************************//**
 * \file   Client.hpp
 * \brief  Client Class that uses the Class Company via the Interface IComp
 *
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/

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

		TestOK = TestOK && check_dump(ost, "Test Company Get Comission Worker Cnt & Add Empl",  static_cast<size_t>(2), company.GetWorkerCount(TWorker::E_CommisionWorker));
		TestOK = TestOK && check_dump(ost, "Test Company Get Houerly Worker Cnt & Add Empl",	static_cast<size_t>(1), company.GetWorkerCount(TWorker::E_HourlyWorker));
		TestOK = TestOK && check_dump(ost, "Test Company Get Boss Cnt & Add Empl",				static_cast<size_t>(1), company.GetWorkerCount(TWorker::E_Boss));
		TestOK = TestOK && check_dump(ost, "Test Company Get Piece Worker Cnt & Add Empl",		static_cast<size_t>(2), company.GetWorkerCount(TWorker::E_PieceWorker));

		
		TestOK = TestOK && check_dump(ost, "Test Company FindWorker by ID",			static_cast<std::string>("Si1"), company.FindWorkerByID("Si1")->GetID());
		TestOK = TestOK && check_dump(ost, "Test Company FindWorker by empty ID",   static_cast<const Employee *>(nullptr), company.FindWorkerByID(""));

		TestOK = TestOK && check_dump(ost, "Test Company Get Size",					static_cast<size_t>(6), company.GetCompanySize());

		TestOK = TestOK && check_dump(ost, "Test Company Get Count worker bevor 1930 date", static_cast<size_t>(0), company.GetCountWorkerBeforDate({ 1930y,November,23d }));
		TestOK = TestOK && check_dump(ost, "Test Company Get Count worker bevor 1951 date", static_cast<size_t>(2), company.GetCountWorkerBeforDate({ 1951y,November,23d }));

		TestOK = TestOK && check_dump(ost, "Test Company Get longest serving employee", TWorker::E_Boss, company.GetLongestServing()->GetWorkerType());

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

