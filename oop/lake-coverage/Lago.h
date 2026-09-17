#ifndef LAGO_H
#define LAGO_H

#include "./SegmentoCosta.h"
#include "./Comuna.h"
#include "./FraccionComuna.h"
#include <string>
#include <vector>

using namespace std;

class Lago {
    private:
        string nombre;
        string tipo;
        vector<SegmentoCosta> perimetros;
        
    public:
        Lago();
        Lago(string nom, string tipo);
        ~Lago();

        // getters
        string getNombre() const;
        string getTipo() const;

        // setters
        void setNombre(string nom);
        void setTipo(string tipo);
        void setPerimetro(vector<SegmentoCosta> seg);

        // metodos extra
        void agregarSegmento(const SegmentoCosta& segmento);

        // reparte el contorno del lago entre las comunas recibidas, tramo a tramo
        vector<FraccionComuna> repartirPorComuna(const vector<Comuna>& comunas) const;

        // sobrecarga de operadores
        bool operator==(const Lago& otro) const;
};

#endif