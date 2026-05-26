#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    elaborarReporte("ArchivosDeDatos/Streams.txt", "ArchivosDeDatos/Categorias.txt", "ArchivosDeDatos/Idiomas.txt",
                    "ArchivosDeDatos/Canales.txt", "ArchivosDeReporte/Reporte.txt");
    return 0;
}