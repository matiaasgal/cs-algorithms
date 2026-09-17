#include <iostream>
#include <vector>
#include "SegmentoCosta.h"

SegmentoCosta::SegmentoCosta(){}

SegmentoCosta::~SegmentoCosta(){
    puntos.clear();
}

void SegmentoCosta::agregarPunto(const Punto& P){
    puntos.push_back(P);
}

// getters
const vector<Punto>& SegmentoCosta::getPuntos() const {
    return puntos;
}

int SegmentoCosta::getCantidadPuntos(){
    return (puntos.size());
}

double SegmentoCosta::calcularLongitudTotal3857() const{
    if (this->puntos.size() < 2){
        return 0;
    }
    double metros = 0;
    for (size_t i = 0; i < this->puntos.size() - 1; i++){
        metros = metros + this->puntos[i].calculateDist3857(this->puntos[i+1]);
    }
    return metros;
}

double SegmentoCosta::calcularLongitudTotal4326() const{
    if (this->puntos.size() < 2){
        return 0;
    }
    double metros = 0;
    for (size_t i = 0; i < this->puntos.size() - 1; i++){
        metros = metros + this->puntos[i].calculateDist4326(this->puntos[i+1]);
    }
    return metros;
}

SegmentoCosta SegmentoCosta::operator+(const SegmentoCosta& otro) const {
    SegmentoCosta resultado = *this;
    for (const auto& p : otro.puntos) {
        resultado.agregarPunto(p);
    }
    return resultado;
}
