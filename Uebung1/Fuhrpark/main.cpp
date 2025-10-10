#include "Test.hpp"
#include "RecordEntry.hpp"
#include "DriveRecord.hpp"

using namespace std;
using namespace chrono;

int main(void){

	RecordEntry entry{ TDate{2025y,October,20d},150 };
	RecordEntry entry1{ TDate{2025y,October,20d},150 };
	RecordEntry entry2{ TDate{2025y,October,20d},150 };

	DriveRecord record;
	record.AddRecord(entry);
	record.AddRecord(entry1);
	record.AddRecord(entry2);

	record.Print();
	cout << record.Get_Milage();

}
