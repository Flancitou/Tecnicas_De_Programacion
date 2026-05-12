#include <iostream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_PACIENTES 50
#define MAX_DOCTORES 50
#define MAX_CRUZADOS 50
#define MAX_CITAS 100

int main() {
    int arrCodigoPaciente[MAX_PACIENTES], arrEdadPaciente[MAX_PACIENTES];
    char arrSexoPaciente[MAX_PACIENTES];
    llenarPacientes(arrCodigoPaciente, arrEdadPaciente, arrSexoPaciente, "ArchivosDeDatos/Pacientes.txt");

    int arrCodigoDoctor[MAX_DOCTORES];
    double arrRatingDoctor[MAX_DOCTORES];
    char arrCarCodigoDoctor[MAX_DOCTORES];
    llenarDoctores(arrCarCodigoDoctor, arrCodigoDoctor, arrRatingDoctor, "ArchivosDeDatos/Doctores.txt");

    int arrCodigoDoctorCruzado[MAX_CRUZADOS], arrCodigoPacienteCruzado[MAX_CRUZADOS];
    char arrCarCodigoDoctorCruzado[MAX_CRUZADOS];
    llenarCruzados(arrCarCodigoDoctorCruzado, arrCodigoDoctorCruzado, arrCodigoPacienteCruzado, "Pacientes_Doctor.txt");
    return 0;
}
