#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135

void generarReporte(const char *nombArchEmpresas, const char *nombArchPlacas, const char *nombArchInfracciones,
                    const char *nombArchTabla, const char *nombArchReporte) {
    ifstream archEmpresas = abrirArchivosEntrada(nombArchEmpresas);
    ifstream archPlacas = abrirArchivosEntrada(nombArchPlacas);
    ifstream archInfracciones = abrirArchivosEntrada(nombArchInfracciones);
    ifstream archTabla = abrirArchivosEntrada(nombArchTabla);
    ofstream arch = abrirArchivosSalida(nombArchReporte);
    arch << right << fixed << setprecision(2);
    arch << setw(78) << "MINISTERIO DE TRANSPORTE" << endl;
    arch << setw(87) << "LISTADO DE ESTADO DE MULTAS POR COMPANIA" << endl;
    elaborarReporte(archEmpresas, archPlacas, archInfracciones, archTabla, arch);
}

void elaborarReporte(ifstream &archEmpresas, ifstream &archPlacas, ifstream &archInfracciones, ifstream &archTabla,
                     ofstream &arch) {
    int empresa, cantCaracteres, i = 0;
    while (true) {
        archEmpresas >> empresa;
        if (archEmpresas.eof()) break;
        double totalPagadasCompania = 0.0, totalPendientesCompania = 0.0;
        imprimirLinea('=', arch);
        arch << "COMPANIA No. " << i + 1 << endl;
        arch << "REPRESENTANTE LEGAL: ";
        imprimirTexto(' ', cantCaracteres, archEmpresas, arch);
        arch << setw(45 - cantCaracteres) << "DNI: " << empresa << setw(15) << "DISTRITO: ";
        imprimirTexto('\r', cantCaracteres, archEmpresas, arch);
        arch << endl;
        leerPlacas(empresa, archPlacas, archTabla, archInfracciones, arch, totalPagadasCompania,
                   totalPendientesCompania);
        imprimirLinea('=', arch);
        arch << "TOTAL MULTAS PAGADAS POR LA COMPANIA: " << totalPagadasCompania << endl;
        arch << "TOTAL MULTAS PENDIENTES DE PAGO POR LA COMPANIA: " << totalPendientesCompania << endl;
        i++;
    }
}

void leerPlacas(int empresa, ifstream &archPlacas, ifstream &archTabla, ifstream &archInfracciones,
                ofstream &arch, double &totalPagadasC, double &totalPendientesC) {
    archPlacas.clear();
    archPlacas.seekg(0, ios::beg);
    int empresaPlaca, placa1, placa2, i = 0;
    char carPlaca, car;
    while (true) {
        archPlacas >> empresaPlaca;
        if (archPlacas.eof()) break;
        if (empresa == empresaPlaca) {
            archPlacas >> carPlaca >> placa1 >> car >> placa2;
            imprimirLinea('=', arch);
            arch << setw(2) << "" << setfill('0') << setw(2) << i + 1 << ")" << setfill(' ') << setw(9) << "PLACA: " <<
                    carPlaca << placa1 << car << placa2 << setw(10) << "TIPO: ";
            if (carPlaca == 'P') arch << "PEQUENO" << endl;
            else if (carPlaca == 'M') arch << "MEDIANO" << endl;
            else if (carPlaca == 'G') arch << "GRANDE" << endl;
            leerInfracciones(carPlaca, placa1, placa2, archInfracciones, archTabla, arch, totalPagadasC,
                             totalPendientesC);
            i++;
        } else ignorarHasta('\r', archPlacas);
    }
}

void leerInfracciones(char carPlaca, int placa1, int placa2, ifstream &archInfracciones,
                      ifstream &archTabla, ofstream &arch, double &totalPagadasC, double &totalPendientesC) {
    archInfracciones.clear();
    archInfracciones.seekg(0, ios::beg);
    int cantPagadas = 0, cantPendientes = 0;
    double totalPagadasPlaca = 0.0, totalPendientesPlaca = 0.0;
    procesarInfracciones(carPlaca, placa1, placa2, archInfracciones, archTabla, arch,
                         cantPagadas, cantPendientes, totalPagadasPlaca, totalPendientesPlaca);
    if (cantPendientes > 0) arch << setw(40) << "TOTAL MULTAS PENDIENTES DE PAGO: " << totalPendientesPlaca << endl;
    totalPagadasC += totalPagadasPlaca;
    totalPendientesC += totalPendientesPlaca;
}

