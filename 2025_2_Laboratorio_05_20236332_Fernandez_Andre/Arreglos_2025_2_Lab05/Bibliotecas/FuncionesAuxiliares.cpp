#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135
#define NO_ENCONTRADO -1

void llenarCanales(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, i = 0;
    while (true) {
        arch >> dd;
        if (arch.eof()) {
            arrNumCanal[i] = 0;
            break;
        }
        ignorarHasta(' ', arch);
        arch >> arrCarCanal[i] >> arrNumCanal[i] >> ws;
        ignorarHasta(' ', arch);
        arch >> arrRatingCanal[i];
        i++;
    }
}

void llenarEtiquetas(int *arrNumEtiqueta, int *arrDuracionEtiqueta, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrNumEtiqueta[i];
        if (arch.eof()) {
            arrNumEtiqueta[i] = 0;
            break;
        }
        arch >> ws;
        ignorarHasta(' ', arch);
        arrDuracionEtiqueta[i] = leerDuracion(arch);
        i++;
    }
}

void llenarCruzados(char *arrCarCanalCruzado, int *arrNumCanalCruzado, int *arrNumEtiquetaCruzado,
                    const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrCarCanalCruzado[i];
        if (arch.eof()) {
            arrNumCanalCruzado[i] = arrNumEtiquetaCruzado[i] = 0;
            break;
        }
        arch >> arrNumCanalCruzado[i] >> arrNumEtiquetaCruzado[i] >> ws;
        i++;
    }
}

void imprimirReportePrueba(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                           int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                           int *arrNumEtiquetaCruzado, const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << "CODIGO CANAL" << setw(15) << "RATING CANAL" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrNumCanal[i] != 0; i++) {
        arch << setw(5) << arrCarCanal[i] << arrNumCanal[i] << setw(14) << arrRatingCanal[i] << endl;
    }
    imprimirLinea('=', arch);
    arch << "CODIGO ETIQUETA" << setw(20) << "DURACION ETIQUETA" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrNumEtiqueta[i] != 0; i++) {
        arch << setw(10) << arrNumEtiqueta[i] << setw(14) << "";
        imprimirDuracion(arrDuracionEtiqueta[i], arch);
        arch << endl;
    }
    imprimirLinea('=', arch);
    arch << "CODIGO CANAL" << setw(20) << "CODIGO ETIQUETA" << endl;
    imprimirLinea('-', arch);
    for (int i = 0; arrNumEtiquetaCruzado[i] != 0; i++) {
        arch << setw(5) << arrCarCanalCruzado[i] << arrNumCanalCruzado[i] << setw(19) << arrNumEtiquetaCruzado[i] <<
                endl;
    }
}

void ordenarEtiquetasXDuracion(int *arrNumEtiqueta, int *arrDuracionEtiqueta) {
    int n = contar(arrNumEtiqueta);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrDuracionEtiqueta[i] < arrDuracionEtiqueta[j]) {
                intercambiarInt(arrNumEtiqueta[i], arrNumEtiqueta[j]);
                intercambiarInt(arrDuracionEtiqueta[i], arrDuracionEtiqueta[j]);
            }
        }
    }
}

void llenarArreglosAuxiliares(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                              int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                              int *arrNumEtiquetaCruzado, int *arrTotalReproduccion, int *arrTotalDuracion,
                              const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int dd, numCanal, numEtiqueta, reproduccion;
    char carCanal;
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        ignorarHasta(' ', arch);
        arch >> carCanal >> numCanal >> numEtiqueta;
        int posCruzado = buscarCruzado(carCanal, numCanal, numEtiqueta, arrCarCanalCruzado, arrNumCanalCruzado,
                                       arrNumEtiquetaCruzado);
        if (posCruzado != NO_ENCONTRADO) {
            arch >> reproduccion;
            int posCanal = buscarCanal(carCanal, numCanal, arrCarCanal, arrNumCanal);
            int posEtiqueta = buscarEtiqueta(numEtiqueta, arrNumEtiqueta);
            if (posCanal != NO_ENCONTRADO and posEtiqueta != NO_ENCONTRADO) {
                int duracion = arrDuracionEtiqueta[posEtiqueta];
                arrTotalReproduccion[posCruzado] += reproduccion;
                arrTotalDuracion[posCruzado] += duracion * reproduccion;
            }
        } else ignorarHasta('\n', arch);
    }
}

void generarInforme(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                    int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                    int *arrNumEtiquetaCruzado, int *arrTotalReproduccion, int *arrTotalDuracion,
                    const char *nombArch) {
    ofstream arch = abrirArchivosSalida(nombArch);
    double tarifaXDuracion = imprimirCabecera(arch);
    for (int i = 0; arrNumEtiqueta[i] != 0; i++) {
        imprimirCabeceraCanal(i, arrNumEtiqueta, arrDuracionEtiqueta, arch);
        int contador = 1, totalReproducciones = 0, totalDuracion = 0;
        double totalRating = 0.00;
        for (int j = 0; arrNumEtiquetaCruzado[j] != 0; j++) {
            if (arrNumEtiqueta[i] == arrNumEtiquetaCruzado[j]) {
                arch << setw(2) << contador << ")" << setw(4) << arrCarCanalCruzado[j] << arrNumCanalCruzado[j];
                for (int k = 0; arrNumCanal[k] != 0; k++) {
                    if (arrCarCanalCruzado[j] == arrCarCanal[k] and arrNumCanalCruzado[j] == arrNumCanal[k]) {
                        arch << setw(10) << arrRatingCanal[k] << setw(15) << arrTotalReproduccion[j] << setw(17) << "";
                        imprimirDuracion(arrTotalDuracion[j], arch);
                        arch << endl;
                        totalReproducciones += arrTotalReproduccion[j];
                        totalDuracion += arrTotalDuracion[j];
                        totalRating += arrRatingCanal[k];
                    }
                }
                contador++;
            }
        }
        imprimirResumen(totalReproducciones, totalDuracion, contador, totalRating, tarifaXDuracion, arch);
    }
}

