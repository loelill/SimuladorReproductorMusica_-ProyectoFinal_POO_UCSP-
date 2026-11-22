#include "../include/MotorOrdenamiento.h"

bool MotorOrdenamiento::debeIrAntes(const Cancion* a, const Cancion* b, CriterioOrden criterio, bool ascendente) {
    int comparacion = 0;

    if (criterio == POR_TITULO) {
        comparacion = Cancion::compararCadenas(a->getTitulo(), b->getTitulo());
    } else if (criterio == POR_DURACION) {
        if (a->getDuracion() < b->getDuracion()) comparacion = -1;
        else if (a->getDuracion() > b->getDuracion()) comparacion = 1;
    } else if (criterio == POR_ANIO) {
        comparacion = a->getAnio() - b->getAnio();
    } else if (criterio == POR_AGREGACION) {
        comparacion = a->getIdAgregacion() - b->getIdAgregacion();
    }

    if (ascendente) {
        return comparacion < 0;
    } else {
        return comparacion > 0;
    }
}

void MotorOrdenamiento::intercambiar(Cancion*& a, Cancion*& b) {
    Cancion* temp = a;
    a = b;
    b = temp;
}

void MotorOrdenamiento::ordenarBurbuja(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;

    for (int i = 0; i < cantidad - 1; i++) {
        bool huboIntercambio = false;
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (debeIrAntes(*(arreglo + j + 1), *(arreglo + j), criterio, ascendente)) {
                intercambiar(*(arreglo + j), *(arreglo + j + 1));
                huboIntercambio = true;
            }
        }
        if (!huboIntercambio) break;
    }
}

void MotorOrdenamiento::ordenarSeleccion(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;

    for (int i = 0; i < cantidad - 1; i++) {
        int indiceExtremo = i;
        for (int j = i + 1; j < cantidad; j++) {
            if (debeIrAntes(*(arreglo + j), *(arreglo + indiceExtremo), criterio, ascendente)) {
                indiceExtremo = j;
            }
        }
        if (indiceExtremo != i) {
            intercambiar(*(arreglo + i), *(arreglo + indiceExtremo));
        }
    }
}

void MotorOrdenamiento::ordenarInsercion(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;

    for (int i = 1; i < cantidad; i++) {
        Cancion* clave = *(arreglo + i);
        int j = i - 1;

        while (j >= 0 && debeIrAntes(clave, *(arreglo + j), criterio, ascendente)) {
            *(arreglo + j + 1) = *(arreglo + j);
            j--;
        }
        *(arreglo + j + 1) = clave;
    }
}

void MotorOrdenamiento::ordenarShellSort(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;

    for (int brecha = cantidad / 2; brecha > 0; brecha /= 2) {
        for (int i = brecha; i < cantidad; i++) {
            Cancion* temp = *(arreglo + i);
            int j = i;
            while (j >= brecha && debeIrAntes(temp, *(arreglo + j - brecha), criterio, ascendente)) {
                *(arreglo + j) = *(arreglo + j - brecha);
                j -= brecha;
            }
            *(arreglo + j) = temp;
        }
    }
}

int MotorOrdenamiento::particionar(Cancion** arreglo, int bajo, int alto, CriterioOrden criterio, bool ascendente) {
    Cancion* pivote = *(arreglo + alto);
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (debeIrAntes(*(arreglo + j), pivote, criterio, ascendente)) {
            i++;
            intercambiar(*(arreglo + i), *(arreglo + j));
        }
    }
    intercambiar(*(arreglo + i + 1), *(arreglo + alto));
    return i + 1;
}

void MotorOrdenamiento::quickSortRecursivo(Cancion** arreglo, int bajo, int alto, CriterioOrden criterio, bool ascendente) {
    if (bajo < alto) {
        int pi = particionar(arreglo, bajo, alto, criterio, ascendente);
        quickSortRecursivo(arreglo, bajo, pi - 1, criterio, ascendente);
        quickSortRecursivo(arreglo, pi + 1, alto, criterio, ascendente);
    }
}

void MotorOrdenamiento::ordenarQuickSort(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;
    quickSortRecursivo(arreglo, 0, cantidad - 1, criterio, ascendente);
}

void MotorOrdenamiento::mezclar(Cancion** arreglo, int izquierda, int medio, int derecha, CriterioOrden criterio, bool ascendente) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    Cancion** L = new Cancion*[n1];
    Cancion** R = new Cancion*[n2];

    for (int i = 0; i < n1; i++) {
        *(L + i) = *(arreglo + izquierda + i);
    }
    for (int j = 0; j < n2; j++) {
        *(R + j) = *(arreglo + medio + 1 + j);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < n1 && j < n2) {
        if (!debeIrAntes(*(R + j), *(L + i), criterio, ascendente)) {
            *(arreglo + k) = *(L + i);
            i++;
        } else {
            *(arreglo + k) = *(R + j);
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arreglo + k) = *(L + i);
        i++;
        k++;
    }

    while (j < n2) {
        *(arreglo + k) = *(R + j);
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void MotorOrdenamiento::mergeSortRecursivo(Cancion** arreglo, int izquierda, int derecha, CriterioOrden criterio, bool ascendente) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        mergeSortRecursivo(arreglo, izquierda, medio, criterio, ascendente);
        mergeSortRecursivo(arreglo, medio + 1, derecha, criterio, ascendente);
        mezclar(arreglo, izquierda, medio, derecha, criterio, ascendente);
    }
}

void MotorOrdenamiento::ordenarMergeSort(Cancion** arreglo, int cantidad, CriterioOrden criterio, bool ascendente) {
    if (arreglo == nullptr || cantidad <= 1) return;
    mergeSortRecursivo(arreglo, 0, cantidad - 1, criterio, ascendente);
}
