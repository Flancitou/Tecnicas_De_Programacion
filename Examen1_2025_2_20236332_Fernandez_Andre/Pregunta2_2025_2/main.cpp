#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_STREAMS 150
#define MAX_CANALES 150

int main() {
    int arrCodigoStream[MAX_STREAMS], arrDuracionStream[MAX_STREAMS], arrIdiomaStream[MAX_STREAMS], arrCategoriaStream[
        MAX_STREAMS];
    char arrCarCategoriaStream[MAX_STREAMS];
    llenarStreams(arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream, arrCategoriaStream,
                  "ArchivosDeDatos/Streams.txt");

    imprimirReportePrueba(arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream,
                          arrCategoriaStream, "ArchivosDeReporte/Reporte_Prueba.txt");

    int arrRepAntigua[MAX_CANALES]{}, arrRepReciente[MAX_CANALES]{}, arrTotRepr[MAX_CANALES]{};
    double arrTotRatCal[MAX_CANALES]{}, arrTotTasaDropOff[MAX_CANALES]{};
    llenarArreglosAuxiliares(arrCodigoStream, arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal,
                             arrTotTasaDropOff, "ArchivosDeDatos/Canales.txt");

    generarReporte(1, arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream,
                   arrCategoriaStream, arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal,
                   arrTotTasaDropOff, "ArchivosDeReporte/Reproducciones-Streams.txt");

    ordenarStreams(arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream, arrCategoriaStream,
                   arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal, arrTotTasaDropOff);

    generarReporte(2, arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream,
                   arrCategoriaStream, arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal,
                   arrTotTasaDropOff, "ArchivosDeReporte/Reproducciones-Streams-Ordenado.txt");

    eliminarStreams(arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream, arrCategoriaStream,
                   arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal, arrTotTasaDropOff);

    generarReporte(2, arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream,
                   arrCategoriaStream, arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal,
                   arrTotTasaDropOff, "ArchivosDeReporte/Reproducciones-Streams-Eliminados.txt");
    return 0;
}
