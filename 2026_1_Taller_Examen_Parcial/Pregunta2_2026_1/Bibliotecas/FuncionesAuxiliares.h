#ifndef PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H

void llenarDisponibilidad(int *arrDia, int *arrHoraInicio, int *arrHoraFin, const char *nombArch);

void llenarArreglosAuxiliares(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                              double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp,
                              int *arrDiaSesTerTard, int *arrHoraSesTerTard, int *arrCantSesFueraDisp, int *arrDia,
                              int *arrHoraInicio, int *arrHoraFin, const char *nombArch);

void llenarDatos(int indice, int alumnos, int duracion, int dia, int horaInicio, int horaFin, int *arrDia,
                 double *arrPromAlumSesion, double *arrOcupacion, int *arrCantSesiones, int *arrHoraSesIniTemp,
                 int *arrDiaSesIniTemp, int *arrHoraSesTerTard, int *arrDiaSesTerTard, int *arrCantSesFueraDisp,
                 int *arrHoraInicio, int *arrHoraFin);

void generarInforme(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                    double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
                    int *arrHoraSesTerTard, int *arrCantSesFueraDisp, const char *nombArch);

void eliminarArreglos(char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
                      double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
                      int *arrHoraSesTerTard, int *arrCantSesFueraDisp);

void eliminar(int indice, char *arrCarAula, int *arrAula, int *arrCantSesiones, double *arrPromAlumSesion,
              double *arrOcupacion, int *arrDiaSesIniTemp, int *arrHoraSesIniTemp, int *arrDiaSesTerTard,
              int *arrHoraSesTerTard, int *arrCantSesFueraDisp, int &numDatos);

int contar(int *arrAula);

void imprimirSesion(int dia, int hora, ofstream &arch);

int buscarAula(char carAula, int aula, char *arrCarAula, int *arrAula);

int buscarDia(int dia, int *arrDia);

int leerHora(ifstream &arch);

void imprimirHora(int hora, ofstream &arch);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);


#endif //PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
