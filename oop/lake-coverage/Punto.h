#ifndef PUNTO_H
#define PUNTO_H

class Punto {
    private:
        // coordenadas originales 3857
        double x;
        double y;

        // coordenadas transformadas 4326
        double E;
        double N;
        
        static constexpr double PI = 3.141592653589793;
        static constexpr double R = 6378137.0;
        
        double transformarX(double a);
        double transformarY(double a);
    public:
        // constructores
        Punto();
        Punto(double x, double y);
        ~Punto();

        // getters
        double getX() const;
        double getY() const;
        double getE() const;
        double getN() const;

        // setters
        void setX(double x);
        void setY(double y);

        // metodos extra
        double calculateDist3857(const Punto& P) const;
        double calculateDist4326(const Punto& P) const;
        void print() const;

        // sobrecarga de operador
        bool operator==(const Punto& P) const;
        Punto& operator=(const Punto& P);
};

#endif
