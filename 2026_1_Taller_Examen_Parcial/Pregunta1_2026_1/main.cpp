#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    elaborarReporte("ArchivosDeDatos/Cursos.txt", "ArchivosDeDatos/Profesores.txt", "ArchivosDeDatos/Sesiones.txt",
                    "ArchivosDeReporte/Reporte.txt");
    return 0;
}
