#include "Lago.h"

using namespace std;

// constructores y destructor
Lago::Lago() : nombre(""), tipo(""){}

Lago::Lago(string nom, string tipo) 
    : nombre(nom), tipo(tipo){}

Lago::~Lago() {
    perimetros.clear();
}

// getters
string Lago::getTipo() const { return tipo; }
string Lago::getNombre() const { return nombre; }

// setters
void Lago::setTipo(string tipo) { this->tipo = tipo; }
void Lago::setNombre(string nom) { this->nombre = nom; }
void Lago::setPerimetro(vector<SegmentoCosta> seg) { this->perimetros = seg; }

// metodos extra
void Lago::agregarSegmento(const SegmentoCosta& segmento) {
    perimetros.push_back(segmento);
}

bool Lago::operator==(const Lago& otro) const {
    return this->tipo == otro.tipo;
}

vector<FraccionComuna> Lago::repartirPorComuna(const vector<Comuna>& comunas) const {
    vector<FraccionComuna> resultado;

    // recorremos cada segmento del contorno del lago
    for (const auto& seg : perimetros) {
        const vector<Punto>& pts = seg.getPuntos();

        // recorremos cada arista de entre dos puntos consecutivos del contorno
        for (size_t i = 0; i + 1 < pts.size(); i++) {
            const Punto& p1 = pts[i];
            const Punto& p2 = pts[i + 1];

            // aca calculamos el punto medio del tramo se usa para decidir a que comuna pertenece
            Punto medio((p1.getX() + p2.getX()) / 2.0, (p1.getY() + p2.getY()) / 2.0);

            double d3857 = p1.calculateDist3857(p2);
            double d4326 = p1.calculateDist4326(p2);

            // buscamos cual comuna contiene el punto medio
            for (const auto& comuna : comunas) {
                if (comuna.contienePunto(medio)) {
                    // buscamos si ya existe una FraccionComuna para esta comuna
                    bool existe = false;
                    for (auto& frac : resultado) {
                        if (frac.getNombreComuna() == comuna.getNombre()) {
                            frac.acumular(d3857, d4326);
                            existe = true;
                            break;
                        }
                    }

                    if (!existe) {
                        FraccionComuna nueva(comuna.getNombre());
                        nueva.acumular(d3857, d4326);
                        resultado.push_back(nueva);
                    }

                    break; // se asume que el punto medio del tramo cae en una sola comuna
                }
            }
        }
    }

    return resultado;
}
