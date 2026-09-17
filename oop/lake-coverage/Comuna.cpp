#include "Comuna.h"

using namespace std;

// constructores y destructor
Comuna::Comuna() : nombre(""), cod_comuna(0){}

Comuna::Comuna(int id, string nom) 
    : nombre(nom), cod_comuna(id){}

Comuna::~Comuna() {
    perimetros.clear();
}

// getters
int Comuna::getCodComuna() const { return cod_comuna; }
string Comuna::getNombre() const { return nombre; }

// setters
void Comuna::setCodComuna(int id) { cod_comuna = id; }
void Comuna::setNombre(string nom) { nombre = nom; }

// metodos extra
void Comuna::agregarSegmento(const SegmentoCosta& segmento) {
    perimetros.push_back(segmento);
}

bool Comuna::contienePunto(const Punto& p) const {
    // algoritmo Ray Casting implementado de forma general para los polígonos de la comuna
    bool dentroTotal = false;
    double px = p.getX();
    double py = p.getY();

    for (const auto& seg : perimetros) {
        const auto& pts = seg.getPuntos();
        int n = pts.size();
        if (n < 3) continue;

        bool adentroSegmento = false;
        for (int i = 0, j = n - 1; i < n; j = i++) {
            double xi = pts[i].getX(), yi = pts[i].getY();
            double xj = pts[j].getX(), yj = pts[j].getY();

            if (((yi > py) != (yj > py)) &&
                (px < (xj - xi) * (py - yi) / (yj - yi) + xi)) {
                adentroSegmento = !adentroSegmento;
            }
        }
        if (adentroSegmento) {
            dentroTotal = true;
            break;
        }
    }
    return dentroTotal;
}

bool Comuna::operator==(const Comuna& otra) const {
    return this->cod_comuna == otra.cod_comuna;
}

bool Comuna::operator<(const Comuna& otra) const {
    return this->cod_comuna < otra.cod_comuna;
}