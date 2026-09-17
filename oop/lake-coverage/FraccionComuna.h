#ifndef FRACCIONCOMUNA_H
#define FRACCIONCOMUNA_H

#include <string>

using namespace std;

class FraccionComuna {
    private:
        string nombreComuna;
        double longitud3857;
        double longitud4326;

    public:
        // constructores y destructor
        FraccionComuna();
        FraccionComuna(string nombre);
        ~FraccionComuna();

        // getters
        string getNombreComuna() const;
        double getLongitud3857() const;
        double getLongitud4326() const;

        // setters
        void setNombreComuna(string nombre);

        // metodos extra
        void acumular(double d3857, double d4326);

        // sobrecarga de operadores
        bool operator==(const FraccionComuna& otra) const;
        FraccionComuna& operator+=(const FraccionComuna& otra);
};

#endif
