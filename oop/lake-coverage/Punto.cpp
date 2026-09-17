#include "./Punto.h"
#include <iostream>
#include <cmath>

using namespace std;

// constructor sin parametros
Punto::Punto() {
    x = 0.0;
    y = 0.0;

    E = transformarX(x);
    N = transformarY(y);
}

// constructor con parametros
Punto::Punto(double x, double y) {
    this->x = x;
    this->y = y;

    E = transformarX(x);
    N = transformarY(y);
}

// destructor
Punto::~Punto() {}

// getters
double Punto::getX() const {
    return x;
}

double Punto::getY() const {
    return y;
}

double Punto::getE() const {
    return E;
}

double Punto::getN() const {
    return N;
}

// metodos setters
void Punto::setX(double x) {
    this->x = x;
    this->E = transformarX(x);
}

void Punto::setY(double y) {
    this->y = y;
    this->N = transformarY(y);
}

double Punto::transformarX(double a) {
    return (180*a)/(PI*R);
}

double Punto::transformarY(double a) {
    return ((180*PI)/(2))*atan(exp(a/R)-(PI/2));
}

double Punto::calculateDist3857(const Punto& P) const{
    double tempX, tempY;
    tempX = P.getX() - getX();
    tempY = P.getY() - getY();
    return sqrt(tempX*tempX + tempY*tempY);
}

double Punto::calculateDist4326(const Punto& P) const{
    double latMedia = ((this->getN() + P.getN()) / 2.0) * (PI / 180.0);
    double dE = (P.getE() - this->getE()) * (PI / 180.0) * R * cos(latMedia);
    double dN = (P.getN() - this->getN()) * (PI / 180.0) * R;
    return sqrt(dE*dE + dN*dN);
}

void Punto::print() const{
    cout << "Las coordenadas originales del punto son: (" << getX() << ","
        << getY() << ") y las coordenadas transformadas son: (" << getE() << ","
        << getN() << ")" << endl;
}

bool Punto::operator==(const Punto& P) const {
    if (this->x == P.getX() && this->y == P.getY()) {
        return true;
    }
    return false;
}

Punto& Punto::operator=(const Punto& P) {
    x = P.getX();
    y = P.getY();
    E = P.getE();
    N = P.getN();

    return *this;
}
