#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

void llenarPacientes(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        arch >> arrCodigoPaciente[i] >> ws;
        ignorarHasta(' ', arch);
        i++;
    }
}

void llenarDoctores(char *arrCarCodigoDoctor, int *arrCodigoDoctor, double *arrRatingDoctor, const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        i++;
    }
}

void llenarCruzados(char *arrCarCodigoDoctorCruzado, int *arrCodigoDoctorCruzado, int *arrCodigoPacienteCruzado,
                    const char *nombArch) {
    ifstream arch = abrirArchivosEntrada(nombArch);
    int i = 0;
    while (true) {
        i++;
    }
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
