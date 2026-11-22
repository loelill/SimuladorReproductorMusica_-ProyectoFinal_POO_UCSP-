#include "ColaReproduccion.h"
#include <iostream>
using namespace std;

ColaReproduccion::ColaReproduccion() {
    capacidad = 4;
    cantidad = 0;
    posicionActual = -1;
    canciones = new Cancion*[capacidad];
}

ColaReproduccion::ColaReproduccion(const ColaReproduccion& otra) {
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    posicionActual = otra.posicionActual;
    canciones = new Cancion*[capacidad];
    for (int i = 0; i < cantidad; i++) {
        *(canciones + i) = *(otra.canciones + i);
    }
}

ColaReproduccion& ColaReproduccion::operator=(const ColaReproduccion& otra) {
    if (this != &otra) {
        Cancion** nuevo = new Cancion*[otra.capacidad];
        for (int i = 0; i < otra.cantidad; i++) {
            *(nuevo + i) = *(otra.canciones + i);
        }
        delete[] canciones;
        canciones = nuevo;
        capacidad = otra.capacidad;
        cantidad = otra.cantidad;
        posicionActual = otra.posicionActual;
    }
    return *this;
}

ColaReproduccion::~ColaReproduccion() {
    delete[] canciones; // No se destruyen las canciones originales.
}

void ColaReproduccion::redimensionar() {
    int nuevaCapacidad = capacidad * 2;
    Cancion** nuevo = new Cancion*[nuevaCapacidad];
    for (int i = 0; i < cantidad; i++) {
        *(nuevo + i) = *(canciones + i);
    }
    delete[] canciones;
    canciones = nuevo;
    capacidad = nuevaCapacidad;
}

bool ColaReproduccion::agregar(Cancion* cancion) {
    if (cancion == nullptr) return false;
    if (cantidad == capacidad) redimensionar();
    *(canciones + cantidad) = cancion;
    cantidad++;
    if (posicionActual == -1) posicionActual = 0;
    return true;
}

bool ColaReproduccion::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad) return false;
    for (int i = indice; i < cantidad - 1; i++) {
        *(canciones + i) = *(canciones + i + 1);
    }
    cantidad--;
    *(canciones + cantidad) = nullptr;
    if (cantidad == 0) posicionActual = -1;
    else if (indice < posicionActual) posicionActual--;
    else if (posicionActual >= cantidad) posicionActual = cantidad - 1;
    return true;
}

bool ColaReproduccion::mover(int origen, int destino) {
    if (origen < 0 || origen >= cantidad || destino < 0 || destino >= cantidad) return false;
    if (origen == destino) return true;

    Cancion* guardada = *(canciones + origen);
    if (origen < destino) {
        for (int i = origen; i < destino; i++) *(canciones + i) = *(canciones + i + 1);
    } else {
        for (int i = origen; i > destino; i--) *(canciones + i) = *(canciones + i - 1);
    }
    *(canciones + destino) = guardada;
    if (posicionActual == origen) posicionActual = destino;
    else if (origen < posicionActual && posicionActual <= destino) posicionActual--;
    else if (destino <= posicionActual && posicionActual < origen) posicionActual++;
    return true;
}

bool ColaReproduccion::seleccionar(int indice) {
    if (indice < 0 || indice >= cantidad) return false;
    posicionActual = indice;
    return true;
}

bool ColaReproduccion::siguiente() {
    if (posicionActual < 0 || posicionActual >= cantidad - 1) return false;
    posicionActual++;
    return true;
}

bool ColaReproduccion::anterior() {
    if (posicionActual <= 0) return false;
    posicionActual--;
    return true;
}

void ColaReproduccion::vaciar() {
    for (int i = 0; i < cantidad; i++) *(canciones + i) = nullptr;
    cantidad = 0;
    posicionActual = -1;
}

Cancion* ColaReproduccion::obtenerActual() const {
    if (posicionActual < 0 || posicionActual >= cantidad) return nullptr;
    return *(canciones + posicionActual);
}

Cancion* ColaReproduccion::obtenerEn(int indice) const {
    if (indice < 0 || indice >= cantidad) return nullptr;
    return *(canciones + indice);
}

int ColaReproduccion::getCantidad() const { return cantidad; }
int ColaReproduccion::getPosicionActual() const { return posicionActual; }
bool ColaReproduccion::estaVacia() const { return cantidad == 0; }

void ColaReproduccion::mostrarCola() const {
    cout << "=== COLA DE REPRODUCCION ===" << endl;
    if (cantidad == 0) cout << "La cola esta vacia." << endl;
    for (int i = 0; i < cantidad; i++) {
        if (i == posicionActual) cout << " > ";
        else cout << "   ";
        Cancion* actual = *(canciones + i);
        cout << i + 1 << ". " << *actual << endl;
    }
}
