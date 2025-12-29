/*
3) Design Patterns: Sensoren

In einem Softwaresystem werden verschiedene Sensoren abgebildet, um die 
	+ Temperatur (int-Wert), den
	+ Druck (double-Wert) und die
	+ Beschleunigung(double-Wert)
zu messen. Jeder Sensor hat einen eigenen Namen und eine Zugriffsmethode 
die den entsprechenden Wert liefert. Die Sensoren sollen weiters eine Schnittstelle aufweisen,
die _____ verschiedene Operationen auf den Sensoren auzuführen. Die Sensoren implementieren 
_______ -che Operationen nicht! Ein Beispiel dafpr ist ein 'Printer', der die Namen und die 
zugewiesenen Werte sammelt und die Sensoren entsprechend ihrem Namen absteigend bzw. aufsteigend
sortiert ausgegeben kann.

Die Sensoren werden in einer Klasse 'Client' verwaltet, die unter anderem eine Funktion
'Output(std::ostream &ost)' zur Verfügung stellt.

Realisierung:
a) Welche(s) Design Pattern haben Sie gewählt und warum?
b) Erstellen Sie ein Klassendiagramm in UML-Notation mit allen Beziehungen. Geben Sie alle
	Methoden in C++ Notation an!
c) Implentieren Sie die Methode 'Client::Output(...)' und deklarieren Sie die notwendigen
	Variablen der Klasse 'Client' in C++!	
*/

void Client::Output(std::ostream & ost){

	Printer print{true};

	for_each(m_Sensors.begin(),m_Sensors.end(),[&](auto & it){
		it->Accept(print);
	});

	print.Print(ost);

}