#include "LectorComunas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<Comuna> LectorComunas::extraerDatos(const string& rutaArchivo) {
    // toda esta parte se encarga validar la existencia del archivo y de abrirlo 
    ifstream archivo(rutaArchivo);
    vector<Comuna> datos;
    
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

        size_t inicio = linea.find("POLYGON");
        
        // esta condicion se encarga de que si no encuentra el inicio de la parte del polygon, entonces siga iterando
        if (inicio == string::npos){
            continue;
        }

        // si ya tiene el inicio entonces empezamos a buscar el fin, pero como no esta en la misma linea que inicio,
        // sigue iterando hasta encontrarlo concatenando las lineas siguientes a la original y asi poder tener ambos (inicio y fin)
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
        size_t posInicioCoords = linea.find_first_of("0123456789-", inicio);    
        string coordenadas = linea.substr(posInicioCoords, fin - posInicioCoords);

        // por si el polygon tiene sub listas
        size_t separadorAnillo = coordenadas.find("),(");
        if (separadorAnillo != string::npos) {
            coordenadas = coordenadas.substr(0, separadorAnillo);
        }

        coordenadas.erase(remove(coordenadas.begin(), coordenadas.end(), '('), coordenadas.end());
        coordenadas.erase(remove(coordenadas.begin(), coordenadas.end(), ')'), coordenadas.end());
        stringstream ss(coordenadas);
        string punto;
    
        while(getline(ss, punto, ',')){
            stringstream ps(punto);
            double x, y;
            if (ps >> x >> y) {
                seg.agregarPunto(Punto(x, y));
            }
        }

        // y aca los demas datos pero solo nos interesa nombre y el codigo ya que asi definimos el constructor de comuna
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
            if (campos.size() >= 10) {
                int id = 0;
                string strId = campos[4];
                strId.erase(remove(strId.begin(), strId.end(), '\"'), strId.end());
                // dejamos este try catch por si es qu eno se logra transformar el string a un int
                try {
                    id = stoi(strId);
                } catch (...) {
                    id = 0;
                }

                string nombreRegion = campos[8];
                nombreRegion.erase(remove(nombreRegion.begin(), nombreRegion.end(), '\"'), nombreRegion.end());
                if (!nombreRegion.empty() && nombreRegion.front() == ' ') {
                    nombreRegion.erase(0, 1);
                }

                string nombre = campos[9];
                nombre.erase(remove(nombre.begin(), nombre.end(), '\"'), nombre.end());
                if (!nombre.empty() && nombre.front() == ' ') {
                    nombre.erase(0, 1);
                }

                nombreRegion.erase(remove(nombreRegion.begin(), nombreRegion.end(), '\"'), nombreRegion.end());
                if (!nombreRegion.empty() && nombreRegion.front() == ' ') {
                    nombreRegion.erase(0, 1);
                }

                // para no extraer todas las comunas y evitar tanto gasto de memoria filtramos por los que sabemos que estan en la misma region que los lagos
                // buscamos asi ya que esas partes que no incluimos contienen tildes lo que dificulta la busqueda
                if (nombreRegion.find("Los Lagos") == string::npos && nombreRegion.find("Los R") == string::npos && nombreRegion.find("Araucan") == string::npos){
                    continue;
                }
                
                // en esta parte creamos una bandera para verificar la existencia de la comuna en el vector
                // si la comuna existe entonces agrega el segmento en vez de crear otro objeto
                bool comunaExiste = false;
                for (size_t i = 0; i < datos.size(); ++i) {
                    if (datos[i].getCodComuna() == id) {
                        datos[i].agregarSegmento(seg);
                        comunaExiste = true;
                        break;
                    }
                }

                if (!comunaExiste) {
                    Comuna nuevaComuna(id, nombre);
                    nuevaComuna.agregarSegmento(seg);
                    datos.push_back(nuevaComuna);

                    // esta linea la usamos para ir probando el codigo pero la dejamos ahi por si se quiere ver ams info
                    //cout << "comuna: " << nuevaComuna.getNombre() << "(" << nuevaComuna.getCodComuna() << ")" << endl;
                }

            }
        }
    }

    if (datos.empty()) {
        cout << "No se encontró ningún POLYGON en el archivo de comunas" << endl;
    }
    return datos;  
}