#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_TABLAS 200
#define MAX_INFRACCIONES 700

int main() {
    int arrInfraccion[MAX_TABLAS];
    double arrMulta[MAX_TABLAS];
    char arrCarInfraccion[MAX_TABLAS];
    llenarTabla(arrCarInfraccion, arrInfraccion, arrMulta, "ArchivosDeDatos/TablaDeInfracciones.txt");

    imprimirReportePrueba(arrCarInfraccion, arrInfraccion, arrMulta, "ArchivosDeReporte/Reporte_Prueba.txt");

    int arrNumPlaca1[MAX_INFRACCIONES]{}, arrNumPlaca2[MAX_INFRACCIONES]{}, arrPagadasCantidad[MAX_INFRACCIONES]{},
            arrPendientesCantidad[MAX_INFRACCIONES]{}, arrPendienteMasAntigua[MAX_INFRACCIONES]{};
    double arrPagadasTotal[MAX_INFRACCIONES]{}, arrPendientesTotal[MAX_INFRACCIONES]{};
    char arrCarPlaca[MAX_INFRACCIONES];
    llenarArreglosAuxiliares(arrCarInfraccion, arrInfraccion, arrMulta, arrCarPlaca, arrNumPlaca1, arrNumPlaca2,
                             arrPagadasCantidad, arrPagadasTotal, arrPendientesCantidad, arrPendientesTotal,
                             arrPendienteMasAntigua, "ArchivosDeDatos/InfraccionesCometidas.txt");

    ordenarPlacas(arrCarPlaca, arrNumPlaca1, arrNumPlaca2, arrPagadasCantidad, arrPagadasTotal, arrPendientesCantidad,
                  arrPendientesTotal, arrPendienteMasAntigua);

    generarReporte(arrCarPlaca, arrNumPlaca1, arrNumPlaca2, arrPagadasCantidad, arrPagadasTotal, arrPendientesCantidad,
                   arrPendientesTotal, arrPendienteMasAntigua, "ArchivosDeReporte/Reporte.txt");
    return 0;
}
