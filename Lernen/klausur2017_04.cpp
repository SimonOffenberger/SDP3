/*
Aufgabe 4) TicketCounter
Gegeben sei folgender Quellcode, wobei eine gemeinsame Basisklasse (Object) aus Platzgründen
weggelassen wurde. CopyCTor und AssignOp müssen nicht implmenetiert werden!

a) Um welche(s) Design Pattern handelt es sich hier?

Template Methode
Factory Methode

b) Beheben Sie alle Fehler im angegebenen Quellcode. Geben Sie bei der Behebung die 
	entsprechende Klasse, die Zeile und den korrigierten Quellcode der gesammten
	Zeile an. Wird zusätzlicher Code eingefügt, so geben Sie die Klasse und die 
	beiden Codezeilen an zwischen denen Sie den Code einfügen wollen.
*/

size_t const DAY_TICKET = 46;
size_t const SEASON_TICKET = 560;

class Ticket {
public:
	void Print(std::ostream &ost) const {
		ost << "Ticket: ";
		DoPrint(ost);
		ost << "charge: " << mCharge << std::endl;
	}
	
protected:
	Ticket(size_t charge) : mCharge(charge) {}
	void DoPrint(std::ostream &ost) const;
	
private:
	Ticket(Tocket const&) {}
	void operator = (Ticket const &) {}
	size_t mCharge;
};

int main () {
	DayTicketVendor day;
	SeasonTicketVendor season;
	TicketVendor* vendor = &day;
	TicketCounter counter;
	counter.Add(vendor->Create("22.12.2013");
	counter.Add(vendor->Create("22.12.2013");
	vendor = season;
	counter.Add(vendor->Get("Max Mustermann"));
	counter.Add(vendor->Get("Herbert Silberberger"));
	counter.Print(std::cout);
	return 0;
}


// Ausbesserungen
virtual void DoPrint(std::ostream &ost) const = 0;

	counter.Add(vendor->Create(DAY_TICKET));
	counter.Add(vendor->Create(DAY_TICKET));
	vendor = &season;
	counter.Add(vendor->Get(SEASON_TICKET));
	counter.Add(vendor->Get(SEASON_TICKET));

	Ticket(Tocket const&) = delete
	void operator = (Ticket const &) = delete