void procesarInfracciones(char carPlaca, int placa1, int placa2, ifstream &archInfracciones,
                          ifstream &archTabla, ofstream &arch, int &cantPagadas, int &cantPendientes,
                          double &totalPagadasPlaca, double &totalPendientesPlaca) {
    int fecha = leerFecha(archInfracciones);
    if (fecha == 0) {
        if (cantPagadas > 0) arch << setw(29) << "TOTAL MULTAS PAGADAS: " << totalPagadasPlaca << endl;
        return;
    }
    int fechaPago = 0, placaInfraccion1, placaInfraccion2, infraccion;
    char carPlacaInfraccion, car, carInfraccion;
    bool pagado = false, esInfraccionBuscada = false;
    archInfracciones >> carPlacaInfraccion >> placaInfraccion1 >> car >> placaInfraccion2;
    if (carPlaca == carPlacaInfraccion and placa1 == placaInfraccion1 and placa2 == placaInfraccion2) {
        esInfraccionBuscada = true;
        archInfracciones >> carInfraccion >> infraccion;
        if (archInfracciones.get() == ' ') {
            archInfracciones >> car;
            fechaPago = leerFecha(archInfracciones);
            pagado = true;
        } else pagado = false;
        if (pagado) {
            imprimirMultas(pagado, cantPagadas, cantPendientes, fecha, fechaPago,
                           carInfraccion, infraccion, archTabla, arch, totalPagadasPlaca, totalPendientesPlaca);
        }
    } else {
        ignorarHasta('\r', archInfracciones);
    }
    procesarInfracciones(carPlaca, placa1, placa2, archInfracciones, archTabla, arch,
                         cantPagadas, cantPendientes, totalPagadasPlaca, totalPendientesPlaca);
    if (esInfraccionBuscada and not pagado) {
        imprimirMultas(pagado, cantPagadas, cantPendientes, fecha, fechaPago,
                       carInfraccion, infraccion, archTabla, arch, totalPagadasPlaca, totalPendientesPlaca);
    }
}

void imprimirMultas(bool pagado, int &cantPagadas, int &cantPendientes, int fecha, int fechaPago,
                    char carInfraccion, int infraccion, ifstream &archTabla, ofstream &arch,
                    double &totalPagadasPlaca, double &totalPendientesPlaca) {
    if (pagado) {
        if (cantPagadas == 0) imprimirCabeceraPagadas(arch);
        imprimirNumeroCorrelativo(cantPagadas + 1, arch);
        imprimirFecha(fecha, arch);
        arch << setw(6) << "";
        imprimirFecha(fechaPago, arch);
        arch << setw(16) << infraccion << setw(13) << "";
        imprimirGravedad(carInfraccion, arch);
        totalPagadasPlaca += leerTabla(carInfraccion, infraccion, archTabla, arch);
        cantPagadas++;
    } else {
        if (cantPendientes == 0) imprimirCabeceraPendientes(arch);
        imprimirNumeroCorrelativo(cantPendientes + 1, arch);
        imprimirFecha(fecha, arch);
        arch << setw(17) << infraccion << setw(13) << "";
        imprimirGravedad(carInfraccion, arch);

        totalPendientesPlaca += leerTabla(carInfraccion, infraccion, archTabla, arch);
        cantPendientes++;
    }
}

double leerTabla(char carInfraccion, int infraccion, ifstream &archTabla, ofstream &arch) {
    archTabla.clear();
    archTabla.seekg(0, ios::beg);
    int infraccionTabla, cantCaracteres;
    double multa;
    char carInfraccionTabla;
    bool hayInfraccion = false;
    while (true) {
        archTabla >> carInfraccionTabla;
        if (archTabla.eof()) break;
        archTabla >> infraccionTabla >> multa;
        if (carInfraccion == carInfraccionTabla and infraccion == infraccionTabla) {
            arch << setw(6) << multa << setw(7) << "";
            imprimirTexto('\r', cantCaracteres, archTabla, arch);
            arch << endl;
            return multa;
        } else ignorarHasta('\r', archTabla);
    }
    arch << setw(6) << "0.00" << setw(7) << "" << "No se encontro esa infraccion" << endl;
    return 0.0;
}

void imprimirGravedad(char carInfraccion, ofstream &arch) {
    if (carInfraccion == 'L') arch << "LEVE" << setw(9) << "";
    else if (carInfraccion == 'G') arch << "GRAVE" << setw(8) << "";
    else if (carInfraccion == 'M') arch << "MUY GRAVE" << setw(4) << "";
}

void imprimirCabeceraPagadas(ofstream &arch) {
    arch << setw(21) << "MULTAS PAGADAS" << endl;
    arch << setw(10) << "No." << setw(11) << "FECHA" << setw(20) << "FECHA DE PAGO"
            << setw(16) << "INFRACCION" << setw(18) << "GRAVEDAD" << setw(11) << "MULTA"
            << setw(19) << "DESCRIPCION" << endl;
}

void imprimirCabeceraPendientes(ofstream &arch) {
    imprimirLinea('-', arch);
    arch << setw(32) << "MULTAS PENDIENTES DE PAGO" << endl;
    arch << setw(10) << "No." << setw(11) << "FECHA" << setw(21) << "INFRACCION"
            << setw(18) << "GRAVEDAD" << setw(11) << "MULTA" << setw(19) << "DESCRIPCION" << endl;
}

void imprimirNumeroCorrelativo(int numero, ofstream &arch) {
    arch << setw(7) << "" << setfill('0') << setw(2) << numero << ")"
            << setfill(' ') << setw(3) << "";
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

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida) {
    char car;
    cantCaracteres = 0;
    archEntrada >> ws;
    while (true) {
        archEntrada.get(car);
        if (car == delim) break;
        if (car == '/' or car == '_' or car == '-') car = ' ';
        archSalida.put(toupper(car));
        cantCaracteres++;
    }
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
