#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135
#define NO_ENCONTRADO -1

void llenarTabla(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrCarInfraccion[i];
        if (arch.eof()) {
            arrInfraccion[i] = 0;
            break;
        }
        arch >> arrInfraccion[i] >> arrMulta[i] >> ws;
        ignorarHasta('\n', arch);
        i++;
    }
}

void imprimirReportePrueba(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(40) << "REPORTE DE PRUEBA - TABLA INFRACCIONES" << endl;
    arch << setw(15) << "CODIGO" << setw(14) << "MULTA" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrInfraccion[i] != 0; i++) {
        arch << setw(10) << arrCarInfraccion[i] << arrInfraccion[i] << setw(16) << arrMulta[i] << endl;
    }
}

void llenarArreglosAuxiliares(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, char *arrCarPlaca,
                              int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad, double *arrPagadasTotal,
                              int *arrPendientesCantidad, double *arrPendientesTotal, int *arrPendienteMasAntigua,
                              const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int fecha, numPlaca1, numPlaca2, numInfraccion, indice, i = 0;
    char carPlaca, carInfraccion, car;
    while (true) {
        fecha = leerFecha(arch);
        if (fecha == 0) break;
        arch >> carPlaca >> numPlaca1 >> car >> numPlaca2;
        int posPlaca = buscarPlaca(i, carPlaca, numPlaca1, numPlaca2, arrCarPlaca, arrNumPlaca1, arrNumPlaca2);
        if (posPlaca == NO_ENCONTRADO) {
            indice = i;
            arrCarPlaca[indice] = carPlaca;
            arrNumPlaca1[indice] = numPlaca1;
            arrNumPlaca2[indice] = numPlaca2;
            i++;
        } else indice = posPlaca;
        arch >> carInfraccion >> numInfraccion;
        int posInfraccion = buscarInfraccion(carInfraccion, numInfraccion, arrCarInfraccion, arrInfraccion);
        if (posInfraccion != NO_ENCONTRADO) {
            if (arch.get() == ' ') {
                arrPagadasCantidad[indice]++;
                arrPagadasTotal[indice] += arrMulta[posInfraccion];
                ignorarHasta('\r', arch);
            } else {
                arrPendientesCantidad[indice]++;
                arrPendientesTotal[indice] += arrMulta[posInfraccion];
                if (arrPendienteMasAntigua[indice] == 0 or fecha < arrPendienteMasAntigua[indice])
                    arrPendienteMasAntigua[indice] = fecha;
            }
        } else ignorarHasta('\r', arch);
    }
}

void ordenarPlacas(char *arrCarPlaca, int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad,
                   double *arrPagadasTotal, int *arrPendientesCantidad, double *arrPendientesTotal,
                   int *arrPendienteMasAntigua) {
    int n = contar(arrNumPlaca1);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((arrCarPlaca[i] < arrCarPlaca[j]) or (
                    ((arrNumPlaca1[i] * 1000 + arrNumPlaca2[i]) < (arrNumPlaca1[j] * 1000 + arrNumPlaca2[j])) and
                    arrCarPlaca[i] == arrCarPlaca[j])) {
                intercambiarChar(arrCarPlaca[i], arrCarPlaca[j]);
                intercambiarInt(arrNumPlaca1[i], arrNumPlaca1[j]);
                intercambiarInt(arrNumPlaca2[i], arrNumPlaca2[j]);
                intercambiarInt(arrPagadasCantidad[i], arrPagadasCantidad[j]);
                intercambiarDouble(arrPagadasTotal[i], arrPagadasTotal[j]);
                intercambiarInt(arrPendientesCantidad[i], arrPendientesCantidad[j]);
                intercambiarDouble(arrPendientesTotal[i], arrPendientesTotal[j]);
                intercambiarInt(arrPendienteMasAntigua[i], arrPendienteMasAntigua[j]);
            }
        }
    }
}

