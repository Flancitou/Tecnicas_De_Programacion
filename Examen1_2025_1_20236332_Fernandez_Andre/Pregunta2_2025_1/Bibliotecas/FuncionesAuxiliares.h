#ifndef PREGUNTA2_2025_1_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2025_1_FUNCIONESAUXILIARES_H

void llenarTabla(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, const char *nombArch);

void imprimirReportePrueba(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, const char *nombArch);

void llenarArreglosAuxiliares(char *arrCarInfraccion, int *arrInfraccion, double *arrMulta, char *arrCarPlaca,
                              int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad, double *arrPagadasTotal,
                              int *arrPendientesCantidad, double *arrPendientesTotal, int *arrPendienteMasAntigua,
                              const char *nombArch);

void ordenarPlacas(char *arrCarPlaca, int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad,
                   double *arrPagadasTotal, int *arrPendientesCantidad, double *arrPendientesTotal,
                   int *arrPendienteMasAntigua);

void generarReporte(char *arrCarPlaca, int *arrNumPlaca1, int *arrNumPlaca2, int *arrPagadasCantidad,
                    double *arrPagadasTotal, int *arrPendientesCantidad, double *arrPendientesTotal,
                    int *arrPendienteMasAntigua, const char *nombArch);

void intercambiarInt(int &datoI, int &datoJ);

void intercambiarDouble(double &datoI, double &datoJ);

void intercambiarChar(char &datoI, char &datoJ);

int contar(int *arr);

int buscarPlaca(int numDatos, char carPlaca, int numPlaca1, int numPlaca2, char *arrCarPlaca, int *arrNumPlaca1,
                int *arrNumPlaca2);

int buscarInfraccion(char carInfraccion, int numInfraccion, char *arrCarInfraccion, int *arrInfraccion);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA2_2025_1_FUNCIONESAUXILIARES_H
