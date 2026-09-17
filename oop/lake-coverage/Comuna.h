#ifndef COMUNA_H
#define COMUNA_H

#include "./SegmentoCosta.h"
#include <string>
#include <vector>

using namespace std;

class Comuna {
    private:
        string nombre;
        int cod_comuna;
        vector<SegmentoCosta> perimetros;

    public:
        // constructores y destructor
        Comuna();
        Comuna(int cod, string nom);
        ~Comuna();
        
        // getters
        int getCodComuna() const;
        string getNombre() const;

        // setters
        void setCodComuna(int cod);
        void setNombre(string nom);
        
        // metodos extra
        void agregarSegmento(const SegmentoCosta& segmento);
        
        // metodo para saber si un punto está dentro de la comuna (Ray Casting)
        bool contienePunto(const Punto& p) const;

        // sobrecarga de operadores
        bool operator==(const Comuna& otra) const;
        bool operator<(const Comuna& otra) const;
};

#endif