void generarReporte(char *arrCarPlaca, int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad,
                    double *arrPagadasTotal, int *arrPendientesCantidad, double *arrPendientesTotal,
                    int *arrPendienteMasAntigua, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    arch << setw(75) << "MINISTERIO DE TRANSPORTES" << endl;
    arch << setw(80) << "LISTADO DE INFRACCIONES TOTALIZADAS POR PLACA" << endl;
    imprimirLinea('=', arch);
    arch << setw(20) << "PLACA" << setw(13) << "CANTIDAD" << setw(11) << "TOTAL" << setw(13) << "CANTIDAD" << setw(11)
            << "TOTAL" << setw(15) << "MAS ANTIGUA" << setw(13) << "CANTIDAD" << setw(11) << "TOTAL" << endl;
    imprimirLinea('=', arch);
    int pagadasCantidadFinal = 0, pendientesCantidadFinal = 0, cantidadFinal = 0;
    double pagadasTotalFinal = 0.00, pendientesTotalFinal = 0.00, totalFinal = 0.00;
    for (int i = 0; arrNumPlaca1[i] != 0; i++) {
        int cantidad = arrPagadasCantidad[i] + arrPendientesCantidad[i];
        int total = arrPagadasTotal[i] + arrPendientesTotal[i];
        pagadasCantidadFinal += arrPagadasCantidad[i];
        pagadasTotalFinal += arrPagadasTotal[i];
        pendientesCantidadFinal += arrPendientesCantidad[i];
        pendientesTotalFinal += arrPendientesTotal[i];
        cantidadFinal += cantidad;
        totalFinal += total;
        arch << setw(10) << i + 1 << ")" << setw(3) << arrCarPlaca[i] << arrNumPlaca1[i] << "-" << arrNumPlaca2[i] <<
                setw(8) <<
                arrPagadasCantidad[i] << setw(14) << arrPagadasTotal[i] << setw(10) << arrPendientesCantidad[i] <<
                setw(14) << arrPendientesTotal[i] << setw(5) << "";
        imprimirFecha(arrPendienteMasAntigua[i], arch);
        arch << setw(10) << cantidad << setw(14) << total << endl;
    }
    imprimirLinea('=', arch);
    arch << setw(14) << "TOTALES" << setw(16) << pagadasCantidadFinal << setw(13) << pagadasTotalFinal << endl;
    imprimirLinea('=', arch);
}

void intercambiarInt(int &datoI, int &datoJ) {
    int aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void intercambiarDouble(double &datoI, double &datoJ) {
    double aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void intercambiarChar(char &datoI, char &datoJ) {
    char aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

int contar(int *arr) {
    int i = 0;
    while (arr[i] != 0) i++;
    return i;
}

int buscarPlaca(int numDatos, char carPlaca, int numPlaca1, int numPlaca2, char *arrCarPlaca, int *arrNumPlaca1,
                int *arrNumPlaca2) {
    for (int i = 0; i < numDatos; i++) {
        if (carPlaca == arrCarPlaca[i] and numPlaca1 == arrNumPlaca1[i] and numPlaca2 == arrNumPlaca2[i]) return i;
    }
    return NO_ENCONTRADO;
}

int buscarInfraccion(char carInfraccion, int numInfraccion, char *arrCarInfraccion, int *arrInfraccion) {
    for (int i = 0; arrInfraccion[i] != 0; i++) {
        if (carInfraccion == arrCarInfraccion[i] and numInfraccion == arrInfraccion[i]) return i;
    }
    return NO_ENCONTRADO;
}

int leerFecha(ifstream &arch) {
    int dd, mm, aa;
    char car;
    arch >> dd;
    if (arch.eof()) return 0;
    arch >> car >> mm >> car >> aa;
    return aa * 10000 + mm * 100 + dd;
}

void imprimirFecha(int fecha, ofstream &arch) {
    int dd, mm, aa;
    if (fecha > 0) {
        aa = fecha / 10000;
        fecha -= aa * 10000;
        mm = fecha / 100;
        fecha -= mm * 100;
        dd = fecha;
        arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
    } else arch << "----------";
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
