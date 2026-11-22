#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

enum CriterioOrden {
    POR_TITULO = 1,
    POR_DURACION = 2,
    POR_ANIO = 3,
    POR_AGREGACION = 4
};

class MotorOrdenamiento {
private:
    static bool debeIrAntes(const Cancion* a, const Cancion* b, CriterioOrden criterio, bool ascendente);
    static void intercambiar(Cancion*& a, Cancion*& b);
    static int particionar(Cancion** arreglo, int bajo, int alto, CriterioOrden criterio, bool ascendente);
    static void quickSortRecursivo(Cancion** arreglo, int bajo, int alto, CriterioOrden criterio, bool ascendente);
    static void mezclar(Cancion** arreglo, int izquierda, int medio, int derecha, CriterioOrden criterio, bool ascendente);
    static void mergeSortRecursivo(Cancion** arreglo, int izquierda, int derecha, CriterioOrden criterio, bool ascendente);

public:
    static void ordenarBurbuja(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
    static void ordenarSeleccion(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
    static void ordenarInsercion(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
    static void ordenarShellSort(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
    static void ordenarQuickSort(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
    static void ordenarMergeSort(Cancion** arreglo, int cantidad, CriterioOrden criterio = POR_TITULO, bool ascendente = true);
};
