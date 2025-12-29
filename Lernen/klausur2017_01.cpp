/*
Aufgabe 1
*/

#include <iostream>

using namespace std;

class A {
public:
	virtual void Print() const {
		cout << x << endl;
	}

private:
	int x = 4711;
};

class B : public A {
public:
	void Print () const override {
		A::Print();
		cout << y << endl;
	}
	
private:
	int y = 4712;
};

int main() {
	A a;
	B b;
	a = b;
	a.Print();
}

/*
1) Das Programm
	a) kann nicht übersetzt werden und liefert einen Fehler.
	b) kann übersetzt werden liefert mindestens eine Warnung.
	c) übersetzt ohne Fehler und ohne Warnung.
	
2) Die Ausgabe des Codes lautet:
	a) 4711
	b) 4712
	c) 4711 und 4712
	e) Es gibt keine Ausgabe, da das Programm nicht ausgeführt werden kann
	f) Das Programm liefert eine leere Ausgabe.
	
3) Ein Problem tritt im Code auf und wie nennt man es?

4) Gib falls notwendig den richtigen Code an.
*/