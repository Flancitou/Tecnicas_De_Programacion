#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 143

void elaborarReporte(const char *nombArchStreams, const char *nombArchCategorias, const char *nombArchIdiomas,
                     const char *nombArchCanales, const char *nombArchReporte) {
    ifstream archStream = abrirArchivosEntrada(nombArchStreams);
    ifstream archCategoria = abrirArchivosEntrada(nombArchCategorias);
    ifstream archIdioma = abrirArchivosEntrada(nombArchIdiomas);
    ifstream archCanal = abrirArchivosEntrada(nombArchCanales);
    ofstream arch = abrirArchivosSalida(nombArchReporte);
    imprimirCabecera(arch);
    leerStreams(archStream, archCategoria, archIdioma, archCanal, arch);
}

void leerStreams(ifstream &archStream, ifstream &archCategoria, ifstream &archIdioma, ifstream &archCanal,
                 ofstream &arch) {
    int stream, duracionStream, idiomaStream, categoriaStream, totalVecesReproducidas, tiempoTotalReproduccion,
            canalMenor, canalMayor, totalStreams = 0, totalDuracion = 0;
    double tasaDropOffMenor, tasaDropOffMayor;
    char carCanalMenor, carCanalMayor;
    char carCategoriaStream;
    while (true) {
        totalVecesReproducidas = tiempoTotalReproduccion = 0;
        tasaDropOffMenor = 99999999.99;
        tasaDropOffMayor = -1.00;
        archStream >> stream;
        if (archStream.eof()) break;
        duracionStream = leerDuracion(archStream);
        archStream >> idiomaStream >> carCategoriaStream >> categoriaStream;
        imprimirLinea('=', arch);
        arch << "STREAM: " << stream;
        leerCategorias(stream, duracionStream, idiomaStream, carCategoriaStream, categoriaStream,
                       totalVecesReproducidas, tiempoTotalReproduccion, tasaDropOffMenor, carCanalMenor, canalMenor,
                       tasaDropOffMayor, carCanalMayor, canalMayor, archCategoria, archIdioma, archCanal, arch);
        if (totalVecesReproducidas > 0) {
            arch << "RESUMEN DEL STREAM:" << endl;
            arch << "#VECES REPRODUCIDO:" << setw(8) << totalVecesReproducidas << endl;
            arch << "TIEMPO TOTAL REPRODUCCION: ";
            imprimirDuracion(tiempoTotalReproduccion, arch);
            arch << endl;
            arch << "TASA DROP-OFF MENOR: " << tasaDropOffMenor << " CANAL: " << carCanalMenor << canalMenor << endl;
            arch << "TASA DROP-OFF MAYOR: " << tasaDropOffMayor << " CANAL: " << carCanalMayor << canalMayor << endl;;
        }
        totalStreams += totalVecesReproducidas;
        totalDuracion += tiempoTotalReproduccion;
    }
    imprimirLinea('=', arch);
    arch << "RESUMEN TOTAL:" << endl;
    imprimirLinea('-', arch);
    arch << "# STREAMS: " << totalStreams << endl;
    arch << "DURACION TOTAL REPRODUCCION: ";
    imprimirDuracion(totalDuracion, arch);
    arch << endl;
    imprimirLinea('=', arch);
}

void leerCategorias(int stream, int duracionStream, int idiomaStream, char carCategoriaStream, int categoriaStream,
                    int &totalVecesReproducidas, int &tiempoTotalReproduccion, double &tasaDropOffMenor,
                    char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor, char &carCanalMayor,
                    int &canalMayor, ifstream &archCategoria, ifstream &archIdioma, ifstream &archCanal,
                    ofstream &arch) {
    archCategoria.clear();
    archCategoria.seekg(0, ios::beg);
    int categoria;
    char carCategoria;
    while (true) {
        archCategoria >> carCategoria;
        if (archCategoria.eof()) break;
        archCategoria >> categoria;
        if (carCategoria == carCategoriaStream and categoria == categoriaStream) {
            int cantCaracteres;
            arch << setw(15) << "CATEGORIA: " << carCategoria << categoria << " - ";
            imprimirTexto(1, cantCaracteres, archCategoria, arch);
            leerIdiomas(stream, duracionStream, idiomaStream, carCategoriaStream, categoriaStream, cantCaracteres,
                        totalVecesReproducidas, tiempoTotalReproduccion, tasaDropOffMenor, carCanalMenor, canalMenor,
                        tasaDropOffMayor, carCanalMayor, canalMayor, archIdioma, archCanal, arch);
        } else while (archCategoria.get() != '\n');
    }
}

