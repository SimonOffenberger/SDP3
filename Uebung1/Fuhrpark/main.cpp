#include <iostream>
#include <fstream>
#include <sstream>
#include "Test.hpp"
#include "RecordEntry.hpp"
#include "DriveRecord.hpp"
#include "Car.hpp"
#include "Garage.hpp"

using namespace std;
using namespace chrono;

static bool Test_RecordEntry(ostream & ost = cout);
static bool Test_DriveRecord(ostream & ost = cout);
static bool Test_Garage(ostream & ost = cout);

int main(void){
	bool Test_OK = true;

	Test_OK = Test_OK && Test_RecordEntry(cout);
	Test_OK = Test_OK && Test_DriveRecord(cout);
	Test_OK = Test_OK && Test_Garage(cout);

	if (Test_OK) TestCaseOK(cout);
	else TestCaseFail(cout);

	//Car Audi{ "Audi A3",TFuel::Diesel };
	//Audi.SetPlate("SB278FH");
	//Audi.AddRecord(RecordEntry{ TDate{2025y,October,10d}, 10 });
	//Audi.AddRecord(RecordEntry{ TDate{2025y,October,11d}, 150 });
	//Audi.AddRecord(RecordEntry{ TDate{2025y,October,12d}, 1980 });
	//Audi.AddRecord(RecordEntry{ TDate{2025y,October,13d}, 150 });
	//Audi.Print();

	//cout << endl << Audi.Get_Milage();
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
	stringstream result2;
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
	// car must be dynamically allocated in order for delete in ~Garade to work.
	Car* testCar = new Car{ "UAZ", Diesel };
	testCar->SetPlate("SR770BA");
	testCar->AddRecord({ { 2025y,October,13d }, 25 });
	
	Garage testGarage;
	testGarage.AddVehicle(testCar);
	testGarage.Print(ost);

	return true;
}