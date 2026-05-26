#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 122
#define NO_ENCONTRADO -1

void llenarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream, char *arrCarCategoriaStream,
                   int *arrCategoriaStream, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int codigo, duracion, idioma, categoria;
    char carCategoria;
    int i = 0;
    while (true) {
        arch >> codigo;
        if (arch.eof()) {
            arrCodigoStream[i] = 0;
            break;
        }
        duracion = leerDuracion(arch);
        arch >> idioma >> carCategoria >> categoria;
        insertarOrdenado(i, codigo, duracion, idioma, carCategoria, categoria, arrCodigoStream, arrDuracionStream,
                         arrIdiomaStream, arrCarCategoriaStream, arrCategoriaStream);
        i++;
    }
}

void imprimirReportePrueba(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                           char *arrCarCategoriaStream, int *arrCategoriaStream, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(56) << "REPORTE DE PRUEBA - STREAMS" << endl;
    arch << setw(18) << "CODIGO" << setw(20) << "DURACION" << setw(18) << "IDIOMA" << setw(21) << "CATEGORIA" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrCodigoStream[i] != 0; i++) {
        arch << setw(18) << arrCodigoStream[i] << setw(12) << "";
        imprimirDuracion(arrDuracionStream[i], arch);
        arch << setw(17) << arrIdiomaStream[i] << setw(16) << arrCarCategoriaStream[i] << arrCategoriaStream[i] << endl;
    }
}

void insertarOrdenado(int numDatos, int codigo, int duracion, int idioma, char carCategoria, int categoria,
                      int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream, char *arrCarCategoriaStream,
                      int *arrCategoriaStream) {
    int pos = numDatos - 1;
    while (pos >= 0 and idioma > arrIdiomaStream[pos] or (
               idioma == arrIdiomaStream[pos] and codigo < arrCodigoStream[pos])) {
        arrCodigoStream[pos + 1] = arrCodigoStream[pos];
        arrDuracionStream[pos + 1] = arrDuracionStream[pos];
        arrIdiomaStream[pos + 1] = arrIdiomaStream[pos];
        arrCarCategoriaStream[pos + 1] = arrCarCategoriaStream[pos];
        arrCategoriaStream[pos + 1] = arrCategoriaStream[pos];
        pos--;
    }
    arrCodigoStream[pos + 1] = codigo;
    arrDuracionStream[pos + 1] = duracion;
    arrIdiomaStream[pos + 1] = idioma;
    arrCarCategoriaStream[pos + 1] = carCategoria;
    arrCategoriaStream[pos + 1] = categoria;
}

void llenarArreglosAuxiliares(int *arrCodigoStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr,
                              double *arrTotRatCal, double *arrTotTasaDropOff, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, codigoCanal, codigoStream, fecha, duracion;
    double ratingCalidad, tasaDropOff;
    char carCodigoCanal;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        ignorarHasta(' ', arch);
        arch >> carCodigoCanal >> codigoCanal >> ws;
        ignorarHasta(' ', arch);
        while (true) {
            arch >> codigoStream;
            fecha = leerFecha(arch);
            duracion = leerDuracion(arch);
            arch >> ratingCalidad >> tasaDropOff;
            int posStream = buscarStream(codigoStream, arrCodigoStream);
            if (posStream != NO_ENCONTRADO) {
                if (arrRepAntigua[posStream] == 0 or fecha < arrRepAntigua[posStream]) arrRepAntigua[posStream] = fecha;
                if (arrRepReciente[posStream] == 0 or fecha > arrRepReciente[posStream])
                    arrRepReciente[posStream] = fecha;
                arrTotRepr[posStream]++;
                arrTotRatCal[posStream] += ratingCalidad;
                arrTotTasaDropOff[posStream] += tasaDropOff;
            }
            if (arch.get() == '\r') break;
        }
    }
}