double imprimirCabecera(ofstream &arch) {
    arch << right << fixed << setprecision(2);
    double tarifaXDuracion;
    cin >> tarifaXDuracion;
    arch << setw(75) << "PLATAFORMA TP_Twitch" << endl;
    arch << setw(68) << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifaXDuracion << " POR CADA MINUTO Y FRACCION" <<
            endl;
    return tarifaXDuracion;
}

void imprimirCabeceraCanal(int i, int *arrNumEtiqueta, int *arrDuracionEtiqueta, ofstream &arch) {
    imprimirLinea('=', arch);
    arch << "ETIQUETA NO. " << i + 1 << endl;
    arch << setw(11) << "CODIGO: " << arrNumEtiqueta[i] << endl;
    arch << setw(13) << "DURACION: ";
    imprimirDuracion(arrDuracionEtiqueta[i], arch);
    arch << endl;
    imprimirLinea('-', arch);
    arch << setw(31) << "CANALES DONDE SE REPRODUCE:" << endl;
    arch << setw(24) << "RATING DE" << setw(17) << "NUMERO TOTAL" << setw(23) << "TIEMPO TOTAL DE" << endl;
    arch << "No." << setw(9) << "CODIGO" << setw(11) << "CALIDAD" << setw(20) << "DE REPRODUCCIONES" << setw(20) <<
            "REPRODUCCIONES" << endl;
}

void imprimirResumen(int totalReproducciones, int totalDuracion, int contador, double totalRating,
                     double tarifaXDuracion, ofstream &arch) {
    imprimirLinea('-', arch);
    arch << setw(27) << "RESUMEN DE LA ETIQUETA:" << endl;
    arch << setw(30) << "TOTAL DE REPRODUCCIONES:" << setw(20) << totalReproducciones << endl;
    arch << setw(31) << "TIEMPO TOTAL REPRODUCIDO:" << setw(10) << "";
    imprimirDuracion(totalDuracion, arch);
    arch << endl;
    double promedioRating = totalRating / (contador - 1);
    double pocentajePromedio;
    arch << setw(37) << "PORCENTAJE PROMEDIO POR RATING:";
    if (promedioRating >= 4 and promedioRating <= 5) {
        arch << setw(13) << "+30%" << endl;
        pocentajePromedio = 1.30;
    } else if (promedioRating >= 3 and promedioRating <= 4) {
        arch << setw(13) << "+20%" << endl;
        pocentajePromedio = 1.20;
    } else if (promedioRating >= 2 and promedioRating <= 3) {
        arch << setw(13) << "0%" << endl;
        pocentajePromedio = 1.00;
    } else if (promedioRating >= 1 and promedioRating <= 2) {
        arch << setw(13) << "-25%" << endl;
        pocentajePromedio = 0.75;
    }
    arch << setw(34) << "INGRESOS POR REPRODUCCIONES:" << setw(9) << "$ " << tarifaXDuracion * totalDuracion / 60 *
            pocentajePromedio << endl;
}

int buscarCruzado(char carCanal, int numCanal, int numEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                  int *arrNumEtiquetaCruzado) {
    for (int i = 0; arrNumCanalCruzado[i] != 0; i++) {
        if (carCanal == arrCarCanalCruzado[i] and numCanal == arrNumCanalCruzado[i] and numEtiqueta ==
            arrNumEtiquetaCruzado[i])
            return i;
    }
    return NO_ENCONTRADO;
}

int buscarCanal(char carCanal, int numCanal, char *arrCarCanal, int *arrNumCanal) {
    for (int i = 0; arrNumCanal[i] != 0; i++) {
        if (carCanal == arrCarCanal[i] and numCanal == arrNumCanal[i]) return i;
    }
    return NO_ENCONTRADO;
}

int buscarEtiqueta(int numEtiqueta, int *arrNumEtiqueta) {
    for (int i = 0; arrNumEtiqueta[i] != 0; i++) {
        if (numEtiqueta == arrNumEtiqueta[i]) return i;
    }
    return NO_ENCONTRADO;
}

void intercambiarInt(int &valorI, int &valorJ) {
    int aux = valorI;
    valorI = valorJ;
    valorJ = aux;
}

int contar(int *arr) {
    int i = 0;
    while (arr[i] != 0) i++;
    return i;
}

int leerDuracion(ifstream &arch) {
    int min, ss;
    char car;
    arch >> min >> car >> ss;
    return min * 60 + ss;
}

void imprimirDuracion(int duracion, ofstream &arch) {
    int aux, hh, min, ss;
    aux = duracion / 60;
    if (aux >= 60) {
        hh = duracion / 3600;
        duracion -= hh * 3600;
        arch << setfill('0') << setw(2) << hh << ":" << setfill(' ');
    }
    min = duracion / 60;
    duracion -= min * 60;
    ss = duracion;
    arch << setfill('0') << setw(2) << min << ":" << setw(2) << ss << setfill(' ');
}

void ignorarHasta(char delim, ifstream &arch) {
    while (arch.get() != delim);
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
