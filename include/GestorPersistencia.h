#pragma once
#include "Cancion.h"
#include <fstream>
#include <iostream>

using namespace std;

class GestorPersistencia {
private:
    char* rutaBiblioteca;
    char* rutaLogBenchmark;

public:
    GestorPersistencia(const char* rutaBib, const char* rutaLog);
    GestorPersistencia(const GestorPersistencia& otro);
    GestorPersistencia& operator=(const GestorPersistencia& otro);
    ~GestorPersistencia();

    bool guardarBiblioteca(Cancion** lista, int cantidad) const;
    bool registrarBenchmark(const char* algoritmo, int cantidadElementos, double tiempoMs) const;
    void mostrarLogBenchmark() const;

    const char* getRutaBiblioteca() const;
    const char* getRutaLogBenchmark() const;
};