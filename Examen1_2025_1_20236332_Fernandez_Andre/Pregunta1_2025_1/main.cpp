#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    generarReporte("ArchivosDeDatos/EmpresasRegistradas.txt", "ArchivosDeDatos/PlacasRegistradas.txt",
                   "ArchivosDeDatos/InfraccionesCometidas.txt", "ArchivosDeDatos/TablaDeInfracciones.txt",
                   "ArchivosDeReporte/Reporte.txt");
    return 0;
}
