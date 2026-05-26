#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_DISPONIBILIDAD 10
#define MAX_SESIONES 150

int main() {
    int arrDia[MAX_DISPONIBILIDAD], arrHoraInicio[MAX_DISPONIBILIDAD], arrHoraFin[
        MAX_DISPONIBILIDAD];
    llenarDisponibilidad(arrDia, arrHoraInicio, arrHoraFin, "ArchivosDeDatos/Disponibilidad.txt");

    int arrAula[MAX_SESIONES]{}, arrCantSesiones[MAX_SESIONES]{}, arrDiaSesIniTemp[MAX_SESIONES]{}, arrHoraSesIniTemp[
        MAX_SESIONES]{}, arrDiaSesTerTard[MAX_SESIONES]{}, arrHoraSesTerTard[MAX_SESIONES]{}, arrCantSesFueraDisp[
        MAX_SESIONES]{};
    double arrPromAlumSesion[MAX_SESIONES]{}, arrOcupacion[MAX_SESIONES]{};
    char arrCarAula[MAX_SESIONES];
    llenarArreglosAuxiliares(arrCarAula, arrAula, arrCantSesiones, arrPromAlumSesion, arrOcupacion, arrDiaSesIniTemp,
                             arrHoraSesIniTemp, arrDiaSesTerTard, arrHoraSesTerTard, arrCantSesFueraDisp, arrDia,
                             arrHoraInicio, arrHoraFin, "ArchivosDeDatos/Sesiones.txt");

    generarInforme(arrCarAula, arrAula, arrCantSesiones, arrPromAlumSesion, arrOcupacion, arrDiaSesIniTemp,
                   arrHoraSesIniTemp, arrDiaSesTerTard, arrHoraSesTerTard, arrCantSesFueraDisp,
                   "ArchivosDeReporte/Reporte.txt");

    eliminarArreglos(arrCarAula, arrAula, arrCantSesiones, arrPromAlumSesion, arrOcupacion, arrDiaSesIniTemp,
                     arrHoraSesIniTemp, arrDiaSesTerTard, arrHoraSesTerTard, arrCantSesFueraDisp);

    generarInforme(arrCarAula, arrAula, arrCantSesiones, arrPromAlumSesion, arrOcupacion, arrDiaSesIniTemp,
                   arrHoraSesIniTemp, arrDiaSesTerTard, arrHoraSesTerTard, arrCantSesFueraDisp,
                   "ArchivosDeReporte/reporteOcupacionMayor35PC.txt");
    return 0;
}
