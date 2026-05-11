#ifndef ARREGLOS_2025_2_LAB05_FUNCIONESAUXILIARES_H
#define ARREGLOS_2025_2_LAB05_FUNCIONESAUXILIARES_H

void llenarCanales(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, const char *nombArch);

void llenarEtiquetas(int *arrNumEtiqueta, int *arrDuracionEtiqueta, const char *nombArch);

void llenarCruzados(char *arrCarCanalCruzado, int *arrNumCanalCruzado, int *arrNumEtiquetaCruzado,
                    const char *nombArch);

void imprimirReportePrueba(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                           int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                           int *arrNumEtiquetaCruzado, const char *nombArch);

void ordenarEtiquetasXDuracion(int *arrNumEtiqueta, int *arrDuracionEtiqueta);

void llenarArreglosAuxiliares(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                              int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                              int *arrNumEtiquetaCruzado, int *arrTotalReproduccion, int *arrTotalDuracion,
                              const char *nombArch);

void generarInforme(char *arrCarCanal, int *arrNumCanal, double *arrRatingCanal, int *arrNumEtiqueta,
                    int *arrDuracionEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                    int *arrNumEtiquetaCruzado, int *arrTotalReproduccion, int *arrTotalDuracion,
                    const char *nombArch);

double imprimirCabecera(ofstream &arch);

void imprimirCabeceraCanal(int i, int *arrNumEtiqueta, int *arrDuracionEtiqueta, ofstream &arch);

void imprimirResumen(int totalReproducciones, int totalDuracion, int contador, double totalRating,
                     double tarifaXDuracion, ofstream &arch);

int buscarCruzado(char carCanal, int numCanal, int numEtiqueta, char *arrCarCanalCruzado, int *arrNumCanalCruzado,
                  int *arrNumEtiquetaCruzado);

int buscarCanal(char carCanal, int numCanal, char *arrCarCanal, int *arrNumCanal);

int buscarEtiqueta(int numEtiqueta, int *arrNumEtiqueta);

void intercambiarInt(int &valorI, int &valorJ);

int contar(int *arr);

int leerDuracion(ifstream &arch);

void imprimirDuracion(int duracion, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //ARREGLOS_2025_2_LAB05_FUNCIONESAUXILIARES_H
