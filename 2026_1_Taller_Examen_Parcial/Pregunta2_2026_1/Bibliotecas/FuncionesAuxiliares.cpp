#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 133
#define MAX_AULAS 50
#define NO_ENCONTRADO -1

void llenarDisponibilidad(int *arrDia, int *arrHoraInicio, int *arrHoraFin, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrDia[i];
        if (arch.eof()) {
            arrDia[i] = 0;
            break;
        }
        arrHoraInicio[i] = leerHora(arch);
        arrHoraFin[i] = leerHora(arch);
        i++;
    }
}

void llenarArreglosAuxiliares(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                              double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp,
                              int *arrDiaSesTerTard, int *arrHoraSesTerTard, int *arrCantSesFueraDisp, int *arrDia,
                              int *arrHoraInicio, int *arrHoraFin, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int curso, horario, alumnos, profesor, dia, horaInicio, horaFin, aula, i;
    char carAula;
    i = 0;
    while (true) {
        arch >> curso;
        if (arch.eof()) break;
        arch >> horario >> alumnos >> profesor;
        while (true) {
            arch >> dia;
            horaInicio = leerHora(arch);
            horaFin = leerHora(arch);
            int duracion = horaFin - horaInicio;
            arch >> carAula >> aula;
            int posAula = buscarAula(carAula, aula, arrCarAula, arrAula);
            int indice;
            if (posAula == NO_ENCONTRADO) {
                indice = i;
                arrCarAula[indice] = carAula;
                arrAula[indice] = aula;
                i++;
            } else indice = posAula;
            llenarDatos(indice, alumnos, duracion, dia, horaInicio, horaFin, arrDia, arrPromAlumSesion, arrOcupacion,
                        arrCantSesiones, arrHoraSesIniTemp, arrDiaSesIniTemp, arrHoraSesTerTard, arrDiaSesTerTard,
                        arrCantSesFueraDisp, arrHoraInicio, arrHoraFin);
            if (arch.get() == '\r') break;
        }
    }
}

void llenarDatos(int indice, int alumnos, int duracion, int dia, int horaInicio, int horaFin, int *arrDia,
                 double *arrPromAlumSesion, double *arrOcupacion, int *arrCantSesiones, int *arrHoraSesIniTemp,
                 int *arrDiaSesIniTemp, int *arrHoraSesTerTard, int *arrDiaSesTerTard, int *arrCantSesFueraDisp,
                 int *arrHoraInicio, int *arrHoraFin) {
    arrPromAlumSesion[indice] += alumnos;
    arrOcupacion[indice] += duracion;
    arrCantSesiones[indice]++;
    if (arrHoraSesIniTemp[indice] == 0 or horaInicio < arrHoraSesIniTemp[indice]) {
        arrHoraSesIniTemp[indice] = horaInicio;
        arrDiaSesIniTemp[indice] = dia;
    }
    if (arrHoraSesTerTard[indice] == 0 or horaFin > arrHoraSesTerTard[indice]) {
        arrHoraSesTerTard[indice] = horaFin;
        arrDiaSesTerTard[indice] = dia;
    }
    int posDia = buscarDia(dia, arrDia);
    if (posDia != NO_ENCONTRADO) {
        if (not(horaInicio >= arrHoraInicio[posDia] and horaFin <= arrHoraFin[posDia]))
            arrCantSesFueraDisp[
                indice]++;
    }
}


void generarInforme(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                    double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
                    int *arrHoraSesTerTard, int *arrCantSesFueraDisp, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    int totalSesiones = 0, cantSesionesFueraDisp = 0;
    arch << setw(75) << "DETALLE DE OCUPACION DE AULAS" << endl;
    imprimirLinea('=', arch);
    arch << setw(9) << "AULA" << setw(15) << "CANT.SESIONES" << setw(19) << "PROM.ALUM.SESION" << setw(12) <<
            "%OCUPACION" << setw(17) << "SES.INI.TEMP" << setw(17) << "SES.TER.TARD" << setw(20) << "SES.FUERA.DISP." <<
            setw(24) << "CANT.SES.FUERA.DISP" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrAula[i] != 0; i++) {
        arch << setw(2) << i + 1 << ")" << setw(3) << arrCarAula[i] << arrAula[i] << setw(9) << arrCantSesiones[i] <<
                setw(20) << arrPromAlumSesion[i] / arrCantSesiones[i] << setw(14) << arrOcupacion[i] / (
                    6 * 15 * 3600.00 / 100) << " %" << setw(4) << "";
        imprimirSesion(arrDiaSesIniTemp[i], arrHoraSesIniTemp[i], arch);
        arch << setw(3) << "";
        imprimirSesion(arrDiaSesTerTard[i], arrHoraSesTerTard[i], arch);
        if (arrCantSesFueraDisp[i] > 0) {
            arch << setw(9) << "SI" << setw(23) << arrCantSesFueraDisp[i] << endl;
            cantSesionesFueraDisp += arrCantSesFueraDisp[i];
        } else arch << setw(9) << "NO" << setw(23) << arrCantSesFueraDisp[i] << endl;
        totalSesiones += arrCantSesiones[i];
    }
    imprimirLinea('=', arch);
    arch << "TOTAL SESIONES: " << totalSesiones << endl;
    arch << "HAY SESIONES QUE SE DICTAN FUERA DE LA DISPONIBILIDAD: ";
    if (cantSesionesFueraDisp > 0) arch << "SI - " << cantSesionesFueraDisp << " Sesiones" << endl;
    else arch << "NO" << endl;
}

