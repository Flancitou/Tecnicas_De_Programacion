#ifndef PREGUNTA1_2025_1_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2025_1_FUNCIONESAUXILIARES_H

void generarReporte(const char *nombArchEmpresas, const char *nombArchPlacas, const char *nombArchInfracciones,
                    const char *nombArchTabla, const char *nombArchReporte);

void elaborarReporte(ifstream &archEmpresas, ifstream &archPlacas, ifstream &archInfracciones, ifstream &archTabla,
                     ofstream &arch);

void leerPlacas(int empresa, ifstream &archPlacas, ifstream &archTabla, ifstream &archInfracciones, ofstream &arch,
                double &totalPagadasC, double &totalPendientesC);

void leerInfracciones(char carPlaca, int placa1, int placa2, ifstream &archInfracciones, ifstream &archTabla,
                      ofstream &arch, double &totalPagadasC, double &totalPendientesC);

void procesarInfracciones(char carPlaca, int placa1, int placa2, ifstream &archInfracciones, ifstream &archTabla,
                          ofstream &arch, int &cantPagadas, int &cantPendientes, double &totalPagadasPlaca,
                          double &totalPendientesPlaca);

void imprimirMultas(bool pagado, int &cantPagadas, int &cantPendientes, int fecha, int fechaPago, char carInfraccion,
                    int infraccion, ifstream &archTabla, ofstream &arch, double &totalPagadasPlaca,
                    double &totalPendientesPlaca);

double leerTabla(char carInfraccion, int infraccion, ifstream &archTabla, ofstream &arch);

void imprimirGravedad(char carInfraccion, ofstream &arch);

void imprimirCabeceraPagadas(ofstream &arch);

void imprimirCabeceraPendientes(ofstream &arch);

void imprimirNumeroCorrelativo(int numero, ofstream &arch);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida);

void ignorarHasta(char delim, ifstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA1_2025_1_FUNCIONESAUXILIARES_H
