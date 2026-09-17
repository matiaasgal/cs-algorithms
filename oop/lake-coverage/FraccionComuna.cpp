#include "FraccionComuna.h"

// constructores y destructor
FraccionComuna::FraccionComuna() : nombreComuna(""), longitud3857(0.0), longitud4326(0.0) {}

FraccionComuna::FraccionComuna(string nombre) : nombreComuna(nombre), longitud3857(0.0), longitud4326(0.0) {}

FraccionComuna::~FraccionComuna() {}

// getters
string FraccionComuna::getNombreComuna() const { return nombreComuna; }
double FraccionComuna::getLongitud3857() const { return longitud3857; }
double FraccionComuna::getLongitud4326() const { return longitud4326; }

// setters
void FraccionComuna::setNombreComuna(string nombre) { nombreComuna = nombre; }

// metodos extra
// va sumando de a poco la longitud que le corresponde a esta comuna
void FraccionComuna::acumular(double d3857, double d4326) {
    longitud3857 += d3857;
    longitud4326 += d4326;
}

// sobrecarga de operadores
bool FraccionComuna::operator==(const FraccionComuna& otra) const {
    return nombreComuna == otra.nombreComuna;
}

FraccionComuna& FraccionComuna::operator+=(const FraccionComuna& otra) {
    longitud3857 += otra.longitud3857;
    longitud4326 += otra.longitud4326;
    return *this;
}
