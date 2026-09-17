#ifndef LECTORCOMUNAS_H
#define LECTORCOMUNAS_H

#include "Comuna.h"
#include <string>
#include <vector>

using namespace std;

class LectorComunas {
    public:
        static vector<Comuna> extraerDatos(const string& rutaArchivo);
};

#endif