#include "Test.hpp"
#include "RecordEntry.hpp"
#include "DriveRecord.hpp"
#include "Car.hpp"

using namespace std;
using namespace chrono;

int main(void){

	Car Audi{ "Audi A3",TFuel::Diesel };
	Audi.SetPlate("SB278FH");
	Audi.AddRecord(RecordEntry{ TDate{2025y,October,10d}, 10 });
	Audi.AddRecord(RecordEntry{ TDate{2025y,October,11d}, 150 });
	Audi.AddRecord(RecordEntry{ TDate{2025y,October,12d}, 1980 });
	Audi.AddRecord(RecordEntry{ TDate{2025y,October,13d}, 150 });
	Audi.Print();

	cout << endl << Audi.GetDriveRecord().Get_Milage();
}
