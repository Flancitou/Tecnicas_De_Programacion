#ifndef INC_2026_1_LAB04_ARREGLOS_MODIFICADO_FUNCIONESAUXILIARES_H
#define INC_2026_1_LAB04_ARREGLOS_MODIFICADO_FUNCIONESAUXILIARES_H

void llenarPacientes(int *arrCodigoPaciente, int *arrEdadPaciente, char *arrSexoPaciente, const char *nombArch);

void llenarDoctores(char *arrCarCodigoDoctor, int *arrCodigoDoctor, double *arrRatingDoctor, const char *nombArch);

void llenarCruzados(char *arrCarCodigoDoctorCruzado, int *arrCodigoDoctorCruzado, int *arrCodigoPacienteCruzado,
                    const char *nombArch);

void ignorarHasta(char delim, ifstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

#endif //INC_2026_1_LAB04_ARREGLOS_MODIFICADO_FUNCIONESAUXILIARES_H
