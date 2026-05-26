#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

#define MAX_LINES 135

void elaborarReporte(const char *nombArchCursos, const char *nombArchProfesores, const char *nombArchSesiones,
                     const char *nombArchReporte) {
    ifstream archCursos = abrirArchivosEntrada(nombArchCursos);
    ifstream archProfesores = abrirArchivosEntrada(nombArchProfesores);
    ifstream archSesiones = abrirArchivosEntrada(nombArchSesiones);
    ofstream arch = abrirArchivosSalida(nombArchReporte);
    arch << right << fixed << setprecision(2);
    arch << setw(75) << "DETALLE DE CURSOS" << endl;
    generarReporte(archCursos, archProfesores, archSesiones, arch);
}

void generarReporte(ifstream &archCursos, ifstream &archProfesores, ifstream &archSesiones, ofstream &arch) {
    int curso, cantCursos = 0, horasTotales = 0;
    double creditoCurso;
    while (true) {
        archCursos >> curso;
        if (archCursos.eof()) break;
        archCursos >> creditoCurso;
        int totalHoras = 0, totalAlumnos = 0;
        leerSesiones(curso, creditoCurso, cantCursos, totalHoras, totalAlumnos, archCursos, archProfesores,
                     archSesiones, arch);
        if (totalHoras > 0) imprimirResumenCursos(totalHoras, totalAlumnos, horasTotales, arch);
    }
    imprimirResumenFinal(cantCursos, horasTotales, arch);
}

void leerSesiones(int curso, int creditoCurso, int &cantCursos, int &totalHoras, int &totalAlumnos,
                  ifstream &archCursos, ifstream &archProfesores, ifstream &archSesiones, ofstream &arch) {
    archSesiones.clear();
    archSesiones.seekg(0, ios::beg);
    int cursoSesion, horario, alumnos, profesorSesion, dia, horaInicio, horaFin, aula, cantCaracteres;
    char carAula;
    bool cursoEncontrado = false;
    while (true) {
        archSesiones >> cursoSesion;
        if (archSesiones.eof()) break;
        if (curso == cursoSesion) {
            if (not cursoEncontrado) {
                imprimirCabeceraCursos(curso, creditoCurso, archCursos, arch);
                cantCursos++;
                cursoEncontrado = true;
            }
            imprimirCabeceraSesiones(horario, alumnos, profesorSesion, archSesiones, archProfesores, arch);
            int contador = 1, duracion = 0;
            while (true) {
                archSesiones >> dia;
                horaInicio = leerHora(archSesiones);
                horaFin = leerHora(archSesiones);
                archSesiones >> carAula >> aula;
                arch << setw(2) << contador << ") ";
                imprimirDia(dia, arch);
                imprimirHora(horaInicio, arch);
                arch << " - ";
                imprimirHora(horaFin, arch);
                arch << setw(4) << carAula << aula << endl;
                duracion += (horaFin - horaInicio);
                contador++;
                if (archSesiones.get() == '\r') break;
            }
            imprimirResumenSesiones(duracion, alumnos, totalHoras, totalAlumnos, arch);
        } else while (archSesiones.get() != '\r');
    }
    if (not cursoEncontrado) while (archCursos.get() != '\r');
}

void leerProfesores(int profesorSesion, ifstream &archProfesores, ofstream &arch) {
    archProfesores.clear();
    archProfesores.seekg(0, ios::beg);
    int profesor, cantCaracteres;
    while (true) {
        archProfesores >> profesor;
        if (archProfesores.eof()) break;
        if (profesor == profesorSesion) {
            imprimirTexto(' ', cantCaracteres, archProfesores, arch);
            arch << setw(49 - cantCaracteres) << " - ";
            imprimirTexto(' ', cantCaracteres, archProfesores, arch);
            arch << setw(18 - cantCaracteres) << " - ";
            imprimirTexto('\r', cantCaracteres, archProfesores, arch);
        } else while (archProfesores.get() != '\r');
    }
}

