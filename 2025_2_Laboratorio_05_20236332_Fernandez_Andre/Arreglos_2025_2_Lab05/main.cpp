#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_CANALES 150
#define MAX_ETIQUETAS 150
#define MAX_CRUZADOS 600
#define MAX_REPRODUCCIONES 800

int main() {
    int arrNumCanal[MAX_CANALES];
    double arrRatingCanal[MAX_CANALES];
    char arrCarCanal[MAX_CANALES];
    llenarCanales(arrCarCanal, arrNumCanal, arrRatingCanal, "ArchivosDeDatos/Canales.txt");

    int arrNumEtiqueta[MAX_ETIQUETAS], arrDuracionEtiqueta[MAX_ETIQUETAS];
    llenarEtiquetas(arrNumEtiqueta, arrDuracionEtiqueta, "ArchivosDeDatos/Etiquetas.txt");

    int arrNumCanalCruzado[MAX_CRUZADOS], arrNumEtiquetaCruzado[MAX_CRUZADOS];
    char arrCarCanalCruzado[MAX_CRUZADOS];
    llenarCruzados(arrCarCanalCruzado, arrNumCanalCruzado, arrNumEtiquetaCruzado,
                   "ArchivosDeDatos/EtiquetasEnCanales.txt");

    imprimirReportePrueba(arrCarCanal, arrNumCanal, arrRatingCanal, arrNumEtiqueta, arrDuracionEtiqueta,
                          arrCarCanalCruzado, arrNumCanalCruzado, arrNumEtiquetaCruzado,
                          "ArchivosDeReporte/Reporte_Prueba.txt");

    ordenarEtiquetasXDuracion(arrNumEtiqueta, arrDuracionEtiqueta);

    int arrTotalReproduccion[MAX_REPRODUCCIONES]{}, arrTotalDuracion[MAX_REPRODUCCIONES]{};
    llenarArreglosAuxiliares(arrCarCanal, arrNumCanal, arrRatingCanal, arrNumEtiqueta, arrDuracionEtiqueta,
                             arrCarCanalCruzado, arrNumCanalCruzado, arrNumEtiquetaCruzado, arrTotalReproduccion,
                             arrTotalDuracion, "ArchivosDeDatos/ReproduccionesDeEtiquetas.txt");

    generarInforme(arrCarCanal, arrNumCanal, arrRatingCanal, arrNumEtiqueta, arrDuracionEtiqueta,
                   arrCarCanalCruzado, arrNumCanalCruzado, arrNumEtiquetaCruzado, arrTotalReproduccion,
                   arrTotalDuracion, "ArchivosDeReporte/ReporteDeCanales_Y_Etiquetas.txt");
    return 0;
}
