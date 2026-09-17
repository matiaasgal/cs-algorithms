#ifndef SEGMENTOCOSTA_H
#define SEGMENTOCOSTA_H

#include "./Punto.h"
#include <vector>

using namespace std;

class SegmentoCosta {
    private:
        vector<Punto> puntos;
    public:
        SegmentoCosta();
        ~SegmentoCosta();

        // getters
        const vector<Punto>& getPuntos() const;
        int getCantidadPuntos();

        // metodos extra
        void agregarPunto(const Punto& P);
        double calcularLongitudTotal3857() const;
        double calcularLongitudTotal4326() const;

        // sobrecarga operadores
        SegmentoCosta operator+(const SegmentoCosta& seg) const;
};

#endif
