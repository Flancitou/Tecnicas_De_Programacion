#ifndef PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H

void elaborarReporte(const char *nombArchCursos, const char *nombArchProfesores, const char *nombArchSesiones,
                     const char *nombArchReporte);

void generarReporte(ifstream &archCursos, ifstream &archProfesores, ifstream &archSesiones, ofstream &arch);

void leerSesiones(int curso, int creditoCurso, int &cantCursos, int &totalHoras, int &totalAlumnos,
                  ifstream &archCursos, ifstream &archProfesores, ifstream &archSesiones, ofstream &arch);

void leerProfesores(int profesorSesion, ifstream &archProfesores, ofstream &arch);

void imprimirCabeceraSesiones(int &horario, int &alumnos, int &profesorSesion, ifstream &archSesiones,
                              ifstream &archProfesores, ofstream &arch);

void imprimirResumenSesiones(int duracion, int alumnos, int &totalHoras, int &totalALumnos, ofstream &arch);

void imprimirCabeceraCursos(int curso, int creditoCurso, ifstream &archCursos, ofstream &arch);

void imprimirResumenCursos(int totalHoras, int totalAlumnos, int &horasTotales, ofstream &arch);


void imprimirResumenFinal(int cantCursos, int horasTotales, ofstream &arch);

void imprimirHora(int hora, ofstream &arch);

void imprimirDia(int dia, ofstream &arch);

int leerHora(ifstream &arch);

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida);

void imprimirLinea(char car, ofstream &arch);

ifstream abrirArchivosEntrada(const char *archEntrada);

ofstream abrirArchivosSalida(const char *archSalida);

#endif //PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