void leerIdiomas(int stream, int duracionStream, int idiomaStream, char carCategoriaStream, int categoriaStream,
                 int cantCaracteres, int &totalVecesReproducidas, int &tiempoTotalReproduccion,
                 double &tasaDropOffMenor, char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor,
                 char &carCanalMayor, int &canalMayor, ifstream &archIdioma, ifstream &archCanal, ofstream &arch) {
    archIdioma.clear();
    archIdioma.seekg(0, ios::beg);
    int idioma;
    arch << right;
    while (true) {
        archIdioma >> idioma;
        if (archIdioma.eof()) break;
        if (idioma == idiomaStream) {
            arch << setw(69 - cantCaracteres) << "IDIOMA: " << idioma << " - ";
            imprimirTexto(2, cantCaracteres, archIdioma, arch);
            arch << setw(23 - cantCaracteres) << "DURACION: ";
            imprimirDuracion(duracionStream, arch);
            arch << endl;
            imprimirLinea('=', arch);
            leerCanales(stream, duracionStream, totalVecesReproducidas, tiempoTotalReproduccion, tasaDropOffMenor,
                        carCanalMenor, canalMenor, tasaDropOffMayor, carCanalMayor, canalMayor, archCanal, arch);
        } else while (archIdioma.get() != '\n');
    }
}

void leerCanales(int stream, int duracionStream, int &totalVecesReproducidas, int &tiempoTotalReproduccion,
                 double &tasaDropOffMenor, char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor,
                 char &carCanalMayor, int &canalMayor, ifstream &archCanal, ofstream &arch) {
    archCanal.clear();
    archCanal.seekg(0, ios::beg);
    int fechaCreacion, canal, streamCanal, fechaReproduccion, horaInicio, horaFin, totalReproducciones, contadorCanales
            = 0, contadorReproducciones;
    double ratingCalidad, tasaDropOff, totalRating, totalTasaDropOff;
    char carCanal;
    while (true) {
        fechaCreacion = leerFecha(archCanal);
        if (fechaCreacion == 0) break;
        archCanal >> carCanal >> canal >> ws;
        ignorarHasta(' ', archCanal);
        contadorReproducciones = 0;
        totalReproducciones = 0;
        totalRating = totalTasaDropOff = 0.00;
        while (true) {
            archCanal >> streamCanal;
            fechaReproduccion = leerFecha(archCanal);
            horaInicio = leerDuracion(archCanal);
            archCanal >> ratingCalidad >> tasaDropOff;
            tasaDropOff *= 100;
            if (stream == streamCanal) {
                if (contadorReproducciones == 0) {
                    imprimirCabeceraCanal(carCanal, canal, contadorCanales, arch);
                }
                imprimirReproducciones(fechaReproduccion, horaInicio, horaFin, duracionStream, ratingCalidad,
                                       tasaDropOff, contadorReproducciones, totalReproducciones, totalRating,
                                       totalTasaDropOff, arch);
            }
            if (archCanal.get() == '\r') break;
        }
        if (contadorReproducciones > 0) {
            imprimirResumenCanal(totalRating, contadorReproducciones, totalTasaDropOff, totalReproducciones, carCanal,
                                 canal, tasaDropOffMenor, carCanalMenor, canalMenor, tasaDropOffMayor, carCanalMayor,
                                 canalMayor, arch);
        }
        tiempoTotalReproduccion += totalReproducciones;
        totalVecesReproducidas += contadorReproducciones;
    }
}

