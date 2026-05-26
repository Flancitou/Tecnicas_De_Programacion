#ifndef PREGUNTA1_2025_2_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2025_2_FUNCIONESAUXILIARES_H

void elaborarReporte(const char *nombArchStreams, const char *nombArchCategorias, const char *nombArchIdiomas,
                     const char *nombArchCanales, const char *nombArchReporte);

void leerStreams(ifstream &archStream, ifstream &archCategoria, ifstream &archIdioma, ifstream &archCanal,
                 ofstream &arch);

void leerCategorias(int stream, int duracionStream, int idiomaStream, char carCategoriaStream, int categoriaStream,
                    int &totalVecesReproducidas, int &tiempoTotalReproduccion, double &tasaDropOffMenor,
                    char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor, char &carCanalMayor,
                    int &canalMayor, ifstream &archCategoria, ifstream &archIdioma, ifstream &archCanal,
                    ofstream &arch);

void leerIdiomas(int stream, int duracionStream, int idiomaStream, char carCategoriaStream, int categoriaStream,
                 int cantCaracteres, int &totalVecesReproducidas, int &tiempoTotalReproduccion,
                 double &tasaDropOffMenor, char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor,
                 char &carCanalMayor, int &canalMayor, ifstream &archIdioma, ifstream &archCanal, ofstream &arch);

void leerCanales(int stream, int duracionStream, int &totalVecesReproducidas, int &tiempoTotalReproduccion,
                 double &tasaDropOffMenor, char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor,
                 char &carCanalMayor, int &canalMayor, ifstream &archCanal, ofstream &arch);

void imprimirCabeceraCanal(int carCanal, int canal, int &contadorCanales, ofstream &arch);

void imprimirReproducciones(int fechaReproduccion, int horaInicio, int horaFin, int duracionStream, int ratingCalidad,
                            double tasaDropOff, int &contadorReproducciones, int &totalReproducciones,
                            double &totalRating, double &totalTasaDropOff, ofstream &arch);

void imprimirResumenCanal(double totalRating, int contadorReproducciones, double totalTasaDropOff,
                          int totalReproducciones, char carCanal, int canal, double &tasaDropOffMenor,
                          char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor, char &carCanalMayor,
                          int &canalMayor, ofstream &arch);

void ignorarHasta(char delim, ifstream &arch);

int leerFecha(ifstream &arch);

void imprimirFecha(int fecha, ofstream &arch);

void imprimirTexto(int tipo, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida);

int leerDuracion(ifstream &arch);

void imprimirDuracion(int duracion, ofstream &arch);

void imprimirCabecera(ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA1_2025_2_FUNCIONESAUXILIARES_H