void eliminarArreglos(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                      double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
                      int *arrHoraSesTerTard, int *arrCantSesFueraDisp) {
    int n = contar(arrAula);
    for (int i = 0; arrAula[i] != 0; i++) {
        double disponibilidad = (1 - (arrCantSesFueraDisp[i] / (double) (arrCantSesiones[i]))) * 100.00;
        if (disponibilidad <= 90.00) {
            eliminar(i, arrCarAula, arrAula, arrCantSesiones, arrPromAlumSesion, arrOcupacion, arrDiaSesIniTemp,
                     arrHoraSesIniTemp, arrDiaSesTerTard, arrHoraSesTerTard, arrCantSesFueraDisp, n);
            i--;
        }
    }
}

void eliminar(int indice, char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
              double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
              int *arrHoraSesTerTard, int *arrCantSesFueraDisp, int &numDatos) {
    for (int i = indice; i < numDatos; i++) {
        arrCarAula[i] = arrCarAula[i + 1];
        arrAula[i] = arrAula[i + 1];
        arrCantSesiones[i] = arrCantSesiones[i + 1];
        arrPromAlumSesion[i] = arrPromAlumSesion[i + 1];
        arrOcupacion[i] = arrOcupacion[i + 1];
        arrDiaSesIniTemp[i] = arrDiaSesIniTemp[i + 1];
        arrHoraSesIniTemp[i] = arrHoraSesIniTemp[i + 1];
        arrDiaSesTerTard[i] = arrDiaSesTerTard[i + 1];
        arrHoraSesTerTard[i] = arrHoraSesTerTard[i + 1];
        arrCantSesFueraDisp[i] = arrCantSesFueraDisp[i + 1];
    }
    numDatos--;
}

int contar(int *arrAula) {
    int i = 0;
    while (arrAula[i] != 0) i++;
    return i;
}

void imprimirSesion(int dia, int hora, ofstream &arch) {
    if (dia == 2) arch << "Lunes" << setw(5) << "";
    else if (dia == 3) arch << "Martes" << setw(4) << "";
    else if (dia == 4) arch << "Miercoles" << setw(1) << "";
    else if (dia == 5) arch << "Jueves" << setw(4) << "";
    else if (dia == 6) arch << "Viernes" << setw(3) << "";
    else if (dia == 7) arch << "Sabado" << setw(4) << "";
    imprimirHora(hora, arch);
}

int buscarAula(char carAula, int aula, char *arrCarAula, int *arrAula) {
    for (int i = 0; arrAula[i] != 0; i++) {
        if (arrCarAula[i] == carAula && arrAula[i] == aula) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

int buscarDia(int dia, int *arrDia) {
    for (int i = 0; arrDia[i] != 0; i++) {
        if (dia == arrDia[i]) return i;
    }
    return NO_ENCONTRADO;
}

int leerHora(ifstream &arch) {
    int hh, min;
    char car;
    arch >> hh >> car >> min;
    return hh * 3600 + min * 60;
}

void imprimirHora(int hora, ofstream &arch) {
    int hh, min;
    hh = hora / 3600;
    hora -= hh * 3600;
    min = (hora / 60);
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << setfill(' ');
}

void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

ifstream abrirArchivosEntrada(const char *archEntrada) {
    ifstream arch(archEntrada, ios::in);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archEntrada << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivosSalida(const char *archSalida) {
    ofstream arch(archSalida, ios::out);
    if (not arch) {
        cout << "ERROR AL ABRIR EL ARCHIVO " << archSalida << endl;
        exit(1);
    }
    return arch;
}
