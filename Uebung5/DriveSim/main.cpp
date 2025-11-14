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
    RPM_Sensor::Sptr rpm_sens = make_shared<RPM_Sensor>("Hello");
    Car TestCar{ 600,rpm_sens };
    Tachometer::Sptr tacho = make_shared<Tachometer>(TestCar);
    Odometer::Sptr odo = make_shared<Odometer>(TestCar);
    TestCar.Attach(tacho);
    TestCar.Attach(odo);
    

   //Erzeugen der Objekte
   WindowsDisplay::SPtr digDisp = make_shared<DigitalDisplay>();
   WindowsDisplay::SPtr anaDisp = make_shared<AnalogDisplay>();

	//send values to displays
	for (int i = 0; i < 4711; i++) {

        TestCar.Process();

      if (digDisp->SendValue(TestCar.GetCurrentSpeed()))
      {
         cout <<  "digi: " << i * 5 << endl;
      }
      if (anaDisp->SendValue((i * 5) % 220))
      {
         cout << "analog: " << i * 5 << endl;
      }
		Sleep(500);
	}

	return 0;
}

