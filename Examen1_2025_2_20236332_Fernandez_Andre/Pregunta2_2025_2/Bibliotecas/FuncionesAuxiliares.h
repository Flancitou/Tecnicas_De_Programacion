#ifndef PREGUNTA2_2025_2_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2025_2_FUNCIONESAUXILIARES_H

void llenarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream, char *arrCarCategoriaStream,
                   int *arrCategoriaStream, const char *nombArch);

void imprimirReportePrueba(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                           char *arrCarCategoriaStream, int *arrCategoriaStream, const char *nombArch);

void insertarOrdenado(int numDatos, int codigo, int duracion, int idioma, char carCategoria, int categoria,
                      int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream, char *arrCarCategoriaStream,
                      int *arrCategoriaStream);

void llenarArreglosAuxiliares(int *arrCodigoStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr,
                              double *arrTotRatCal, double *arrTotTasaDropOff, const char *nombArch);

void generarReporte(int tipo, int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                    char *arrCarCategoriaStream,
                    int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr,
                    double *arrTotRatCal, double *arrTotTasaDropOff, const char *nombArch);

void imprimirResumen(int streamMenorDuracion, int menorDuracion, int streamMayorDuracion, int mayorDuracion,
                     ofstream &arch);

void calcularMenorMayorDuracion(int totRepr, int arrCodigoStream, int &streamMenorDuracion, int &menorDuracion,
                                int &streamMayorDuracion, int &mayorDuracion);

void ordenarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                    char *arrCarCategoriaStream, int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente,
                    int *arrTotRepr, double *arrTotRatCal, double *arrTotTasaDropOff);

void eliminarStreams(int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream,
                     char *arrCarCategoriaStream, int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente,
                     int *arrTotRepr, double *arrTotRatCal, double *arrTotTasaDropOff);

void eliminar(int indice, int *arrCodigoStream, int *arrDuracionStream, int *arrIdiomaStream, char *arrCarCategoriaStream,
              int *arrCategoriaStream, int *arrRepAntigua, int *arrRepReciente, int *arrTotRepr, double *arrTotRatCal,
              double *arrTotTasaDropOff, int &numDatos);

int contar(int *arrCodigoStream);

void intercambiarInt(int &datoI, int &datoK);

void intercambiarDouble(double &datoI, double &datoK);

void intercambiarChar(char &datoI, char &datoK);

void imprimirCabecera(int tipo, ofstream &arch);

int buscarStream(int codigoStream, int *arrCodigoStream);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

int leerDuracion(ifstream &arch);

void imprimirDuracion(int duracion, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA2_2025_2_FUNCIONESAUXILIARES_H
