
#include <iostream>
/*
Aufgabe 2
a)
	Erstellen Sie zu folgendem Code ein
	UML Klassendiagramm (ohne Methoden) und tragen Sie alle Beziehungen ein.
*/

class A {
public:
	A() { std::cout << "A"; }
	~A() { std::cout << "~A"; }
};

class B : public A {
public:
	B() { std::cout << "B"; }
	~B() { std::cout << "~B"; }
};

class X : public A {
public:
	X() { std::cout << "X"; }
	~X() { std::cout << "~X"; }
};

class C : public B {
public:
	C() { std::cout << "C"; }
	~C() { std::cout << "~C"; }
};

class D : public B {
public:
	D() { std::cout << "D"; }
	~D() { std::cout << "~D"; }
	X x;
};

class Y : public X {
public:
	Y() {
		mpD = new D();
		std::cout << "Y";
	}
	virtual ~Y() {
		delete mpD;
		std::cout << "~Y";
	}

private:
	D* mpD;
};

class Z : public Y {
public:
	Z() { std::cout << "Z"; }
	~Z() { std::cout << "~Z"; }
};

/*
2b)
	Es werden folgende Anweisungen abgearbeitet.
	Wie sieht die Ausgabe auf std::cout aus?
*/
int main() {
	D* pD = new D();
	std::cout << "\n";
	Z* pZ = new Z();
	std::cout << "\n";

	delete pD; pD = 0;
	std::cout << "\n";
	delete pZ; pZ = 0;
}
