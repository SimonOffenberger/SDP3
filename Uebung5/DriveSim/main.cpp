/*****************************************************************//**
 * \file   main.cpp
 * \brief  Test Driver for the Drive Sim
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/

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

#define WriteOutputFile ON

using namespace std;

static bool TestOdometer(std::ostream & ost = std::cout);
static bool TestTachometer(std::ostream & ost = std::cout);
static bool TestRPMSensor(std::ostream& ost = std::cout);
static bool TestCar(std::ostream& ost = std::cout);

int main() 
{
    bool TestOK = true;

    ofstream output{ "output.txt" };

    try {

        TestOK = TestOK && TestOdometer();
        TestOK = TestOK && TestTachometer();
        TestOK = TestOK && TestRPMSensor();
        TestOK = TestOK && TestCar();


        if (WriteOutputFile) {

            TestOK = TestOK && TestOdometer(output);
            TestOK = TestOK && TestTachometer(output);
            TestOK = TestOK && TestRPMSensor(output);
            TestOK = TestOK && TestCar(output);

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

        RPM_Sensor::Sptr rpm_sens = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr TestCar = make_shared<Car>( 600, rpm_sens );
        Tachometer::Sptr tacho = make_shared<Tachometer>(TestCar,anaDisp);
        Odometer::Sptr odo = make_shared<Odometer>(TestCar, digDisp);
        TestCar->Attach(tacho);
        TestCar->Attach(odo);

	    //send values to displays
	    while(1){

            TestCar->Process();
		    Sleep(Odometer::Update_Intervall);
	    }
    }
    catch (const string& err) {
        cerr << err;
    }
    catch (bad_alloc const& error) {
        cerr << error.what();
    }
    catch (const exception& err) {
        cerr << err.what();
    }
    catch (...) {
        cerr << "Unhandelt Exception";
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
        Odometer::Sptr OdoMeter = make_shared<Odometer>(AudiA3);
        AudiA3->Attach(OdoMeter);
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
        Odometer::Sptr OdoMeter = make_shared<Odometer>(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr Car in Odometer CTOR", Odometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Odometer::Sptr OdoMeter = make_shared<Odometer>(AudiA3, nullptr);
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

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Odometer::Sptr OdoMeter = make_shared<Odometer>(nullptr, nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr in CTOR of Odometer", Odometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Odometer::Sptr OdoMeter = make_shared<Odometer>(AudiA3);
        AudiA3.reset(); // <-- Free Car
        OdoMeter->Update(); // <-- throws exception Car not set
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

    TestOK = TestOK && check_dump(ost, "Test Car nullptr in Update of Odometer", Odometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Odometer::Sptr OdoMeter = make_shared<Odometer>(AudiA3);

        OdoMeter->SetDisplay(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr in Set Display", Odometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_test_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(1000, sen);
        Odometer::Sptr OdoMeter = make_shared<Odometer>(AudiA3);
        AudiA3->Attach(OdoMeter);

        TestOK = TestOK && check_dump(ost, "Test initial Milage of Odomerter", static_cast<size_t>(0), OdoMeter->GetMilage());
        
        AudiA3->Process();

        TestOK = TestOK && check_dump(ost, "Test Milage after one Process of Odomerter", static_cast<size_t>(26), OdoMeter->GetMilage());
        
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
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(AudiA3);
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
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr Car in Tachometer CTOR", Tachometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(AudiA3, nullptr);
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
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(nullptr, nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr in CTOR of Tachometer", Tachometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();


    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(AudiA3);
        AudiA3.reset(); // <-- Free Car
        TachMeter->Update(); // <-- throws exception Car not set
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

    TestOK = TestOK && check_dump(ost, "Test Car nullptr in Update of Tachometer", Tachometer::ERROR_NULLPTR, error_msg);
    error_msg.clear();
    
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr AudiA3 = make_shared<Car>(600, sen);
        Tachometer::Sptr TachMeter = make_shared<Tachometer>(AudiA3);

        TachMeter->SetDisplay(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test nullptr in Set Display", Tachometer::ERROR_NULLPTR, error_msg);
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
        size_t revs = sen->GetRevolutions();
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

    // test invalid Data
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data_invalid1.txt");
        size_t revs = sen->GetRevolutions();
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
    TestOK = TestOK && check_dump(ost, "Test invalid RPM Data (aaaa aaaa)", RPM_Sensor::ERROR_SENSOR_INVALID_DATA_INPUT, error_msg);
    error_msg.clear();


    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data_invalid2.txt");
        size_t revs = sen->GetRevolutions();
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
    TestOK = TestOK && check_dump(ost, "Test invalid RPM Data (-1000)", RPM_Sensor::ERROR_SENSOR_INVALID_DATA_INPUT, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data_invalid3.txt");
        size_t revs = sen->GetRevolutions();
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
    TestOK = TestOK && check_dump(ost, "Test invalid RPM Data (1007ab)", RPM_Sensor::ERROR_SENSOR_INVALID_DATA_INPUT, error_msg);
    error_msg.clear();
    
    
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data_invalid4.txt");
        size_t revs = sen->GetRevolutions();
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
    TestOK = TestOK && check_dump(ost, "Test invalid RPM Data (10.00)", RPM_Sensor::ERROR_SENSOR_INVALID_DATA_INPUT, error_msg);
    error_msg.clear();

    // test file not found
    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("file_not_found.txt");
        size_t revs = sen->GetRevolutions();
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
        size_t revs = sen->GetRevolutions();
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

bool TestCar(std::ostream& ost)
{
    assert(ost.good());
    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try {
        Car c{ 100,nullptr };
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
    TestOK = TestOK && check_dump(ost, "Test Car CTOR with RPM Nullptr", Car::ERROR_NULLPTR,error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");

        Car c{ 0 ,sen };
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
    TestOK = TestOK && check_dump(ost, "Test Car CTOR with 0 Wheel Diameter", Car::ERROR_WHEEL_DIA_0,error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car c{ 100,sen };
        c.Attach(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test Car Attach with nullptr", Car::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car c{ 100,sen };
        c.Detach(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test Car Detach with nullptr", Car::ERROR_NULLPTR, error_msg);
    error_msg.clear();


    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_data.txt");
        Car::Sptr c = make_shared<Car>(100,sen );
        Odometer::Sptr odmeter = make_shared<Odometer>(c);
        c->Detach(odmeter);
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

    TestOK = TestOK && check_dump(ost, "Test Car Detach with non attached observer", true, error_msg.empty());
    error_msg.clear();

    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_test_data.txt");
        Car::Sptr c = make_shared<Car>(100,sen );
        c->Process();
        TestOK = TestOK && check_dump(ost, "Test Car Get Current Speed", static_cast<size_t>(18849), static_cast<size_t>(c->GetCurrentSpeed()));
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

    TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
    error_msg.clear();


    try {
        RPM_Sensor::Sptr sen = make_shared<RPM_Sensor>("rpm_test_data.txt");
        Car::Sptr c = make_shared<Car>(100,sen );
        while(1) c->Process();
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

    TestOK = TestOK && check_dump(ost, "Test Exception End of File in Car Process",RPM_Sensor::ERROR_SENSOR_EOF, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}
