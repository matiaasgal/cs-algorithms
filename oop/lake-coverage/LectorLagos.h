#ifndef LECTORLAGOS_H
#define LECTORLAGOS_H

#include "Lago.h"
#include <string>
#include <vector>

using namespace std;

class LectorLagos {
    public:
        static vector<Lago> extraerDatos(const string& rutaArchivo);
};

#endif