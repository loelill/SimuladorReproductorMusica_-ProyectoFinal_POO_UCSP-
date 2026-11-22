#include "Artista.h"

Artista::Artista(const char* nom, const char* pais)
    : cantidadObras(0), capacidad(4) {
    
    int lenNom = Cancion::longitudCadena(nom);
    nombre = new char[lenNom + 1];
    Cancion::copiarCadena(nombre, nom);

    int lenPais = Cancion::longitudCadena(pais);
    paisOrigen = new char[lenPais + 1];
    Cancion::copiarCadena(paisOrigen, pais);

    obras = new Cancion*[capacidad];
}

Artista::Artista(const Artista& otro)
    : cantidadObras(otro.cantidadObras), capacidad(otro.capacidad) {
    
    int lenNom = Cancion::longitudCadena(otro.nombre);
    nombre = new char[lenNom + 1];
    Cancion::copiarCadena(nombre, otro.nombre);

    int lenPais = Cancion::longitudCadena(otro.paisOrigen);
    paisOrigen = new char[lenPais + 1];
    Cancion::copiarCadena(paisOrigen, otro.paisOrigen);

    obras = new Cancion*[capacidad];
    for (int i = 0; i < cantidadObras; i++) {
        // Asociación: se copian las direcciones de memoria de las obras existentes
        *(obras + i) = *(otro.obras + i);
    }
}

Artista& Artista::operator=(const Artista& otro) {
    if (this != &otro) {
        delete[] nombre;
        delete[] paisOrigen;
        delete[] obras;

        cantidadObras = otro.cantidadObras;
        capacidad = otro.capacidad;

        int lenNom = Cancion::longitudCadena(otro.nombre);
        nombre = new char[lenNom + 1];
        Cancion::copiarCadena(nombre, otro.nombre);

        int lenPais = Cancion::longitudCadena(otro.paisOrigen);
        paisOrigen = new char[lenPais + 1];
        Cancion::copiarCadena(paisOrigen, otro.paisOrigen);

        obras = new Cancion*[capacidad];
        for (int i = 0; i < cantidadObras; i++) {
            *(obras + i) = *(otro.obras + i);
        }
    }
    return *this;
}

Artista::~Artista() {
    delete[] nombre;
    delete[] paisOrigen;
    delete[] obras;
}

void Artista::redimensionar() {
    capacidad *= 2;
    Cancion** nuevoArreglo = new Cancion*[capacidad];
    for (int i = 0; i < cantidadObras; i++) {
        *(nuevoArreglo + i) = *(obras + i);
    }
    delete[] obras;
    obras = nuevoArreglo;
}

void Artista::agregarObra(Cancion* cancion) {
    if (cancion == nullptr) return;
    if (cantidadObras == capacidad) {
        redimensionar();
    }
    *(obras + cantidadObras) = cancion;
    cantidadObras++;
}

void Artista::mostrarDiscografia() const {
    cout << "Artista: " << nombre << " (" << paisOrigen << ")" << endl;
    cout << "Obras registradas (" << cantidadObras << "):" << endl;
    for (int i = 0; i < cantidadObras; i++) {
        cout << "  - " << *(*(obras + i)) << endl;
    }
}

const char* Artista::getNombre() const {
    return nombre;
}

const char* Artista::getPaisOrigen() const {
    return paisOrigen;
}

int Artista::getCantidadObras() const {
    return cantidadObras;
}