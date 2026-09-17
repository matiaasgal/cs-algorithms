#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "LectorLagos.h"
#include "LectorComunas.h"
#include "SegmentoCosta.h"
#include "Lago.h"
#include "Comuna.h"
#include "FraccionComuna.h"

using namespace std;

// declaramos funciones extras qeu vamos a usar en el main
// convierte un numero a texto con 2 decimales
string formatearNumero(double valor);
// imprime el como el "reporte" del lago
void imprimirReporteLago(const Lago& lago, const vector<Comuna>& comunas);

int main() {
    string rutaLagos = "masas_lacustres.txt"; 
    string rutaComunas = "comunas.txt";

    vector<Lago> lagos = LectorLagos::extraerDatos(rutaLagos);
    vector<Comuna> comunas = LectorComunas::extraerDatos(rutaComunas);

    for (const auto& lago : lagos) {
        imprimirReporteLago(lago, comunas);
        cout << "======================================" << endl << endl;
    }

    return 0;
}

string formatearNumero(double valor) {
    ostringstream oss;
    oss << fixed << setprecision(2) << valor;
    string texto = oss.str();
    return texto;
}

void imprimirReporteLago(const Lago& lago, const vector<Comuna>& comunas) {
    vector<FraccionComuna> fracciones = lago.repartirPorComuna(comunas);

    if (fracciones.empty()) {
        cout << "No se encontraron comunas para el lago " << lago.getNombre() << endl << endl;
        return;
    }

    // totales del lago en cada sistema vienen en metro asi que al imprimir hacemos la conversion
    double total3857 = 0.0;
    double total4326 = 0.0;
    for (const auto& frac : fracciones) {
        total3857 += frac.getLongitud3857();
        total4326 += frac.getLongitud4326();
    }

    cout << lago.getNombre() << ":" << endl << endl;

    cout << "Sistema EPSG:3857" << endl;
    for (const auto& frac : fracciones) {
        double km = frac.getLongitud3857() / 1000.0;
        double porcentaje = (total3857 > 0) ? (frac.getLongitud3857() / total3857) * 100.0 : 0.0;
        cout << "- Comuna " << frac.getNombreComuna() << ": " << formatearNumero(km)
             << " km (" << formatearNumero(porcentaje) << " %)" << endl;
    }
    cout << "- TOTAL: " << formatearNumero(total3857 / 1000.0) << " km" << endl << endl;

    cout << "Sistema EPSG:4326" << endl;
    for (const auto& frac : fracciones) {
        double km = frac.getLongitud4326() / 1000.0;
        double porcentaje = (total4326 > 0) ? (frac.getLongitud4326() / total4326) * 100.0 : 0.0;
        cout << "- Comuna " << frac.getNombreComuna() << ": " << formatearNumero(km)
             << " km  (" << formatearNumero(porcentaje) << " %)" << endl;
    }
    cout << "- TOTAL: " << formatearNumero(total4326 / 1000.0) << " km" << endl << endl;

    cout << "Distorsiones: EPSG:3857 - EPSG:4326" << endl;
    double totalDiferenciaKm = 0.0;
    for (const auto& frac : fracciones) {
        double km3857 = frac.getLongitud3857() / 1000.0;
        double km4326 = frac.getLongitud4326() / 1000.0;
        double diferenciaKm = km3857 - km4326;
        double diferenciaPorcentaje = (km3857 > 0) ? (diferenciaKm / km3857) * 100.0 : 0.0;
        totalDiferenciaKm += diferenciaKm;
        cout << "- Comuna " << frac.getNombreComuna() << ": " << formatearNumero(diferenciaKm)
             << " km (" << formatearNumero(diferenciaPorcentaje) << " %)" << endl;
    }
    double totalDiferenciaPorcentaje = (total3857 > 0) ? (totalDiferenciaKm / (total3857 / 1000.0)) * 100.0 : 0.0;
    cout << "- TOTAL: " << formatearNumero(totalDiferenciaKm) << " km ("
         << formatearNumero(totalDiferenciaPorcentaje) << " %)" << endl << endl;

    cout << "Distorsiones: EPSG:3857 / EPSG:4326" << endl;
    for (const auto& frac : fracciones) {
        double km3857 = frac.getLongitud3857() / 1000.0;
        double km4326 = frac.getLongitud4326() / 1000.0;
        double cociente = (km3857 > 0) ? (km4326 / km3857) * 100.0 : 0.0;
        cout << "- Comuna  " << frac.getNombreComuna() << ": (" << formatearNumero(cociente) << " %)" << endl;
    }
    double totalCociente = (total3857 > 0) ? (total4326 / total3857) * 100.0 : 0.0;
    cout << "- TOTAL: " << formatearNumero(totalCociente) << "%." << endl << endl;
}