void generarReporte(int tipo, int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                    char *arrCarCategoriaStream,
                    int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr,
                    double *arrTotRatCal, double *arrTotTasaDropOff, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    int streamMenorDuracion, menorDuracion = 0, streamMayorDuracion, mayorDuracion = 0;
    double promRatCal, promTasaDropOff;
    imprimirCabecera(tipo, arch);
    for (int i = 0; arrCodigoStream[i] != 0; i++) {
        arch << arrCodigoStream[i] << setw(8) << arrIdiomaStream[i] << setw(7) << arrCarCategoriaStream[i] <<
                arrCategoriaStream[i] << setw(5) << "";
        int totRepr = arrTotRepr[i] * arrDuracionStream[i];
        if (arrTotRepr[i] == 0) {
            promRatCal = arrTotRatCal[i];
            promTasaDropOff = arrTotTasaDropOff[i];
            arch << setw(5) << "-" << setw(15) << "-";
            if (tipo == 1) arch << setw(16) << "-" << setw(17) << "-" << setw(11) << "";
            else arch << setw(16) << promRatCal << setw(18) << promTasaDropOff << "%" << setw(9) << "";
        } else {
            promRatCal = arrTotRatCal[i] / arrTotRepr[i];
            promTasaDropOff = arrTotTasaDropOff[i] / arrTotRepr[i] * 100;
            imprimirFecha(arrRepAntigua[i], arch);
            arch << setw(5) << "";
            imprimirFecha(arrRepReciente[i], arch);
            arch << setw(11) << promRatCal << setw(18) << promTasaDropOff << "%" << setw(9) << "";
        }
        imprimirDuracion(arrDuracionStream[i], arch);
        arch << setw(6) << arrTotRepr[i] << setw(5) << "";
        imprimirDuracion(totRepr, arch);
        arch << endl;
        calcularMenorMayorDuracion(totRepr, arrCodigoStream[i], streamMenorDuracion, menorDuracion, streamMayorDuracion,
                                   mayorDuracion);
    }
    if (tipo == 1) imprimirResumen(streamMenorDuracion, menorDuracion, streamMayorDuracion, mayorDuracion, arch);
}

void imprimirResumen(int streamMenorDuracion, int menorDuracion, int streamMayorDuracion, int mayorDuracion,
                     ofstream &arch) {
    imprimirLinea('-', arch);
    arch << "RESUMEN:" << endl;
    arch << "STREAM CON MAYOR DURACION:" << setw(10) << streamMayorDuracion << " - ";
    imprimirDuracion(mayorDuracion, arch);
    arch << " hrs" << endl;
    arch << "STREAM CON MENOR DURACION:" << setw(10) << streamMenorDuracion << " - ";
    imprimirDuracion(menorDuracion, arch);
    arch << " hrs" << endl;
    imprimirLinea('=', arch);
}

void calcularMenorMayorDuracion(int totRepr, int arrCodigoStream, int &streamMenorDuracion, int &menorDuracion,
                                int &streamMayorDuracion, int &mayorDuracion) {
    if (totRepr == 0) return;
    if (menorDuracion == 0 or totRepr < menorDuracion) {
        menorDuracion = totRepr;
        streamMenorDuracion = arrCodigoStream;
    }
    if (mayorDuracion == 0 or totRepr > mayorDuracion) {
        mayorDuracion = totRepr;
        streamMayorDuracion = arrCodigoStream;
    }
}

void ordenarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                    char *arrCarCategoriaStream, int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente,
                    int *arrTotRepr, double *arrTotRatCal, double *arrTotTasaDropOff) {
    int n = contar(arrCodigoStream);
    double promTasaDropOffI, promTasaDropOffJ;
    for (int i = 0; i < n - 1; i++) {
        if (arrTotRepr[i] != 0) promTasaDropOffI = arrTotTasaDropOff[i] / arrTotRepr[i];
        else promTasaDropOffI = arrTotRatCal[i] = arrTotTasaDropOff[i] = 0.00;
        for (int j = i + 1; j < n; j++) {
            if (arrTotRepr[j] != 0)promTasaDropOffJ = arrTotTasaDropOff[j] / arrTotRepr[j];
            else promTasaDropOffJ = arrTotRatCal[j] = arrTotTasaDropOff[j] = 0.00;
            if (arrIdiomaStream[i] > arrIdiomaStream[j] or (
                    arrIdiomaStream[i] == arrIdiomaStream[j] and promTasaDropOffI < promTasaDropOffJ)) {
                intercambiarInt(arrCodigoStream[i], arrCodigoStream[j]);
                intercambiarInt(arrDuracionStream[i], arrDuracionStream[j]);
                intercambiarInt(arrIdiomaStream[i], arrIdiomaStream[j]);
                intercambiarChar(arrCarCategoriaStream[i], arrCarCategoriaStream[j]);
                intercambiarInt(arrCategoriaStream[i], arrCategoriaStream[j]);
                intercambiarInt(arrRepAntigua[i], arrRepAntigua[j]);
                intercambiarInt(arrRepReciente[i], arrRepReciente[j]);
                intercambiarInt(arrTotRepr[i], arrTotRepr[j]);
                intercambiarDouble(arrTotRatCal[i], arrTotRatCal[j]);
                intercambiarDouble(arrTotTasaDropOff[i], arrTotTasaDropOff[j]);
            }
        }
    }
}

void eliminarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                     char *arrCarCategoriaStream, int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente,
                     int *arrTotRepr, double *arrTotRatCal, double *arrTotTasaDropOff) {
    int n = contar(arrCodigoStream);
    double promTasaDropOff;
    for (int i = 0; arrCodigoStream[i] != 0; i++) {
        if (arrTotRepr[i] != 0) promTasaDropOff = (arrTotTasaDropOff[i] / arrTotRepr[i]) * 100;
        else promTasaDropOff = arrTotRatCal[i] = arrTotTasaDropOff[i] = 0.00;
        if (promTasaDropOff < 60.00) {
            eliminar(i, arrCodigoStream, arrDuracionStream, arrIdiomaStream, arrCarCategoriaStream, arrCategoriaStream,
                     arrRepAntigua, arrRepReciente, arrTotRepr, arrTotRatCal, arrTotTasaDropOff, n);
            i--;
        }
    }
}

void eliminar(int indice, int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
              char *arrCarCategoriaStream,
              int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr, double *arrTotRatCal,
              double *arrTotTasaDropOff, int &numDatos) {
    for (int i = indice; i < numDatos; i++) {
        arrCodigoStream[i] = arrCodigoStream[i + 1];
        arrDuracionStream[i] = arrDuracionStream[i + 1];
        arrIdiomaStream[i] = arrIdiomaStream[i + 1];
        arrCarCategoriaStream[i] = arrCarCategoriaStream[i + 1];
        arrCategoriaStream[i] = arrCategoriaStream[i + 1];
        arrRepAntigua[i] = arrRepAntigua[i + 1];
        arrRepReciente[i] = arrRepReciente[i + 1];
        arrTotRepr[i] = arrTotRepr[i + 1];
        arrTotRatCal[i] = arrTotRatCal[i + 1];
        arrTotTasaDropOff[i] = arrTotTasaDropOff[i + 1];
    }
    numDatos--;
}

int contar(int *arrCodigoStream) {
    int i = 0;
    while (arrCodigoStream[i] != 0) i++;
    return i;
}

void intercambiarInt(int &datoI, int &datoK) {
    int aux = datoI;
    datoI = datoK;
    datoK = aux;
}

void intercambiarDouble(double &datoI, double &datoK) {
    double aux = datoI;
    datoI = datoK;
    datoK = aux;
}

void intercambiarChar(char &datoI, char &datoK) {
    char aux = datoI;
    datoI = datoK;
    datoK = aux;
}

void imprimirCabecera(int tipo, ofstream &arch) {
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(74) << "PLATAFORMA DE STREAMING TP" << endl;
    if (tipo == 1) arch << setw(82) << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS" << endl;
    else
        arch << setw(100) << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR IDIOMA Y POR TASA DROP-OFF" <<
                endl;
    imprimirLinea('=', arch);
    arch << "STREAM" << setw(9) << "IDIOMA" << setw(12) << "CATEGORIA" << setw(14) << "REP.ANTIGUA" << setw(15) <<
            "REP.RECIENTE" << setw(15) << "PROM.RAT.CAL" << setw(21) << "PROM.TASA.DROP-OFF" << setw(9) << "DURAC." <<
            setw(9) << "#REPR." << setw(12) << "TOT.REPR." << endl;
    imprimirLinea('-', arch);
}

int buscarStream(int codigoStream, int *arrCodigoStream) {
    for (int i = 0; arrCodigoStream[i] != 0; i++) {
        if (codigoStream == arrCodigoStream[i]) return i;
    }
    return NO_ENCONTRADO;
}

int leerFecha(ifstream &arch) {
    int dd, mm, aa;
    char car;
    arch >> dd >> car >> mm >> car >> aa;
    return dd + mm * 100 + aa * 10000;
}

void imprimirFecha(int fecha, ofstream &arch) {
    int dd, mm, aa;
    aa = fecha / 10000;
    fecha -= aa * 10000;
    mm = fecha / 100;
    fecha -= mm * 100;
    dd = fecha;
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setfill(' ') << aa;
}


int leerDuracion(ifstream &arch) {
    int hh, min, ss;
    char car;
    arch >> hh >> car >> min >> car >> ss;
    return hh * 3600 + min * 60 + ss;
}

void imprimirDuracion(int duracion, ofstream &arch) {
    int hh, min, ss;
    hh = duracion / 3600;
    duracion -= hh * 3600;
    min = duracion / 60;
    duracion -= min * 60;
    ss = duracion;
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}


void imprimirLinea(char car, ofstream &arch) {
    for (int i = 0; i < MAX_LINES; i++) arch.put(car);
    arch.put('\n');
}

void ignorarHasta(char delim, ifstream &arch) {
    while (arch.get() != delim);
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