void imprimirCabeceraSesiones(int &horario, int &alumnos, int &profesorSesion, ifstream &archSesiones,
                              ifstream &archProfesores, ofstream &arch) {
    imprimirLinea('-', arch);
    arch << "Horario" << setw(10) << "Alumnos" << setw(20) << "Profesor" << endl;
    archSesiones >> horario >> alumnos >> profesorSesion;
    arch << setw(1) << "" << setfill('0') << setw(4) << horario << setfill(' ') << setw(10) << alumnos <<
            setw(12) << profesorSesion << " - ";
    leerProfesores(profesorSesion, archProfesores, arch);
    arch << setw(17) << "Sesiones" << setw(12) << "Hora" << setw(15) << "Aula" << endl;
}

void imprimirResumenSesiones(int duracion, int alumnos, int &totalHoras, int &totalALumnos, ofstream &arch) {
    arch << "Horas de dictado del horario: ";
    imprimirHora(duracion, arch);
    arch << endl;
    totalHoras += duracion;
    totalALumnos += alumnos;
}

void imprimirCabeceraCursos(int curso, int creditoCurso, ifstream &archCursos, ofstream &arch) {
    int cantCaracteres;
    imprimirLinea('=', arch);
    arch << "CURSO: " << curso << " - ";
    imprimirTexto(' ', cantCaracteres, archCursos, arch);
    arch << setw(60 - cantCaracteres) << "CREDITOS:" << setw(6) << creditoCurso << setw(17) << "ESPECIALIDAD: ";
    imprimirTexto('\r', cantCaracteres, archCursos, arch);
    imprimirLinea('-', arch);
}

void imprimirResumenCursos(int totalHoras, int totalAlumnos, int &horasTotales, ofstream &arch) {
    imprimirLinea('-', arch);
    arch << "TOTAL DE HORAS DE DICTADO DEL CURSO: ";
    imprimirHora(totalHoras, arch);
    arch << endl;
    arch << "TOTAL DE ALUMNOS MATRICULADOS:" << setw(5) << totalAlumnos << endl;
    horasTotales += totalHoras;
}

void imprimirResumenFinal(int cantCursos, int horasTotales, ofstream &arch) {
    imprimirLinea('=', arch);
    arch << "RESUMEN" << endl;
    arch << "TOTAL DE CURSOS DICTADOS: " << cantCursos << endl;
    arch << "HORAS TOTALES DICTADAS: ";
    imprimirHora(horasTotales, arch);
    arch << endl;
    imprimirLinea('=', arch);
}

void imprimirHora(int hora, ofstream &arch) {
    int hh, min;
    hh = hora / 3600;
    hora -= hh * 3600;
    min = hora / 60;
    arch << setfill('0') << setw(2) << hh << ":" << setw(2) << min << setfill(' ');
}

void imprimirDia(int dia, ofstream &arch) {
    if (dia == 1) arch << "Domingo" << setw(3) << "";
    else if (dia == 2) arch << "Lunes" << setw(5) << "";
    else if (dia == 3) arch << "Martes" << setw(4) << "";
    else if (dia == 4) arch << "Miercoles" << setw(1) << "";
    else if (dia == 5) arch << "Jueves" << setw(4) << "";
    else if (dia == 6) arch << "Viernes" << setw(3) << "";
    else if (dia == 7) arch << "Sabado" << setw(4) << "";
}

int leerHora(ifstream &arch) {
    int hh, min;
    char car;
    arch >> hh >> car >> min;
    return hh * 3600 + min * 60;
}

void imprimirTexto(char delim, int &cantCaracteres, ifstream &archEntrada, ofstream &archSalida) {
    char car;
    cantCaracteres = 0;
    archEntrada >> ws;
    while (true) {
        archEntrada.get(car);
        if (car == delim)break;
        if (car == '_' or car == '/' or car == '-') car = ' ';
        if (not(car == '(' or car == ')' or car == '[' or car == ']')) archSalida.put(toupper(car));
        cantCaracteres++;
    }
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
