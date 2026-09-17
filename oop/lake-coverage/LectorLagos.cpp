#include "LectorLagos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<Lago> LectorLagos::extraerDatos(const string& rutaArchivo) {
    // toda esta parte se encarga validar la existencia del archivo y de abrirlo 
    ifstream archivo(rutaArchivo);
    vector<Lago> datos;
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << rutaArchivo << endl;
        return datos;
    }

    string linea;
    getline(archivo, linea); // ignora la cabecera que viene en el txt 

    // aca empieza a obtener linea por linea
    while (getline(archivo, linea)){
        // esto se hace para los saltos de linea que puedan haber ya que sino no agarra bien las lineas
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }

        size_t inicio = linea.find("POLYGON ((");
        
        // esta condicion se encarga de que si no encuentra el inicio de la parte del polygon, entonces siga iterando
        if (inicio == string::npos){
            continue;
        }

        // si ya tiene el inicio entonces empezamos a buscar el fin, pero como no esta en la misma linea que inicio,
        // sigue iterando hasta encontrarlo, concatenando las lineas siguientes a la original y asi poder tener ambos (inicio y fin)
        size_t fin = linea.find("))");

        while (fin == string::npos) {
            string pedazo;
            if (getline(archivo, pedazo)) {
                if (!pedazo.empty() && pedazo.back() == '\r') {
                    pedazo.pop_back();
                }

                linea += pedazo;
                fin = linea.find("))");
            } else {
                break;
            }
        }

        // mantenemos una condicion en caso de error
        if (fin == string::npos) {
            cerr << "Error: Se encontró un POLYGON que nunca se cerró." << endl;
            continue;
        }

        // a partir de aca empezamos a extraer los datos de polygon
        SegmentoCosta seg;        
        string coordenadas = linea.substr(inicio + 10, fin - (inicio + 10));

        // esto por si el polygon tiene sub listas
        size_t separadorAnillo = coordenadas.find("),(");
        if (separadorAnillo != string::npos) {
            coordenadas = coordenadas.substr(0, separadorAnillo);
        }

        stringstream ss(coordenadas);
        string punto;
    
        while(getline(ss, punto, ',')){
            stringstream ps(punto);
            double x, y;
            if (ps >> x >> y) {
                seg.agregarPunto(Punto(x, y));
            }
        }

        // y aca los demas datos pero solo nos interesa nombre y tipo ya que asi definimos el constructor de lago
        size_t posComa = linea.find(',', fin);

        if (posComa != string::npos) {
            string resto = linea.substr(posComa + 1);
            stringstream rs(resto);
            vector<string> campos;
            string campo;

            while (getline(rs, campo, ',')) {
                campos.push_back(campo);
            }
            
            // esta validacion se encarga de asegurar que extrajo los otros datos y guarda los que necesitamos
            if (campos.size() >= 5) {
                string nombre, tipo;

                if (campos.size() > 3) {
                    nombre = campos[3];
                }
                if (campos.size() > 4) {
                    tipo = campos[4];
                }

                nombre.erase(remove(nombre.begin(), nombre.end(), '\"'), nombre.end());
                if (!nombre.empty() && nombre.front() == ' ') {
                    nombre.erase(0, 1);
                }

                // filtramos por los lagos que necesitamos para no extraer todos y no gastar tanta memoria
                if (nombre != "Lago Llanquihue" && nombre != "Lago Ranco" && nombre != "Lago Villarrica"){
                    continue;
                }

                // en esta parte creamos una bandera para verificar la existencia del lago en el vector
                // si el lago existe entonces agrega el segmento en vez de crear otro objeto
                bool lagoExiste = false;
                for (size_t i = 0; i < datos.size(); ++i) {
                    if (datos[i].getNombre() == nombre) { 
                        datos[i].agregarSegmento(seg);
                        lagoExiste = true;
                        break;
                    }
                }

                if (!lagoExiste) {
                    Lago nuevoLago(nombre, tipo);
                    nuevoLago.agregarSegmento(seg);
                    datos.push_back(nuevoLago);

                    // esta linea la usamos para ir probando el codigo pero la dejamos ahi por si se quiere ver ams info
                    // cout << "lago: " << nuevoLago.getNombre() << "(" << nuevoLago.getTipo() << ")" << endl;
                }
            }
        }
    }

    if (datos.empty()) {
        cout << "No se encontró ningún POLYGON en el archivo de lagos" << endl;
    }

    return datos;  
}