void imprimirCabeceraCanal(int carCanal, int canal, int &contadorCanales, ofstream &arch) {
    arch << setw(2) << "" << setfill('0') << setw(2) << contadorCanales + 1 << ")" << setfill(' ') <<
            setw(9) << "CANAL: " << carCanal << canal << endl;
    arch << setw(21) << "REPRODUCCIONES" << endl;
    arch << setw(10) << "No." << setw(10) << "FECHA" << setw(15) << "INICIO" << setw(12) << "FIN" <<
            setw(23) << "RATING CALIDAD" << setw(22) << "TASA DROP-OFF" << endl;
    contadorCanales++;
}

void imprimirReproducciones(int fechaReproduccion, int horaInicio, int horaFin, int duracionStream, int ratingCalidad,
                            double tasaDropOff, int &contadorReproducciones, int &totalReproducciones,
                            double &totalRating, double &totalTasaDropOff, ofstream &arch) {
    arch << setw(6) << "" << setfill('0') << setw(2) << contadorReproducciones + 1 << ")" << setfill(' ') <<
            setw(3) << "";
    imprimirFecha(fechaReproduccion, arch);
    arch << setw(6) << "";
    imprimirDuracion(horaInicio, arch);
    arch << setw(6) << "";
    horaFin = duracionStream + horaInicio;
    imprimirDuracion(horaFin, arch);
    arch << setw(14) << ratingCalidad << setw(24) << tasaDropOff << "%" << endl;
    totalReproducciones += duracionStream;
    totalRating += ratingCalidad;
    totalTasaDropOff += tasaDropOff;
    contadorReproducciones++;
}

void imprimirResumenCanal(double totalRating, int contadorReproducciones, double totalTasaDropOff,
                          int totalReproducciones, char carCanal, int canal, double &tasaDropOffMenor,
                          char &carCanalMenor, int &canalMenor, double &tasaDropOffMayor, char &carCanalMayor,
                          int &canalMayor, ofstream &arch) {
    double promRating = totalRating / contadorReproducciones;
    double promDropOff = totalTasaDropOff / contadorReproducciones;
    arch << setw(35) << "TOTAL TIEMPO REPRODUCCIONES: ";
    imprimirDuracion(totalReproducciones, arch);
    arch << endl;
    arch << setw(31) << "PROMEDIO RATING CALIDAD: " << promRating << endl;
    arch << setw(30) << "PROMEDIO TASA DROP-OFF: " << promDropOff << "%" << endl;
    imprimirLinea('-', arch);
    if (promDropOff < tasaDropOffMenor) {
        tasaDropOffMenor = promDropOff;
        carCanalMenor = carCanal;
        canalMenor = canal;
    }
    if (promDropOff > tasaDropOffMayor) {
        tasaDropOffMayor = promDropOff;
        carCanalMayor = carCanal;
        canalMayor = canal;
    }
}


void ignorarHasta(char delim, ifstream &arch) {
    while (arch.get() != delim);
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
    aa = fecha / 10000;
    fecha -= aa * 10000;
    mm = fecha / 100;
    fecha -= mm * 100;
    dd = fecha;
    arch << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
}

void imprimirTexto(int tipo, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida) {
    char car, carAnt = ' ';
    cantCaracteres = 0;
    archEntrada >> ws;
    while (true) {
        archEntrada.get(car);
        if (car == '\r') break;
        if (car == '_') car = ' ';
        if (tipo == 1 or (tipo == 2 and carAnt == ' ')) archSalida.put(toupper(car));
        else if (tipo == 2 and carAnt != ' ') archSalida.put(tolower(car));
        carAnt = car;
        cantCaracteres++;
    }
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

void imprimirCabecera(ofstream &arch) {
    arch << right << fixed << setprecision(2);
    imprimirLinea('=', arch);
    arch << setw(78) << "PLATAFORMA DE STREAMING TP" << endl;
    arch << setw(77) << "REPRODUCCION DE STREAMS" << endl;
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
