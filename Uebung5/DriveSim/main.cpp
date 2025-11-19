/*****************************************************************//**
 * \file   main.cpp
 * \brief  Test Driver for the Drive Sim
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <memory>
#include <windows.h>

//zur Verwendung der analogen und digitalen Anzeige
#include "WindowsDisplay.h"

#include "RPM_Sensor.hpp"
#include "Car.hpp"
#include "Tachometer.hpp"
#include "Odometer.hpp"

#include "Test.hpp"
#include "vld.h"
#include <fstream>
#include <iostream>
#include <cassert>

#include <cstdio>

using namespace std;

#define WriteOutputFile ON

using namespace std;

static bool TestOdometer(std::ostream & ost = std::cout);
static bool TestTachometer(std::ostream & ost = std::cout);
static bool TestRPMSensor(std::ostream& ost = std::cout);


int main() 
{

    bool TestOK = true;

    ofstream output{ "output.txt" };


    try {

        TestOK = TestOK && TestOdometer();
        TestOK = TestOK && TestTachometer();
        TestOK = TestOK && TestRPMSensor();


        if (WriteOutputFile) {

            TestOK = TestOK && TestOdometer(output);
            TestOK = TestOK && TestTachometer(output);
            TestOK = TestOK && TestRPMSensor(output);

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

    try{

        //Erzeugen der Objekte
        WindowsDisplay::SPtr digDisp = make_shared<DigitalDisplay>();
        WindowsDisplay::SPtr anaDisp = make_shared<AnalogDisplay>();

        RPM_Sensor::Sptr rpm_sens = make_shared<RPM_Sensor>("rpm_data_empty.txt");
        Car::Sptr TestCar = make_shared<Car>( 600, rpm_sens );
        Tachometer::Sptr tacho = make_shared<Tachometer>(*TestCar,anaDisp);
        Odometer::Sptr odo = make_shared<Odometer>(*TestCar, digDisp);
        TestCar->Attach(tacho);
        TestCar->Attach(odo);

	    //send values to displays
	    while(1){

            TestCar->Process();
		    Sleep(500);
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


	return 0;
}

bool TestOdometer(std::ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        WindowsDisplay::SPtr digDisp = make_shared<DigitalDisplay>();
        Odometer::Sptr OdMeter = make_shared<Odometer>(*AudiA3,digDisp);
        AudiA3->Attach(OdMeter);
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

    TestOK = TestOK && check_dump(ost, "Test normal operation in Odometer Setup", true, error_msg.empty());
    error_msg.clear();


    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Odometer::Sptr OdMeter = make_shared<Odometer>(*AudiA3, nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test Display nullptr in CTOR of Odometer", Odometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestTachometer(std::ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        WindowsDisplay::SPtr digDisp = make_shared<DigitalDisplay>();
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(*AudiA3, digDisp);
        AudiA3->Attach(TachMeter);
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

    TestOK = TestOK && check_dump(ost, "Test normal operation in Tachometer Setup", true, error_msg.empty());
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(*AudiA3, nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test Display nullptr in CTOR of Tachometer", Tachometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestRPMSensor(std::ostream& ost)
{
    assert(ost.good());
    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    // test normal operation
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        unsigned int revs = sen->GetRevolutions();
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

    // check if exception was thrown
    TestOK = TestOK && check_dump(ost, "Test normal operation in RPM_Sensor", true, error_msg.empty());
    error_msg.clear();

    // test file not found
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("file_not_found.txt");
        unsigned int revs = sen->GetRevolutions();
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

    TestOK = TestOK && check_dump(ost, "Test file not found in RPM_Sensor", RPM_Sensor::ERROR_SENSOR_FILE_NOT_FOUND, error_msg);
    error_msg.clear();

    // check empty file
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data_empty.txt");
        unsigned int revs = sen->GetRevolutions();
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
    TestOK = TestOK && check_dump(ost, "Test empty file in RPM_Sensor", RPM_Sensor::ERROR_SENSOR_INVALID_DATA_INPUT, error_msg);
    error_msg.clear();
    ost << TestEnd;

    return TestOK;
}
