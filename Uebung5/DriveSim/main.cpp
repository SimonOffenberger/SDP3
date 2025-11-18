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

using namespace std;

int main() 
{
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
		Sleep(500);
	}

	return 0;
}

